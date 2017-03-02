/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  kyString.cpp - string type

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include <limits.h>

#include <boost/lexical_cast.hpp>

using namespace boost;

#include "kyString.h"

static string g_white_string = " \t\r\n";


int kyString::find(const string& str, const string& what, int s, int e)/*{{{*/
{	
	int r = str.find(what, s);
	if (r > e) {
		r = -1;
	}

	return r;
}
/*}}}*/

bool kyString::find(const string& str, regex& re, mr_t& mr, int s, int e)/*{{{*/
{	
	if (e > str.length())
		e = str.length();

	string::const_iterator start, end; 
	start = str.begin() + s;
	end = str.begin() + e;

	if ( regex_search(start, end, mr, re) ) {
		return true;
	}
	
	return false;
}
/*}}}*/

bool kyString::starts_with(const string& str, const string& s) /*{{{*/
{
	return strncmp(str.c_str(), s.c_str(), s.length()) == 0 ? true : false;
}
/*}}}*/

bool kyString::starts_with(const string& str, regex& r) /*{{{*/
{	
	match_results<string::const_iterator> mr;
	string::const_iterator start, end; 
	start = str.begin();
	end = str.end();

	bool d = false;
	if ( regex_search(start, end, mr, r) ) {
		if (mr[0].first == str.begin()) {
			d = true;
		}
	}

	return d;
}
/*}}}*/

bool kyString::ends_with(const string& str, const string& s)/*{{{*/
{	
	int l1 = str.length();
	int l2 = s.length();
	if (l1 < l2) return false;
	return strncmp(str.c_str() + (l1-l2), s.c_str(), l2) == 0 ? true : false;
}
/*}}}*/

bool kyString::ends_with(const string& str, regex& re)/*{{{*/
{	
	match_results<string::const_iterator> mr;
	string::const_iterator start, end; 
	start = str.begin();
	end = str.end();

	bool d = false;
	do {
		if ( regex_search(start, end, mr, re) ) {
			if (mr[0].second == str.end()) {
				d = true;
				break;
			}
			start = mr[0].second;
		}
		else {
			break;
		}
	} while(true);

	return d;
}
/*}}}*/

int kyString::hash(const string& str, int mod)/*{{{*/
{	
	unsigned int val = 0;
	int i=0;

	while (i < str.length()) {
		val += str[i++];
	}

	if (mod > 0) {
		val %= mod;
	}

	return val;
}
/*}}}*/

vector<string> kyString::split(const string& str, const string& by) /*{{{*/
{	
	vector<string> vs;
	int start = 0;

	do {
		int r = str.find(by, start);
		if (r < 0) {
			vs.push_back(str.substr(start));
			break;
		}

		if (r-start == 0) { } // nothing
		else vs.push_back(str.substr(start, r - start));
		start = r+by.length();
	} while(true);

	return vs;
}
/*}}}*/

vector<string> kyString::split(const string& str, regex& re) /*{{{*/
{	
	vector<string> vs;
	int start = 0;

	do {
		match_results<string::const_iterator> mr;
		string::const_iterator siter, eiter; 
		siter = str.begin() + start;
		eiter = str.begin() + str.length();

		if ( regex_search(siter, eiter, mr, re) ) {
			if ((mr[0].first - str.begin() - start) == 0) { } // nothing 
			else vs.push_back(str.substr(start, (mr[0].first - str.begin()) - start));
		}
		else {
			vs.push_back(str.substr(start));
			break;
		}

		start = (mr[0].second - str.begin());
	} while(true);

	return vs;
}
/*}}}*/

vector<int> kyString::find_all(const string& str, const string& p, int s, int e) /*{{{*/
{
	vector<int> v;
	int start = s;

	do {
		int r = find(str, p, start, e);
		if (r < 0)
			break;

		v.push_back(r);
		start = r+1;
	} while(true);

	return v;
}
/*}}}*/

vector<mr_t> kyString::find_all(const string& str, regex& p, int s, int e) /*{{{*/
{
	vector<mr_t> v;
	int start = s;

	do {
		mr_t mr;
		if (!find(str, p, mr, start, e))
			break;

		v.push_back(mr);
		start = mr[0].second - str.begin();

	} while(true);

	return v;
}
/*}}}*/

string kyString::replace(const string& src, const string& from, const string&to, int s, int e)/*{{{*/
{	
	string str = src;

	int r = s;
	do {
		r = str.find(from, r );
		if (r > e || r < 0) break;

		str.replace(r, from.length(), to);
		r += to.length();
	} while(true);

	return str;
}
/*}}}*/

string kyString::replace(const string& src, regex& re, const string& to, int s, int e)/*{{{*/
{	
	string str = src;

	if (s < 0) s = 0;
	if (s > str.length()) s = str.length();
	if (e > str.length()) e = str.length();

	if (s==0 && e == str.length()) {
		str = regex_replace(str, re, to, match_default | format_all);
	}
	else {
		string::const_iterator start, end; 
		start = str.begin() + s;
		end = str.begin() + e;
		stringstream result;
		ostream_iterator<char, char> oi(result);
	 
		regex_replace(oi, start, end, re, to, 
					  match_default | format_all);

		str = str.substr(0, s) + result.str() + str.substr(e);
	}

	return str;
}
/*}}}*/

string kyString::strip(const string& str, const string& what)/*{{{*/
{ 
	int start = str.find_first_not_of(what);
	int end = str.find_last_not_of(what);

	if (start < 0 || end < 0) {
		return "";
	}

	return str.substr(start, end-start+1);
}
/*}}}*/

string kyString::lstrip(const string& str, const string& what)/*{{{*/
{ 
	int start = str.find_first_not_of(what);

	if (start < 0) {
		return "";
	}

	return str.substr(start);
}
/*}}}*/

string kyString::rstrip(const string& str, const string& what)/*{{{*/
{ 
	int end = str.find_last_not_of(what);

	if (end < 0) {
		return "";
	}

	return str.substr(0, end+1);
}
/*}}}*/

string kyString::strip(const string& s)/*{{{*/
{
	return strip(s, g_white_string);
}
/*}}}*/

string kyString::to_escape(const string& s)/*{{{*/
{
	string src = s;
	src = replace(src, "\t", "\\t");
	src = replace(src, "\n", "\\n");
	src = replace(src, "\r", "\\r");
	src = replace(src, "\b", "\\b");

	return src;
}
/*}}}*/

string kyString::from_escape(const string& s)/*{{{*/
{
	string src = s;
	src = replace(src, "\\t", "\t");
	src = replace(src, "\\n", "\n");
	src = replace(src, "\\r", "\r");
	src = replace(src, "\\b", "\b");

	return src;
}
/*}}}*/

