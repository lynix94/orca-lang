/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  kyString.h - string type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_KY_STRING
#define _DEF_KY_STRING

#include <string>
#include <boost/regex.hpp>

using namespace std;

typedef match_results<string::const_iterator> mr_t;

class kyString
{
public:
	static int find(const string& src, const string& s,
					int start = 0, int end = INT_MAX);
	static bool find(const string& src, boost::regex& r, mr_t& mr,
					 int start = 0, int end = INT_MAX);

	static vector<int> find_all(const string& src, const string& s,
								int start = 0, int end = INT_MAX);
	static vector<mr_t> find_all(const string& src, boost::regex& r,
								 int start = 0, int end = INT_MAX);

	static string strip(const string& src);
	static string strip(const string& src, const string& s);
	static string strip(const string& src, boost::regex& r);
	static string lstrip(const string& src, const string& s);
	static string lstrip(const string& src, boost::regex& r);
	static string rstrip(const string& src, const string& s);
	static string rstrip(const string& src, boost::regex& r);

	static string replace(const string& str, const string& from,
						const string&to, int s = 0, int e = INT_MAX);
	static string replace(const string& str, boost::regex& re,
						const string&to, int s = 0, int e = INT_MAX);

	static bool starts_with(const string& src, const string& s);
	static bool starts_with(const string& src, boost::regex& r);

	static bool ends_with(const string& src, const string& s);
	static bool ends_with(const string& src, boost::regex& r);

	static int hash(const string& src, int mod = INT_MAX);

	static vector<string> chomp(const string& src, const string& s);
	static vector<string> chomp(const string& src, boost::regex& r);

	static string to_escape(const string& src);
	static string from_escape(const string& src);
};

#endif

