/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaStopWatch.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SWATCH
#define _DEF_ORCA_SWATCH

#include "porting.h"

#ifdef WINDOWS
#else
#include <sys/time.h>
#include <unistd.h>
#endif


#include "orcaObject.h"


class orcaStopWatch : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaStopWatch);

	orcaStopWatch()
	{
		set_name("stopwatch");
		insert_native_function("start", (object_fp)&orcaStopWatch::ex_start);
		insert_native_function("elapse", (object_fp)&orcaStopWatch::ex_elapse);
		insert_native_function("scope_start", (object_fp)&orcaStopWatch::ex_start);
		insert_native_function("scope_end", (object_fp)&orcaStopWatch::ex_lap);
		insert_native_function("lap", (object_fp)&orcaStopWatch::ex_lap);
		insert_native_function("title", (object_fp)&orcaStopWatch::ex_title);

		m_tv.tv_sec = 0;
		m_tv.tv_usec = 0;
	}

	orcaData ex_start(orcaVM* vm, int n) 
	{
		gettimeofday(&m_tv, NULL);
		return NIL;
	}

	orcaData ex_elapse(orcaVM* vm, int n) 
	{
		timeval tv;
		gettimeofday(&tv, NULL);

		long long usec = diff(m_tv, tv);

		// for speed (orcaData(int), not orcaData(long long))
		if (usec < INT_MAX) {
			return (int)usec;
		}

		return usec;
	}

	orcaData ex_title(orcaVM* vm, int n) 
	{
		if (n == 0) {
			m_title = "";
		}
		else {
			m_title = vm->get_param(0).String();
		}

		return this;
	}

	orcaData ex_lap(orcaVM* vm, int n) 
	{
		timeval tv;
		gettimeofday(&tv, NULL);

		long long usec = diff(m_tv, tv);
		int day, hour, min, sec, ms, us;
		decode(usec, day, hour, min, sec, ms, us);

		const char* cp = m_title.c_str();
		printf("%s", cp ? cp : "");

		if (n > 0) {
			string& title = vm->get_param(0).String();
			printf("%s", title.c_str());
		}

		bool flag = false;
		if (day)	flag = true;
		if (flag)	printf("%d day, ", day);
		if (hour)	flag = true;
		if (flag)	printf("%d hour, ", hour);
		if (min)	flag = true;
		if (flag)	printf("%d min, ", min);
		if (sec)	flag = true;
		if (flag)	printf("%d sec, ", sec);
		if (ms)		flag = true;
		if (flag)	printf("%d ms, ", ms);
		printf("%d us\n", us);

		return NIL;
	}

private:
	long long diff(timeval& start, timeval&end)
	{
		long long sec = end.tv_sec - start.tv_sec;
		return (sec * 1000 * 1000) + (end.tv_usec - start.tv_usec);
	}

	void decode(long long diff, 
				int& day, int& hour, int& min, 
				int& sec, int& ms, int& us)
	{
		day = hour = min = sec = ms = us = 0;

		us = diff % 1000;
		diff /= 1000;
		if (diff == 0) return;

		ms = diff % 1000;
		diff /= 1000;
		if (diff == 0) return;

		sec = diff % 60;
		diff /= 60;
		if (diff == 0) return;

		min = diff % 60;
		diff /= 60;
		if (diff == 0) return;

		hour = diff % 24;
		diff /= 24;
		if (diff == 0) return;
		
		day = (int)diff;
	}

	timeval m_tv;
	string m_title;
};

#endif



