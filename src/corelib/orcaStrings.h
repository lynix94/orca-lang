/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaStrings.h - system utils

  Copyright (C) 2009-2010 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_STRINGS
#define _DEF_ORCA_STRINGS

#include <sstream>

class orcaStringBuilder : public orcaObject 
{
public:
	orcaStringBuilder(void* vp) {}

	virtual ~orcaStringBuilder()
	{
		for (int i=0; i<items.size(); i++) {
			items[i].rc_dec();
		}
	}

	orcaObject* v_clone() {
		return new orcaStringBuilder((void*)NULL);
	}

	orcaStringBuilder() 
	{ 
		set_name("builder"); 
		insert_native_function("push_back", (object_fp)&orcaStringBuilder::ex_push_back);
		insert_native_function("+", (object_fp)&orcaStringBuilder::ex_push_back);
		insert_native_function("string", (object_fp)&orcaStringBuilder::ex_string);
		insert_native_function("clear", (object_fp)&orcaStringBuilder::ex_clear);
	}

	virtual orcaData operator()(orcaVM* vm, int n)
	{
		return new orcaStringBuilder();
	}

	orcaData ex_push_back(orcaVM* vm, int n)
	{
		if (n < 1) vm->need_param();
		items.push_back(vm->get_param(0));
		vm->get_param(0).rc_inc();
		return this;
	}

	orcaData ex_clear(orcaVM* vm, int n)
	{
		for (int i=0; i<items.size(); i++) {
			items[i].rc_dec();
		}

		items.clear();
		return this;
	}

	orcaData ex_string(orcaVM* vm, int n)
	{
		string ret;
		string_(vm, ret);
		return ret;
	}

	virtual void string_(orcaVM* vm, string& str)
	{
		stringstream ss;
		ss << str;
		for (int i=0; i<items.size(); i++) {
			ss << items[i].string_(vm);
		}

		str += ss.str();
	}

	vector<orcaData> items;
};

class orcaStrings : public orcaObject 
{
public:
	orcaStrings() 
	{
		set_name("strings");

		insert_member("builder", new orcaStringBuilder());
		insert_static_native_function("join", (object_fp)&orcaStrings::ex_join);
		insert_static_native_function("html_escape", (object_fp)&orcaStrings::ex_html_escape);
		insert_static_native_function("html_unescape", (object_fp)&orcaStrings::ex_html_unescape);
		insert_static_native_function("url_escape", (object_fp)&orcaStrings::ex_url_escape);
		insert_static_native_function("url_unescape", (object_fp)&orcaStrings::ex_url_unescape);
	}

	orcaData ex_join(orcaVM* vm, int n) 
	{
		if (n < 2) {
			return "";
		}

		stringstream ss;
		string split = vm->get_param(0).String();
		for (int i=1; i<n; i++) {
			ss << vm->get_param(i).string_(vm);
			if (i != n-1) {
				ss << split;
			}
		}

		return ss.str();
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
			if (s[i] == '+') {
				ss << ' ';
				continue;
			}

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

