/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaDatetime.h -

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_DATETIME
#define _DEF_ORCA_DATETIME


#include "porting.h"
#include "orcaObject.h"
#include "orcaException.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::gregorian;
using namespace boost::posix_time;


class orcaDatetime : public orcaObject 
{
friend class orcaDate;
public:
	DEFAULT_NATIVE_DEFINE(orcaDatetime);

	void __init();
	orcaDatetime();
	orcaDatetime(ptime t);
	orcaDatetime(time_t t);
	ptime& get_ptime();

	virtual void string_(orcaVM* vm, string& str);

	orcaData ex_init(orcaVM* vm, int n);
	orcaData ex_now(orcaVM* vm, int n);
	orcaData ex_date(orcaVM* vm, int n); 
	orcaData ex_time(orcaVM* vm, int n); 

	orcaData ex_add(orcaVM* vm, int n); 
	orcaData ex_sub(orcaVM* vm, int n); 
	orcaData ex_lt(orcaVM* vm, int n); 
	orcaData ex_eq(orcaVM* vm, int n); 

	void init_by_string(string& format)
	{
		try {
			if (format.length() <= 15) {
				m_ptime = from_iso_string(format);
			}
			else {
				m_ptime = time_from_string(format);
			}
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
	ptime m_ptime;
	static cp_map<orcaData>::Type m_static_datetime;
};

#endif

