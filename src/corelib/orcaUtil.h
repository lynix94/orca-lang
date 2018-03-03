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


class orcaUtil : public orcaObject 
{
public:
	orcaUtil()
	{
		set_name("cutil");
		insert_member("lru", new ex_lru());
	}

	class ex_lru : public orcaObject 
	{
	public:
		DEFAULT_NATIVE_DEFINE(ex_lru);

		ex_lru() 
		{ 
			set_name("lru"); 
			insert_native_function("insert", (object_fp)&ex_lru::ex_insert);
			insert_native_function("victimize", (object_fp)&ex_lru::ex_victimize);
			insert_native_function("touch", (object_fp)&ex_lru::ex_touch);
			insert_native_function("size", (object_fp)&ex_lru::ex_size);
			insert_native_function("dump", (object_fp)&ex_lru::ex_dump);
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
};

#endif

