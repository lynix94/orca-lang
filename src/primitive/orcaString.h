/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaString.h - string type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_STRING
#define _DEF_ORCA_STRING

#include <boost/regex.hpp>

#include "orcaObject.h"
#include "orcaTuple.h"


class LIBORCA_API orcaString : public orcaObject
{
public:
	orcaString();

	orcaData length(orcaVM* vm, string& str);
	orcaData find(orcaVM* vm, string& str);
	orcaData find_all(orcaVM* vm, string& str);
	orcaData strip(orcaVM* vm, string& str);
	orcaData lstrip(orcaVM* vm, string& str);
	orcaData rstrip(orcaVM* vm, string& str);
	orcaData substr(orcaVM* vm, string& str);
	orcaData integer(orcaVM* vm, string& str);
	orcaData float_(orcaVM* vm, string& str);
	orcaData to_string(orcaVM* vm, string& str);
	orcaData replace(orcaVM* vm, string& str);
	orcaData starts_with(orcaVM* vm, string& str);
	orcaData ends_with(orcaVM* vm, string& str);
	orcaData hash(orcaVM* vm, string& str);
	orcaData split(orcaVM* vm, string& str);
	orcaData push_back(orcaVM* vm, string& str);
	orcaData char_(orcaVM* vm, string& str);
	orcaData upper(orcaVM* vm, string& str);
	orcaData lower(orcaVM* vm, string& str);

	static string slice(string& s, int start, int end, bool include_right);

private:
	orcaTuple* _find_regex(string& str, boost::regex& re, int s, int e);
};

extern orcaString g_string;

#endif

