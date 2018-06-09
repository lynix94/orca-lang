/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaStrings.h - system utils

  Copyright (C) 2009-2010 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_STRINGS
#define _DEF_ORCA_STRINGS

#include <sstream>


class orcaStrings : public orcaObject 
{
public:
	orcaStrings() 
	{
		set_name("strings");

		insert_static_native_function("join", (object_fp)&orcaStrings::ex_join);
		insert_member("builder", new orcaStringBuilder());
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
};

#endif

