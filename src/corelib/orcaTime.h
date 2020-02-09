/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaTime.h - 

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_TIME
#define _DEF_ORCA_TIME

#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::gregorian;
using namespace boost::posix_time;

#include "porting.h"
#include "orcaObject.h"
#include "orcaException.h"

class orcaTimer;
class orcaTicker;

class orcaGlobalTimer
{
public:
	orcaGlobalTimer()
	{
		flag_quit = false;
	}

	void start()
	{
		mutex.lock();
		pthread_create(&tid, NULL, entry_point, this);
		cond.wait(&mutex);
		mutex.unlock();
	}

	void quit();

	static void* entry_point(void* vp)
	{
		orcaGlobalTimer* tp = (orcaGlobalTimer*)vp;
		tp->do_timer();
	}

	long long current_ns()
	{
		timeval tv;
		gettimeofday(&tv, NULL);
		return (tv.tv_sec * 1000*1000*1000) + (tv.tv_usec * 1000);
	}

	void do_timer();
	void push_timer(double time, orcaTimer* to);
	void pop_timer(orcaTimer* to);


	void push_timer_gc(orcaTimer* to)
	{
		mutex_gc.lock();
		timer_gc.push_back(to);
		mutex_gc.unlock();
	}

private:
	void push_timer_wo_lock(double time, orcaTimer* to);

	multimap<long long, orcaTimer*> timers;
	vector<orcaTicker*> tickers;

	portCond cond;
	portMutex mutex;
	pthread_t tid;
	bool flag_quit;

	portMutex mutex_gc;
	vector<orcaTimer*> timer_gc;
};

extern orcaGlobalTimer* g_timer;



class orcaTimer : public orcaObject 
{
public:
	orcaTimer(void* vp) {}

	virtual ~orcaTimer() 
	{
		if (!invalid) {
			g_timer->pop_timer(this);
		}
	}

	orcaObject* v_clone() {
		return new orcaTimer((void*)NULL);
	}

	orcaTimer(double tm)
	{
		__init();
		g_timer->push_timer(tm, this);
	}

	void __init()
	{
		set_name("timer");
		insert_native_function("stop", (object_fp)&orcaTimer::ex_stop);
		insert_native_function("reset", (object_fp)&orcaTimer::ex_reset);
		insert_native_function("size", (object_fp)&orcaTimer::ex_size);
		insert_native_function("->", (object_fp)&orcaTimer::ex_out);

		nano_ts = -1;
		invalid = false;
	}

	orcaData ex_stop(orcaVM* vm, int n) 
	{
		g_timer->pop_timer(this);
		return NIL;
	}

	orcaData ex_reset(orcaVM* vm, int n) 
	{
		double tmout = vm->get_param(0).Double();

		g_timer->pop_timer(this);
		g_timer->push_timer(tmout, this);
		return NIL;
	}

	orcaData ex_size(orcaVM* vm, int n) 
	{
		return nano_ts > 0 ? 1 : 0;
	}

	orcaData ex_out(orcaVM* vm, int n) 
	{
		long long ret = nano_ts;
		nano_ts = -1;

		return ret;
	}

	void alarm(long long ts)
	{
		nano_ts = ts;
		get_current_vm()->channel_signal(this);
	}

	void invalidate()
	{
		invalid = true;
		g_timer->push_timer_gc(this);
	}

	long long nano_ts;
	bool invalid;
};

class orcaTicker : public orcaTimer 
{
public:
	orcaTicker(void* vp) : orcaTimer(vp) {}

	virtual ~orcaTicker() 
	{
		if (!invalid) {
			g_timer->pop_timer(this);
		}
	}

	orcaObject* v_clone() {
		return new orcaTicker((void*)NULL);
	}

	orcaTicker(double tm) : orcaTimer((void*)NULL)
	{
		__init();
		interval = tm;
		g_timer->push_timer(tm, this);
	}

	void __init()
	{
		set_name("ticker");
		insert_native_function("stop", (object_fp)&orcaTimer::ex_stop);
		insert_native_function("size", (object_fp)&orcaTimer::ex_size);
		insert_native_function("->", (object_fp)&orcaTimer::ex_out);

		nano_ts = -1;
		invalid = false;
	}

	double interval;
};



class orcaTime : public orcaObject 
{
friend class orcaDatetime;
friend class orcaDate;
public:
	DEFAULT_NATIVE_DEFINE(orcaTime);

	void __init();

	orcaTime()
	{
		__init();
	}

	orcaTime(time_duration t)
	{
		__init();
		m_td = t;
	}

	orcaTime(int h, int m, int s, int us);

	virtual void string_(orcaVM* vm, string& str)
	{
		str += to_simple_string(m_td);
	}

	orcaData ex_sleep(orcaVM* vm, int n);
	orcaData ex_timer(orcaVM* vm, int n);
	orcaData ex_ticker(orcaVM* vm, int n);
	orcaData ex_init(orcaVM* vm, int n);
	orcaData ex_get(orcaVM* vm, int n);
	orcaData ex_add(orcaVM* vm, int n);
	orcaData ex_sub(orcaVM* vm, int n);
	orcaData ex_mul(orcaVM* vm, int n);
	orcaData ex_div(orcaVM* vm, int n);
	orcaData ex_lt(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);
	orcaData ex_total_seconds(orcaVM* vm, int n);

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

