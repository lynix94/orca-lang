/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaOnce.h - handling once block

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_ONCE
#define _DEF_ORCA_ONCE

#include <vector>
#include <map>
#include <set>

#include "orcaData.h"
#include "orcaMap.h"
class orcaObject;

using namespace std;

class orcaOnce
{
public:
	orcaOnce() {}
	~orcaOnce();

	typedef map<void*, orcaMap*> once_map;

	bool find(orcaObject* module, int id, orcaData& out);
	void add(orcaObject* module, int id, orcaData val);
	void load(orcaObject* module, orcaMap* mp);
	void reg(orcaObject* module, string& path);
	
private:
	int m_id;
	once_map m_map;
	map<void*, string> m_paths;
	set<void*> m_changed;
};

#endif


