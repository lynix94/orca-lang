/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMysql.h - mysql client

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#include "orcaObject.h"
#include "orcaTuple.h"
#include "orcaRoot.h"
#include "orcaException.h"

#include <my_global.h>
#include <mysql.h>

class orcaMysqlResult;
extern orcaMysqlResult* g_mysqlresult;

class orcaMysqlResult : public orcaObject 
{
public:
	orcaMysqlResult();
	virtual ~orcaMysqlResult() { }

	orcaMysqlResult(void* vp) { }
	orcaObject* v_clone();

	static orcaMysqlResult* rs_clone(MYSQL_RES* result);
	orcaData ex_next(orcaVM* vm, int n);
	virtual orcaData operator()(orcaVM* vm, int param_n);
private:
	MYSQL_RES *m_result;
	int m_size;
	MYSQL_ROW m_row;
};

class orcaMysql : public orcaObject 
{
public:
	orcaMysql();
	virtual ~orcaMysql() {}

	orcaMysql(void* vp) { }
	orcaObject* v_clone();

	orcaData ex_connect(orcaVM* vm, int n);
	orcaData ex_update(orcaVM* vm, int n);
	orcaData ex_execute(orcaVM* vm, int n); 

private:
	MYSQL *m_conn;
};



