/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaUtil.h - for functional programming

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_UTIL
#define _DEF_ORCA_UTIL

#include <stdlib.h>

#include "porting.h"
#include "orcaStack.h"
#include "orcaObject.h"


template <typename K, typename V>
struct list_item
{
	list_item* next;
	list_item* prev;
	K key;
	V item;
};

template <typename K, typename V>
struct orca_lru
{
	typedef list_item<K, V> lru_item;

	orca_lru() 
	{
		head = &s_head;
		head->next = head;
		head->prev = head;
	}

	void insert(K k, V v)
	{
		lru_item* i = new lru_item();
		i->key = k;
		i->item = v;

		mtx.lock();
			kv_map[k] = i;

			i->prev = head;
			i->next = head->next;
			head->next = i;
			i->next->prev = i;
		mtx.unlock();
	}

	bool victimize(V* v, K* k = NULL)
	{
		mtx.lock();
			if (head->prev == head) {
				mtx.unlock();
				return false;
			}

			lru_item* i = head->prev;
			head->prev = i->prev;
			i->prev->next = head;

			kv_map.erase(kv_map.find(i->key));
		mtx.unlock();

		*v = i->item;

		if (k != NULL)
			*k = i->key;

		delete i;

		return true;
	}

	lru_item* touch(K key)
	{
		mtx.lock();
			typename map<K, lru_item*>::iterator it = kv_map.find(key);
			
			lru_item* i = NULL;
			if (it != kv_map.end()) {
				i = it->second;

				i->prev->next = i->next;
				i->next->prev = i->prev;

				i->prev = head;
				i->next = head->next;
				i->next->prev = i;
				head->next = i;
			}
		mtx.unlock();

		return i; 
	}

	int size()
	{
		return kv_map.size();
	}

	lru_item s_head;
	lru_item* head;
	map<K, lru_item*> kv_map;
	portMutex mtx;
};


class orcaUtilLru : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaUtilLru);

	orcaUtilLru() 
	{ 
		set_name("lru"); 
		insert_native_function("insert", (object_fp)&orcaUtilLru::ex_insert);
		insert_native_function("victimize", (object_fp)&orcaUtilLru::ex_victimize);
		insert_native_function("touch", (object_fp)&orcaUtilLru::ex_touch);
		insert_native_function("size", (object_fp)&orcaUtilLru::ex_size);
		insert_native_function("dump", (object_fp)&orcaUtilLru::ex_dump);
	}

	orcaData ex_insert(orcaVM* vm, int n)
	{
		if (n < 2) vm->need_param();
		m_lru.insert(vm->get_param(0), vm->get_param(1));
		vm->get_param(0).rc_inc();
		vm->get_param(1).rc_inc();
		return NIL;
	}

	orcaData ex_victimize(orcaVM* vm, int n)
	{
		orcaData key = NIL;
		orcaData dp = NIL;

		if (m_lru.victimize(&dp, &key)) {
			dp.rc_dec();
			key.rc_dec();
		}

		return NIL;
	}

	orcaData ex_touch(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();
		return m_lru.touch(vm->get_param(0));
	}

	orcaData ex_size(orcaVM* vm, int n)
	{
		return m_lru.size();
	}

	orcaData ex_dump(orcaVM* vm, int n)
	{
		list_item<orcaData, orcaData>* head = m_lru.head;
		list_item<orcaData, orcaData>* curr = head->next;
		
		while (curr != head) {
			curr->item.dump();
			curr = curr->next;
		}

		return NIL;
	}

	orca_lru<orcaData, orcaData> m_lru;
};


class orcaStringUtil : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaStringUtil);

	orcaStringUtil()
	{
		set_name("stringutil");
		insert_static_native_function("html_escape", (object_fp)&orcaStringUtil::ex_html_escape);
		insert_static_native_function("html_unescape", (object_fp)&orcaStringUtil::ex_html_unescape);
		insert_static_native_function("url_escape", (object_fp)&orcaStringUtil::ex_url_escape);
		insert_static_native_function("url_unescape", (object_fp)&orcaStringUtil::ex_url_unescape);
	}

	orcaData ex_html_escape(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		string s = vm->get_param(0).String();

		stringstream ss;
		for (int i=0; i<s.length(); i++) {
			switch (s[i])
			{
			case '\"':	ss << "&quot;"; break;
			case '<':	ss << "&lt;"; break;
			case '>':	ss << "&gt;"; break;
			case '&':	ss << "&amp;";	break;
			default:	ss << s[i];
			}
		}

		return ss.str();
	}

	orcaData ex_html_unescape(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		string s = vm->get_param(0).String();

		stringstream ss;
		for (int i=0; i<s.length(); i++) {
			if (s[i] == '&') {
				if (i+5 < s.length() &&
					strncmp(s.c_str() + i + 1, "quot;", 5) == 0)
				{
					ss << '\"';
					i += 5;
					continue;
				}

				if (i+4 < s.length() &&
					strncmp(s.c_str() + i + 1, "amp;", 4) == 0)
				{
					ss << '&';
					i += 4;
					continue;
				}

				if (i+3 < s.length() &&
					strncmp(s.c_str() + i + 1, "lt;", 3) == 0)
				{
					ss << '<';
					i += 3;
					continue;
				}

				if (i+3 < s.length() &&
					strncmp(s.c_str() + i + 1, "gt;", 3) == 0)
				{
					ss << '>';
					i += 3;
					continue;
				}
			}

			ss << s[i];
		}

		return ss.str();
	}

	orcaData ex_url_escape(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		string s = vm->get_param(0).String();

		char buff[16];
		stringstream ss;
		for (int i=0; i<s.length(); i++) {
			unsigned char c = (unsigned char)s[i];
			if ((c >= 'a' && c <= 'z') ||
				(c >= 'A' && c <= 'Z') ||
				(c >= '0' && c <= '9') ||
				(c == '.' || c == '-'))
			{
				ss << c;
				continue;
			}

			sprintf(buff, "%%%02X", c);
			ss << buff;
		}

		return ss.str();
	}

	orcaData ex_url_unescape(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();
		string s = vm->get_param(0).String();

		stringstream ss;
		for (int i=0; i<s.length(); i++) {
			if (s[i] == '%') {
				if (i+2 >= s.length()) {
					throw orcaException(vm, "url decoding failed");
				}

				unsigned int h = (unsigned int)s[i+1];
				unsigned int l = (unsigned int)s[i+2];
				unsigned int val;

				if (h >= '0' && h <= '9') {
					val = (h - '0') << 4;
				}
				else if (h >= 'a' && h <= 'f') {
					val = (h - 'a' + 10) << 4;
				}
				else if (h >= 'A' && h <= 'F') {
					val = (h - 'A' + 10) << 4;
				}
				else {
					throw orcaException(vm, "url decoding failed");
				}

				if (l >= '0' && l <= '9') {
					val += (l - '0');
				}
				else if (l >= 'a' && l <= 'f') {
					val += (l - 'a' + 10);
				}
				else if (l >= 'A' && l <= 'F') {
					val += (l - 'A' + 10);
				}
				else {
					throw orcaException(vm, "url decoding failed");
				}

				ss << (char)val;
				i += 2;
			}
			else {
				ss << s[i];
			}
		}

		return ss.str();
	}
};


#endif

