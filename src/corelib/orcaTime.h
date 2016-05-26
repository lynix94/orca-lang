/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTime.h - 

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_TIME
#define _DEF_ORCA_TIME

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::gregorian;
using namespace boost::posix_time;

#include "porting.h"
#include "orcaObject.h"
#include "orcaDate.h"
#include "orcaException.h"


class orcaTime : public orcaObject 
{
friend class orcaDatetime;
friend class orcaDate;
public:
	DEFAULT_NATIVE_DEFINE(orcaTime);

	void __init()
	{
		set_name("time");
		insert_static_native_function("msleep", (object_fp)&orcaTime::ex_msleep);
		insert_native_function("init", (object_fp)&orcaTime::ex_init);
		insert_native_function(".attr", (object_fp)&orcaTime::ex_get);
		insert_native_function("+", (object_fp)&orcaTime::ex_add);
		insert_native_function("-", (object_fp)&orcaTime::ex_sub);
		insert_native_function("*", (object_fp)&orcaTime::ex_mul);
		insert_native_function("/", (object_fp)&orcaTime::ex_div);
		insert_native_function("<", (object_fp)&orcaTime::ex_lt);
		insert_native_function("==", (object_fp)&orcaTime::ex_eq);

		insert_static_native_function("time_of_day", (object_fp)&orcaTime::ex_time_of_day);
		insert_static_native_function("hours", (object_fp)&orcaTime::ex_hours);
		insert_static_native_function("minutes", (object_fp)&orcaTime::ex_minutes);
		insert_static_native_function("seconds", (object_fp)&orcaTime::ex_seconds);
		insert_static_native_function("microseconds", (object_fp)&orcaTime::ex_microseconds);
	}

	orcaTime()
	{
		__init();
	}

	orcaTime(time_duration t)
	{
		__init();
		m_td = t;
	}

	orcaTime(int h, int m, int s, int us)
	{
		__init();

		if (h) m_td += hours(h);
		if (m) m_td += minutes(m);
		if (s) m_td += seconds(s);
		if (us) m_td += microseconds(us);
	}

	virtual void string_(orcaVM* vm, string& str)
	{
		str += to_simple_string(m_td);
	}

	orcaData ex_msleep(orcaVM* vm, int n) 
	{
		int tmout = 0;
		if (n > 0) {
			tmout = vm->get_param(0).Integer();
		}

		port_msleep(tmout);
		return NIL;
	}

	orcaData ex_init(orcaVM* vm, int n) 
	{
		m_td = hours(0);

		if (n < 1) {
			return this;
		}

		orcaData d = vm->get_param(0);
		
		if (is<TYPE_STR>(d)) {
			string format = vm->get_param(0).String();
			init_by_string(format);
		}
		else {
			int h = vm->get_param(0).Integer();
			m_td += hours(h);

			if (n>=2) {
				int m = vm->get_param(1).Integer();
				m_td += minutes(m);
			}
			if (n>=3) {
				int s = vm->get_param(2).Integer();
				m_td += seconds(s);
			}
			if (n>=4) {
				int us = vm->get_param(3).Integer();
				m_td += microseconds(us);
			}
		}

		return this;
	}

	orcaData ex_get(orcaVM* vm, int n) 
	{
		string name = vm->get_param(0).String();
		if (name == "hour") {
			return (int)m_td.hours();
		}
		else if (name == "minute") {
			return (int)m_td.minutes();
		}
		else if (name == "second") {
			return (int)m_td.seconds();
		}

		throw orcaException(vm, "orca.lang", "member not exists");

		return NIL;
	}

	orcaData ex_add(orcaVM* vm, int n) 
	{
		orcaData d = vm->get_param(0);
		int i;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			return new orcaTime(m_td + microseconds(i));

		case TYPE_BIGNUM: {
			mpz_t b, b_tmp;
			mpz_init(b);
			mpz_init(b_tmp);

			mpz_mod_ui(b, d.bn(), 1000000);
			int us = mpz_get_si(b);
			mpz_tdiv_q_ui(b_tmp, d.bn(), 1000000);

			mpz_mod_ui(b, b_tmp, 3600);
			int s = mpz_get_si(b);
			mpz_tdiv_q_ui(b_tmp, b_tmp, 3600);

			int h = mpz_get_si(b_tmp);

			mpz_clear(b);
			mpz_clear(b_tmp);

			return new orcaTime(m_td 
								+ hours(h) 
								+ seconds(s) 
								+ microseconds(us));
			}

		case TYPE_OBJ:
			orcaObject* op = vm->get_param(0).Object();
			if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
				return new orcaTime(m_td + tp->m_td);
			}
			/* add date, datetime is defined in orcaDate, orcaDatetime */
		}

		return NIL;
	}

	orcaData ex_sub(orcaVM* vm, int n) 
	{
		orcaData d = vm->get_param(0);
		int i;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			return new orcaTime(m_td - microseconds(i));

		case TYPE_BIGNUM: {
			mpz_t b, b_tmp;
			mpz_init(b);
			mpz_init(b_tmp);

			mpz_mod_ui(b, d.bn(), 1000000);
			int us = mpz_get_si(b);
			mpz_tdiv_q_ui(b_tmp, d.bn(), 1000000);

			mpz_mod_ui(b, b_tmp, 3600);
			int s = mpz_get_si(b);
			mpz_tdiv_q_ui(b_tmp, b_tmp, 3600);

			int h = mpz_get_si(b_tmp);

			mpz_clear(b);
			mpz_clear(b_tmp);

			return new orcaTime(m_td 
								- hours(h) 
								- seconds(s) 
								- microseconds(us));
			}

		case TYPE_OBJ:
			orcaObject* op = vm->get_param(0).Object();
			if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
				return new orcaTime(m_td - tp->m_td);
			}
		}

		return NIL;
	}

	orcaData ex_mul(orcaVM* vm, int n) 
	{
		orcaData d = vm->get_param(0);
		int i;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			return new orcaTime(m_td * i);
		}

		return NIL;
	}

	orcaData ex_div(orcaVM* vm, int n) 
	{
		orcaData d = vm->get_param(0);
		int i;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			return new orcaTime(m_td / i);
		}

		return NIL;
	}

	orcaData ex_lt(orcaVM* vm, int n) 
	{
		orcaObject* op = vm->get_param(0).Object();
		
		if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
			return m_td < tp->m_td;
		}

		return NIL;
	}

	orcaData ex_eq(orcaVM* vm, int n) 
	{
		orcaObject* op = vm->get_param(0).Object();
		
		if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
			return m_td == tp->m_td;
		}

		return NIL;
	}

	orcaData ex_hours(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();
		return new orcaTime(i,0,0,0);
	}

	orcaData ex_minutes(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();
		return new orcaTime(0,i,0,0);
	}

	orcaData ex_seconds(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();
		return new orcaTime(0,0,i,0);
	}

	orcaData ex_microseconds(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();
		return new orcaTime(0,0,0,i);
	}

	orcaData ex_time_of_day(orcaVM* vm, int n) 
	{
		return new orcaTime(microsec_clock::local_time().time_of_day());
	}

	orcaData ex_totalseconds(orcaVM* vm, int n)
	{
		int sec = m_td.total_seconds();
		int us = (int)m_td.fractional_seconds();

		if (abs(sec) > 1000) {
			mpz_t b;
			mpz_init(b);
			mpz_set_si(b, sec);
			mpz_mul_ui(b, b, 1000000);
			mpz_add_ui(b, b, us);
			mpz_clear(b);
			return b;
		}
		else {
			return sec*1000000 + us;
		}
	}

	void init_by_string(string& format)
	{
		try {
			m_td = duration_from_string(format);
		}
		catch (...) {
			throw orcaException(NULL, "orca.format", "invalid time format");
		}
	}

	virtual string pack_save()
	{
		string str = ",";
		string_(NULL, str);
		return str;
	}

	virtual void pack_load(string& str)
	{
		init_by_string(str);
	}


private:
	time_duration m_td;
	static cp_map<orcaData>::Type m_static_time;
};

#endif

