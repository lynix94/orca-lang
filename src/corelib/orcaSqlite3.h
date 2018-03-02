/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSqlite3.h - sqlite3 client

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#include <sqlite3.h>

#include "orcaObject.h"


class orcaSqlite3Result;

class orcaSqlite3Result : public orcaObject 
{
public:
	orcaSqlite3Result()
	{
		set_name("sqlite3result");
		insert_native_function("next", (object_fp)&orcaSqlite3Result::ex_next);
	}

	virtual ~orcaSqlite3Result()
	{
		if (stmt != NULL) {
			sqlite3_finalize(stmt);
		}
	}

	orcaSqlite3Result(void* vp) { }
	orcaObject* v_clone();

	static orcaSqlite3Result* rs_make(sqlite3_stmt *stmt);
	static orcaSqlite3Result* rs_make(bool rc, const string& msg = "");

	orcaData ex_next(orcaVM* vm, int n);
	virtual orcaData operator()(orcaVM* vm, int param_n);
private:
	bool rc;
	string msg;

	sqlite3_stmt *stmt;
	int ncols;
	bool done;
};

class orcaSqlite3Conn : public orcaObject 
{
public:
	orcaSqlite3Conn(sqlite3* db)
	{
		set_name("sqlite3conn");
		insert_native_function("execute", (object_fp)&orcaSqlite3Conn::ex_execute);

		this->db = db;
	}

	virtual ~orcaSqlite3Conn() {}
	orcaSqlite3Conn(void* vp) { }
	orcaObject* v_clone()
	{
		orcaSqlite3Conn* sp = new orcaSqlite3Conn((void*)NULL);
		sp->db = db;
		return sp;
	}

	orcaData ex_execute(orcaVM* vm, int n); 

private:
	sqlite3 *db;
};

class orcaSqlite3 : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaSqlite3);
	orcaSqlite3()
	{
		set_name("sqlite3");
		insert_native_function("connect", (object_fp)&orcaSqlite3::ex_connect);
	}

	orcaData ex_connect(orcaVM* vm, int n);
};



