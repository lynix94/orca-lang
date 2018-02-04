/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTime.cpp - 

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#include "orcaTime.h"

orcaGlobalTimer g_timer;

void orcaGlobalTimer::quit()
{
	mutex.lock();
	flag_quit = true;
	cond.signal();
	mutex.unlock();

	long long status = 0;
	pthread_join(tid, (void**)&status);
}


void orcaGlobalTimer::do_timer()
{
	long long nsec = -1;
	while(flag_quit == false) {
		mutex.lock();
		cond.wait(&mutex, nsec);
		if (flag_quit == true) {
			break;
		}

		long long cns = current_ns();

		multimap<long long, orcaTimer*>::iterator from = timers.begin();
		multimap<long long, orcaTimer*>::iterator to = timers.upper_bound(cns);
		for(; from != to; ++from) {
			from->second->alarm(cns);
			orcaTicker* tp = dynamic_cast<orcaTicker*>(from->second);
			if (tp != NULL) {
				tickers.push_back(tp);
			}
		}
		timers.erase(timers.begin(), to);

		for (int i=0; i<tickers.size(); i++) {
			orcaTicker* tp = tickers[i];
			push_timer_wo_lock(tp->interval, tp);
		}
		tickers.clear();

		nsec = -1;
		if (timers.empty() == false) {
			nsec = timers.begin()->first - cns;
		}
		mutex.unlock();
	}
}

void orcaGlobalTimer::push_timer(double time, orcaTimer* to)
{
	mutex.lock();
	long long rel = time * (1000*1000*1000);
	long long now = current_ns();
	long long abs = now + rel;

	if (abs > now) {
		timers.insert(make_pair(abs, to));
		cond.signal();
	}
	mutex.unlock();
}


void orcaGlobalTimer::push_timer_wo_lock(double time, orcaTimer* to)
{
	long long rel = time * (1000*1000*1000);
	long long now = current_ns();
	long long abs = now + rel;

	if (abs > now) {
		timers.insert(make_pair(abs, to));
	}
}

void orcaGlobalTimer::pop_timer(orcaTimer* to)
{
	mutex.lock();
	multimap<long long, orcaTimer*>::iterator it = timers.begin();
	for(; it != timers.end(); ++it) {
		if (it->second == to) {
			timers.erase(it);
			break;
		}
	}
	mutex.unlock();
}

orcaTime::orcaTime(int h, int m, int s, int us)
{
	__init();

	if (h) m_td += hours(h);
	if (m) m_td += minutes(m);
	if (s) m_td += seconds(s);
	if (us) m_td += microseconds(us);
}

void orcaTime::__init()
{
	set_name("time");
	insert_static_native_function("sleep", (object_fp)&orcaTime::ex_sleep);
	insert_static_native_function("timer", (object_fp)&orcaTime::ex_timer);
	insert_static_native_function("ticker", (object_fp)&orcaTime::ex_ticker);
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

orcaData orcaTime::ex_timer(orcaVM* vm, int n) 
{
	double tmout = vm->get_param(0).Double();
	orcaTimer* to = new orcaTimer(tmout);
	return to;
}

orcaData orcaTime::ex_ticker(orcaVM* vm, int n) 
{
	double tmout = vm->get_param(0).Double();
	orcaTicker* to = new orcaTicker(tmout);
	return to;
}

orcaData orcaTime::ex_sleep(orcaVM* vm, int n) 
{
	double tmout = 0;
	if (n > 0) {
		tmout = vm->get_param(0).Double();
	}

	port_nsleep(tmout * (1000*1000*1000));
	return NIL;
}

orcaData orcaTime::ex_init(orcaVM* vm, int n) 
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

orcaData orcaTime::ex_get(orcaVM* vm, int n) 
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

orcaData orcaTime::ex_add(orcaVM* vm, int n) 
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

orcaData orcaTime::ex_sub(orcaVM* vm, int n) 
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

orcaData orcaTime::ex_mul(orcaVM* vm, int n) 
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

orcaData orcaTime::ex_div(orcaVM* vm, int n) 
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

orcaData orcaTime::ex_lt(orcaVM* vm, int n) 
{
	orcaObject* op = vm->get_param(0).Object();
	
	if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
		return m_td < tp->m_td;
	}

	return NIL;
}

orcaData orcaTime::ex_eq(orcaVM* vm, int n) 
{
	orcaObject* op = vm->get_param(0).Object();
	
	if (orcaTime* tp = dynamic_cast<orcaTime*>(op)) {
		return m_td == tp->m_td;
	}

	return NIL;
}

orcaData orcaTime::ex_totalseconds(orcaVM* vm, int n)
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

