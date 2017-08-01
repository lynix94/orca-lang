/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaIO.h - 

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_IO
#define _DEF_ORCA_IO

#include <iostream>

#include "orcaObject.h"
#include "orcaFile.h"

using namespace std;

class orcaIO : public orcaObject 
{
public:
	orcaIO() 
	{
		set_name("io");
		insert_static("print", new ex_print());
		insert_static("put", new ex_put());
		insert_static("open", new ex_open());
		insert_static("input", new ex_input());
	}

	class ex_print : public orcaObject 
	{
	public:
		DEFAULT_NATIVE_DEFINE(ex_print);
		ex_print() 
		{ 
			set_name("print"); 
		}

		virtual orcaData operator()(orcaVM* vm, int n) 
		{
			string str;
			for (int i=0; i<n; i++) 
				vm->get_param(i).string_(vm, str);

			str += "\n";

			cout << str;

			return NIL;
		}
	};

	class ex_put : public orcaObject 
	{
	public:
		DEFAULT_NATIVE_DEFINE(ex_put);
		ex_put()
		{ 
			set_name("put"); 
		}

		virtual orcaData operator()(orcaVM* vm, int n) 
		{
			string str;
			for (int i=0; i<n; i++) 
				vm->get_param(i).string_(vm, str);

			cout << str;

			return NIL;
		}
	};

	class ex_open : public orcaObject 
	{
	public:
		DEFAULT_NATIVE_DEFINE(ex_open);
		ex_open()
		{ 
			set_name("open"); 
		}

		virtual orcaData operator()(orcaVM* vm, int n) 
		{
			orcaFile *file = new orcaFile();
			orcaData ret = file->get_member("open");
			ret.native_call(vm, n);

			return file;
		}
	};

	class ex_input : public orcaObject 
	{
	public:
		DEFAULT_NATIVE_DEFINE(ex_input);
		ex_input()
		{ 
			set_name("input"); 
		}

		virtual orcaData operator()(orcaVM* vm, int n) 
		{
			char buff[1024];
			if (fgets(buff, sizeof(buff), stdin) == NULL) {
				return "";
			}

			return buff;
		}
	};
};


#endif

