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

	orcaData ex_add(orcaVM* vm, string& str, int param_n);
	orcaData ex_mul(orcaVM* vm, string& str, int param_n);
	orcaData ex_mod(orcaVM* vm, string& str, int param_n);
	orcaData ex_gt(orcaVM* vm, string& str, int param_n);
	orcaData ex_ge(orcaVM* vm, string& str, int param_n);
	orcaData ex_lt(orcaVM* vm, string& str, int param_n);
	orcaData ex_le(orcaVM* vm, string& str, int param_n);
	orcaData ex_eq(orcaVM* vm, string& str, int param_n);
	orcaData ex_neq(orcaVM* vm, string& str, int param_n);
	orcaData ex_length(orcaVM* vm, string& str, int param_n);
	orcaData ex_find(orcaVM* vm, string& str, int param_n);
	orcaData ex_find_all(orcaVM* vm, string& str, int param_n);
	orcaData ex_strip(orcaVM* vm, string& str, int param_n);
	orcaData ex_lstrip(orcaVM* vm, string& str, int param_n);
	orcaData ex_rstrip(orcaVM* vm, string& str, int param_n);
	orcaData ex_substr(orcaVM* vm, string& str, int param_n);
	orcaData ex_integer(orcaVM* vm, string& str, int param_n);
	orcaData ex_float(orcaVM* vm, string& str, int param_n);
	orcaData ex_string(orcaVM* vm, string& str, int param_n);
	orcaData ex_repr(orcaVM* vm, string& str, int param_n);
	orcaData ex_replace(orcaVM* vm, string& str, int param_n);
	orcaData ex_starts_with(orcaVM* vm, string& str, int param_n);
	orcaData ex_ends_with(orcaVM* vm, string& str, int param_n);
	orcaData ex_hash(orcaVM* vm, string& str, int param_n);
	orcaData ex_split(orcaVM* vm, string& str, int param_n);
	orcaData ex_push_back(orcaVM* vm, string& str, int param_n);
	orcaData ex_char(orcaVM* vm, string& str, int param_n);
	orcaData ex_upper(orcaVM* vm, string& str, int param_n);
	orcaData ex_lower(orcaVM* vm, string& str, int param_n);
	orcaData ex_list_format(orcaVM* vm, string& str, int param_n);

	static string slice(string& s, int start, int end, bool include_right);

private:
	orcaTuple* _find_regex(string& str, boost::regex& re, int s, int e);
};

extern orcaString g_string;

#endif

