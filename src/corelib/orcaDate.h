/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaDate.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_DATE
#define _DEF_ORCA_DATE

#include "porting.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;


#include "orcaObject.h"
#include "orcaDatetime.h"
#include "orcaTime.h"

class orcaDateDuration : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaDateDuration);

	orcaDateDuration(int y, int m, int d, int w) : years(y), months(m), days(d), weeks(w)
	{
		set_name("dateduration");
		insert_native_function("+", (object_fp)&orcaDateDuration::ex_add);
		insert_native_function("-", (object_fp)&orcaDateDuration::ex_sub);
		insert_native_function("*", (object_fp)&orcaDateDuration::ex_mul);
		insert_native_function("/", (object_fp)&orcaDateDuration::ex_div);
		insert_native_function("==", (object_fp)&orcaDateDuration::ex_eq);
	}

	orcaData ex_add(orcaVM* vm, int n) 
	{
		int i;
		orcaData d = vm->get_param(0);
		orcaDateDuration* dp = NULL;
		orcaObject* op;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			dp = new orcaDateDuration(years, months, days, weeks);
			dp->days += i;
			return dp;

		case TYPE_OBJ:
			op = vm->get_param(0).Object();
			if (orcaDateDuration* ddp = dynamic_cast<orcaDateDuration*>(op)) {
				dp = new orcaDateDuration(years, months, days, weeks);
				dp->years += ddp->years;
				dp->months += ddp->months;
				dp->days += ddp->days;
				dp->weeks += ddp->weeks;
				return dp;
			}
		}

		return NIL;
	}

	orcaData ex_sub(orcaVM* vm, int n) 
	{
		int i;
		orcaData d = vm->get_param(0);
		orcaDateDuration* dp = NULL;
		orcaObject* op;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			dp = new orcaDateDuration(years, months, days, weeks);
			dp->days -= i;
			return dp;

		case TYPE_OBJ:
			op = vm->get_param(0).Object();
			if (orcaDateDuration* ddp = dynamic_cast<orcaDateDuration*>(op)) {
				dp = new orcaDateDuration(years, months, days, weeks);
				dp->years -= ddp->years;
				dp->months -= ddp->months;
				dp->days -= ddp->days;
				dp->weeks -= ddp->weeks;
				return dp;
			}
		}

		return NIL;
	}

	orcaData ex_mul(orcaVM* vm, int n) 
	{
		int i;
		orcaData d = vm->get_param(0);
		orcaDateDuration* dp = NULL;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			dp = new orcaDateDuration(years, months, days, weeks);
			dp->years *= i;
			dp->months *= i;
			dp->weeks *= i;
			dp->days *= i;
			return dp;
		}

		return NIL;
	}

	orcaData ex_div(orcaVM* vm, int n) 
	{
		int i;
		orcaData d = vm->get_param(0);
		orcaDateDuration* dp = NULL;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			dp = new orcaDateDuration(years, months, days, weeks);
			dp->years /= i;
			dp->months /= i;
			dp->weeks /= i;
			dp->days /= i;
			return dp;
		}

		return NIL;
	}

	orcaData ex_eq(orcaVM* vm, int n) 
	{
		orcaObject* op = vm->get_param(0).Object();
		
		if (orcaDateDuration* ddp = dynamic_cast<orcaDateDuration*>(op)) {
			return	(years == ddp->years) &&
					(months == ddp->months) &&
					(days == ddp->days) &&
					(weeks == ddp->weeks);
		}

		return NIL;
	}

	virtual void string_(orcaVM* vm, string& str)
	{
		if (years != 0) {
			str += boost::lexical_cast<string>(years) + " years ";
		}
		if (months != 0) {
			str += boost::lexical_cast<string>(months) + " months ";
		}
		if (weeks != 0) {
			str += boost::lexical_cast<string>(weeks) + " weeks ";
		}
		if (days != 0) {
			str += boost::lexical_cast<string>(days) + " days ";
		}
	}

	int years;
	int months;
	int days;
	int weeks;
};


class orcaDate : public orcaObject 
{
friend class orcaDatetime;
friend class orcaDateDuration;
friend class orcaTime;

public:
	DEFAULT_NATIVE_DEFINE(orcaDate);

	void __init()
	{
		set_name("date");
		insert_static_native_function("today", (object_fp)&orcaDate::ex_today);
		insert_native_function("init", (object_fp)&orcaDate::ex_init);

		insert_native_function(".attr", (object_fp)&orcaDate::ex_get);
		insert_native_function("+", (object_fp)&orcaDate::ex_add);
		insert_native_function("-", (object_fp)&orcaDate::ex_sub);
		insert_native_function("<", (object_fp)&orcaDate::ex_lt);
		insert_native_function("==", (object_fp)&orcaDate::ex_eq);

		insert_static_native_function("years", (object_fp)&orcaDate::ex_years);
		insert_static_native_function("months", (object_fp)&orcaDate::ex_months);
		insert_static_native_function("days", (object_fp)&orcaDate::ex_days);
		insert_static_native_function("weeks", (object_fp)&orcaDate::ex_weeks);
	}

	orcaDate()
	{
		__init();
	}

	orcaDate(date d)
	{
		__init();
		m_date = d;
	}

	virtual void string_(orcaVM* vm, string& str)
	{
		str += to_iso_extended_string(m_date);
	}

	orcaData ex_today(orcaVM* vm, int n) 
	{
		return new orcaDate(day_clock::local_day());
	}

	orcaData ex_init(orcaVM* vm, int n) 
	{
		if (n<0) {
			return this;
		}

		string format = vm->get_param(0).String();
		init_by_string(format);
		
		return this;
	}

	orcaData ex_get(orcaVM* vm, int n) 
	{
		string name = vm->get_param(0).String();
		if (name == "year") {
			return (int)m_date.year();
		}
		else if (name == "month") {
			return (int)m_date.month();
		}
		else if (name == "day") {
			return (int)m_date.day();
		}
		else if (name == "day_of_week") {
			return (int)m_date.day_of_week();
		}
		else if (name == "day_of_year") {
			return (int)m_date.day_of_year();
		}

		throw orcaException(vm, "orca.lang", "member not exists");

		return NIL;
	}

	orcaData ex_add(orcaVM* vm, int n) 
	{
		int i;
		orcaData d = vm->get_param(0);
		orcaDate* dp = NULL;
		orcaObject* op;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			dp = new orcaDate(m_date);
			dp->m_date += days(i);
			return dp;

		case TYPE_OBJ:
			op = vm->get_param(0).Object();
			if (orcaDateDuration* ddp = dynamic_cast<orcaDateDuration*>(op)) {
				dp = new orcaDate(m_date);
				dp->m_date += years(ddp->years);
				dp->m_date += months(ddp->months);
				dp->m_date += days(ddp->days);
				dp->m_date += weeks(ddp->weeks);
				return dp;
			}
			else if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
				return new orcaDatetime(ptime(m_date, tp->m_td));
			}
		}

		return NIL;
	}

	orcaData ex_sub(orcaVM* vm, int n) 
	{
		int i;
		orcaData d = vm->get_param(0);
		orcaDate* dp = NULL;
		orcaObject* op = NULL;

		switch(d.get_type())
		{
		case TYPE_INT:
		case TYPE_REAL:
		case TYPE_STR:
			i = d.Integer();
			dp = new orcaDate(m_date);
			dp->m_date -= days(i);
			return dp;

		case TYPE_OBJ:
			op = vm->get_param(0).Object();
			if (orcaDateDuration* ddp = dynamic_cast<orcaDateDuration*>(op)) {
				dp = new orcaDate(m_date);
				dp->m_date -= years(ddp->years);
				dp->m_date -= months(ddp->months);
				dp->m_date -= days(ddp->days);
				dp->m_date -= weeks(ddp->weeks);
				return dp;
			}
			else if (orcaDate* dp2 = dynamic_cast<orcaDate*>(op)) {
				return (int)(m_date - dp2->m_date).days();
			}
			else if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
				return new orcaDatetime(ptime(m_date, tp->m_td.invert_sign()));
			}
		}

		return NIL;
	}

	orcaData ex_lt(orcaVM* vm, int n) 
	{
		orcaObject* op = vm->get_param(0).Object();
		
		if (orcaDate* dp = dynamic_cast<orcaDate*>(op)) {
			return m_date < dp->m_date;
		}
		else if (orcaDatetime* dtp = dynamic_cast<orcaDatetime*>(op)) {
			return ptime(m_date, hours(0)) < dtp->m_ptime;
		}

		return NIL;
	}

	orcaData ex_eq(orcaVM* vm, int n) 
	{
		orcaObject* op = vm->get_param(0).Object();
		
		if (orcaDate* dp = dynamic_cast<orcaDate*>(op)) {
			return m_date == dp->m_date;
		}
		else if (orcaDatetime* dtp = dynamic_cast<orcaDatetime*>(op)) {
			return ptime(m_date, hours(0)) == dtp->m_ptime;
		}

		return NIL;
	}

	orcaData ex_years(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();

		return new orcaDateDuration(i,0,0,0);
	}

	orcaData ex_months(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();

		return new orcaDateDuration(0,i,0,0);
	}

	orcaData ex_days(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();

		return new orcaDateDuration(0,0,i,0);
	}

	orcaData ex_weeks(orcaVM* vm, int n) 
	{
		if (n<1) vm->need_param();

		int i = vm->get_param(0).Integer();

		return new orcaDateDuration(0,0,0,i);
	}

	void init_by_string(string& format)
	{
		try {
			if (format.length() > 8) {
				m_date = from_string(format);
			}
			else {
				m_date = from_undelimited_string(format);
			}
		}
		catch (...) {
			throw orcaException(NULL, "orca.format", "invalid date format");
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
	date m_date;
	static cp_map<orcaData>::Type m_static_date;
};

#endif

