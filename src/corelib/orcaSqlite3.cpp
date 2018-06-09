/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaSqlite3.cpp -

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/



#include "porting.h"
#include "orcaSqlite3.h"
#include "orcaRoot.h"
#include "orcaException.h"
#include "orcaTuple.h"

#include "kyString.h"

orcaSqlite3Result* orcaSqlite3Result::rs_make(sqlite3_stmt* stmt)
{
	orcaSqlite3Result* rp = new orcaSqlite3Result();
	rp->stmt = stmt;
	rp->ncols = sqlite3_column_count(stmt);
	if (sqlite3_step(stmt) == SQLITE_DONE) {
		rp->done = true;
	}
	else {
		rp->done = false;
	}

	rp->flag_ready = false;
	return rp;
}

orcaSqlite3Result* orcaSqlite3Result::rs_make(bool rc, const string& msg)
{
	orcaSqlite3Result* rp = new orcaSqlite3Result();
	rp->stmt = NULL;
	rp->ncols = 1;
	rp->done = false;

	rp->rc = rc;
	rp->msg = msg;

	rp->flag_ready = false;
	return rp;
}

orcaObject* orcaSqlite3Result::v_clone() 
{
	orcaSqlite3Result* sp = new orcaSqlite3Result(NULL);
	sp->stmt = this->stmt;
	sp->ncols = this->ncols;
	sp->flag_ready = this->flag_ready;
	return sp;
}

orcaData orcaSqlite3Result::ex_next(orcaVM* vm, int n) 
{
	if (flag_ready == false) {
		flag_ready = true;
		return this;
	}

	if (done || stmt == NULL || sqlite3_step(stmt) == SQLITE_DONE) {
		done = true;
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	return this;
}

orcaData orcaSqlite3Result::operator()(orcaVM* vm, int param_n)
{
	if (done) {
		throw orcaException(vm, "orca.iter.end", "out of range");
	}

	if (stmt == NULL) {
		return rc;
	}

	orcaTuple* tp = new orcaTuple();
	for (int i=0; i<ncols; i++) {
		switch (sqlite3_column_type(stmt, i))
		{
		case (SQLITE3_TEXT):
			tp->push_back((char*)sqlite3_column_text(stmt, i));
			break;
		case (SQLITE_INTEGER):
			tp->push_back(sqlite3_column_int(stmt, i));
			break;
		case (SQLITE_FLOAT):
			tp->push_back(sqlite3_column_double(stmt, i));
			break;
		default:
			tp->push_back(NIL);
			break;
		}
	}

	return tp;
}





orcaData orcaSqlite3Conn::ex_execute(orcaVM* vm, int n) 
{
	if (n < 1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	char *err_msg;
	string query = vm->get_param(0).String();
	if (kyString::starts_with(kyString::to_lower(kyString::strip(query)), "select") == false) {
		int ret = sqlite3_exec(db, query.c_str(), 0, 0, &err_msg);
		if (ret != SQLITE_OK) {
			string msg = err_msg;
			sqlite3_free(err_msg);
			throw orcaException(vm, "db.execute", msg);
		}

		return orcaSqlite3Result::rs_make(true);
	}

	// select
	sqlite3_stmt *stmt;
	int ret = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		throw orcaException(vm, "db.execute", sqlite3_errmsg(db));
	}

	return orcaSqlite3Result::rs_make(stmt);
}

orcaData orcaSqlite3::ex_connect(orcaVM* vm, int n) 
{
	if (n < 1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	const char* file = vm->get_param(0).String().c_str();

	sqlite3* db;
	int ret = sqlite3_open(file, &db);
	if (ret != SQLITE_OK) {
		sqlite3_close(db);
		throw orcaException(vm, "db.connect", "can't connect db");
	}

	orcaSqlite3Conn* sp = new orcaSqlite3Conn(db);
	return sp;
}




