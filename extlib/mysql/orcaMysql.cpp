/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMysql.cpp -

  Copyright (C) 2009-2010 Lee, Ki-Yeul

**********************************************************************/



#include "porting.h"
#include "orcaMysql.h"

orcaMysqlResult s_mysqlresult;
orcaMysqlResult *g_mysqlresult = &s_mysqlresult;

extern "C" void* get_mysql() 
{
	orcaMysql* my = new orcaMysql();
	return my;
}

orcaMysqlResult* orcaMysqlResult::rs_clone(MYSQL_RES* result)
{
	orcaMysqlResult* rp = (orcaMysqlResult*)g_mysqlresult->clone(g_root);
	rp->m_result = result;
	rp->m_size = 0;
	rp->m_row = NULL;

	if (result) {
		rp->m_size = mysql_num_fields(result);
		rp->m_row = mysql_fetch_row(result);
	}
	return rp;
}

orcaObject* orcaMysqlResult::v_clone() 
{
	orcaMysqlResult* mp = new orcaMysqlResult(NULL);
	mp->m_result = this->m_result;
	m_size = this->m_size;
	m_row = this->m_row;
	return mp;
}

orcaData orcaMysqlResult::ex_next(orcaVM* vm, int n) 
{
	m_row = mysql_fetch_row(m_result);
	if (m_row == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	return this;
}

orcaData orcaMysqlResult::operator()(orcaVM* vm, int param_n)
{
	if (m_row == NULL) {
		throw orcaException(vm, "orca.iter", "out of range");
	}

	orcaTuple* tp = new orcaTuple();
	for (int i=0; i<m_size; i++) {
		tp->push_back(m_row[i]);
	}

	return tp;
}

orcaMysqlResult::orcaMysqlResult()
{
	set_name("mysqlresult");

	insert_native_function("next", (object_fp)&orcaMysqlResult::ex_next);
}





orcaObject* orcaMysql::v_clone() 
{
	orcaMysql* mp = new orcaMysql(NULL);
	mp->m_conn = NULL;
	return mp;
}

orcaData orcaMysql::ex_connect(orcaVM* vm, int n) 
{
	if (n < 4) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	const char* host = vm->get_param(0).String().c_str();
	const char* id = vm->get_param(1).String().c_str();
	const char* pw = vm->get_param(2).String().c_str();
	const char* db = vm->get_param(3).String().c_str();

	if (m_conn != NULL) mysql_close(m_conn);
	m_conn = mysql_init(NULL);
	mysql_real_connect(m_conn, host, id, pw, db, 0, NULL, 0);

	return NIL;
}

orcaData orcaMysql::ex_update(orcaVM* vm, int n) 
{
	if (n < 1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	return mysql_query(m_conn, vm->get_param(0).String().c_str());
}

orcaData orcaMysql::ex_execute(orcaVM* vm, int n) 
{
	if (n < 1) {
		throw orcaException(vm, "orca.param", "insufficient parameter");
	}

	int ret = mysql_query(m_conn, vm->get_param(0).String().c_str());
	if (ret == 0) {
		return orcaMysqlResult::rs_clone(mysql_store_result(m_conn));
	}

	return NIL;
}

orcaMysql::orcaMysql()
{
	set_name("mysql");
	insert_native_function("connect", (object_fp)&orcaMysql::ex_connect);
	insert_native_function("execute", (object_fp)&orcaMysql::ex_execute);
	insert_native_function("update", (object_fp)&orcaMysql::ex_update);

	m_conn = NULL;
}



