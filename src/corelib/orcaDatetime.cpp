/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaDatetime.cpp -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaDatetime.h"
#include "orcaDate.h"
#include "orcaTime.h"

#include "orcaThread.h"
set<pthread_t> orcaThread::m_remains;

cp_map<orcaData>::Type orcaDate::m_static_date;
cp_map<orcaData>::Type orcaTime::m_static_time;
cp_map<orcaData>::Type orcaDatetime::m_static_datetime;

void orcaDatetime::__init()
{
	set_name("datetime");
	insert_static_native_function("now", (object_fp)&orcaDatetime::ex_now);
	insert_native_function("init", (object_fp)&orcaDatetime::ex_init);
	insert_native_function("date", (object_fp)&orcaDatetime::ex_date);
	insert_native_function("time", (object_fp)&orcaDatetime::ex_time);
	insert_native_function("+", (object_fp)&orcaDatetime::ex_add);
	insert_native_function("-", (object_fp)&orcaDatetime::ex_sub);
	insert_native_function("<", (object_fp)&orcaDatetime::ex_lt);
	insert_native_function("==", (object_fp)&orcaDatetime::ex_eq);
}

orcaDatetime::orcaDatetime()
{
	__init();
}

orcaDatetime::orcaDatetime(ptime t)
{
	__init();
	m_ptime = t;
}

orcaDatetime::orcaDatetime(time_t t)
{
	__init();
	m_ptime = from_time_t(t);
}

ptime& orcaDatetime::get_ptime()
{
	return m_ptime;
}

void orcaDatetime::string_(orcaVM* vm, string& str)
{
	str += to_iso_extended_string(m_ptime);
}

orcaData orcaDatetime::ex_init(orcaVM* vm, int n) 
{
	if (n < 0) {
		return this;
	}

	string format = vm->get_param(0).String();
	init_by_string(format);
	return this;
}

orcaData orcaDatetime::ex_now(orcaVM* vm, int n) 
{
	return new orcaDatetime(microsec_clock::local_time());
}

orcaData orcaDatetime::ex_date(orcaVM* vm, int n) 
{
	return new orcaDate(m_ptime.date());
}

orcaData orcaDatetime::ex_time(orcaVM* vm, int n) 
{
	return new orcaTime(m_ptime.time_of_day());
}

orcaData orcaDatetime::ex_add(orcaVM* vm, int n) 
{
	orcaData d = vm->get_param(0);
	orcaData bn, bn_tmp;
	int i;

	switch(d.get_type())
	{
	case TYPE_INT:
	case TYPE_REAL:
	case TYPE_STR:
		i = d.Integer();
		return new orcaDatetime(m_ptime + microseconds(i));

	case TYPE_BIGNUM: {
		mpz_t b, b_tmp;
		mpz_init(b);
		mpz_init(b_tmp);

		mpz_mod_ui(b, d.bn(), 1000000);
		int us = mpz_get_si(b);
		mpz_tdiv_q_ui(b_tmp, d.bn(), 1000000);

		mpz_mod_ui(b, b_tmp, 3600*24);
		int s = mpz_get_si(b);
		mpz_tdiv_q_ui(b_tmp, b_tmp, 3600*24);

		int ds = mpz_get_si(b_tmp);

		mpz_clear(b);
		mpz_clear(b_tmp);
		return new orcaDatetime(m_ptime 
								+ days(ds) 
								+ seconds(s) 
								+ microseconds(us));
		}

	case TYPE_OBJ:
		orcaObject* op = vm->get_param(0).Object();
		if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
			return new orcaDatetime(m_ptime + tp->m_td);
		}
		else if (orcaDateDuration* dd = dynamic_cast<orcaDateDuration*>(op)) {
			return new orcaDatetime(m_ptime 
									+ years(dd->years)
									+ months(dd->months)
									+ days(dd->days)
									+ weeks(dd->weeks));
		}
	}

	return NIL;
}

orcaData orcaDatetime::ex_sub(orcaVM* vm, int n) 
{
	orcaData d = vm->get_param(0);
	int i;

	switch(d.get_type())
	{
	case TYPE_INT:
	case TYPE_REAL:
	case TYPE_STR:
		i = d.Integer();
		return new orcaDatetime(m_ptime - microseconds(i));

	case TYPE_BIGNUM: {
		mpz_t b, b_tmp;
		mpz_init(b);
		mpz_init(b_tmp);

		mpz_mod_ui(b, d.bn(), 1000000);
		int us = mpz_get_si(b);
		mpz_tdiv_q_ui(b_tmp, d.bn(), 1000000);

		mpz_mod_ui(b, b_tmp, 3600*24);
		int s = mpz_get_si(b);
		mpz_tdiv_q_ui(b_tmp, b_tmp, 3600*24);

		int ds = mpz_get_si(b_tmp);

		mpz_clear(b);
		mpz_clear(b_tmp);
		return new orcaDatetime(m_ptime 
								- days(ds) 
								- seconds(s) 
								- microseconds(us));
		}

	case TYPE_OBJ:
		orcaObject* op = vm->get_param(0).Object();
		if (orcaDatetime* dtp = dynamic_cast<orcaDatetime*>(op)) {
			return new orcaTime(m_ptime - dtp->m_ptime);
		}
		else if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
			return new orcaDatetime(m_ptime - tp->m_td);
		}
		else if (orcaDateDuration* dd = dynamic_cast<orcaDateDuration*>(op)) {
			return new orcaDatetime(m_ptime 
									- years(dd->years)
									- months(dd->months)
									- days(dd->days)
									- weeks(dd->weeks));
		}
	}

	return NIL;
}

orcaData orcaDatetime::ex_lt(orcaVM* vm, int n) 
{
	orcaObject* op = vm->get_param(0).Object();
	
	if (orcaDatetime* tp = dynamic_cast<orcaDatetime*>(op)) {
		return m_ptime < tp->m_ptime;
	}
	else if (orcaDate* dp = dynamic_cast<orcaDate*>(op)) {
		return m_ptime < ptime(dp->m_date, hours(0));
	}

	return NIL;
}

orcaData orcaDatetime::ex_eq(orcaVM* vm, int n) 
{
	orcaObject* op = vm->get_param(0).Object();
	
	if (orcaDatetime* tp = dynamic_cast<orcaDatetime*>(op)) {
		return m_ptime == tp->m_ptime;
	}
	else if (orcaDate* dp = dynamic_cast<orcaDate*>(op)) {
		return m_ptime == ptime(dp->m_date, hours(0));
	}

	return NIL;
}

