/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaOnce.cpp - handling once block

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "porting.h"

#include "orcaOnce.h"
#include "orcaObject.h"
#include "orcaPack.h"

orcaOnce::~orcaOnce()
{
	once_map::iterator mi = m_map.begin();
	for (; mi != m_map.end(); ++mi) {
		orcaObject* op = (orcaObject*)mi->first;
			if (m_changed.find(op) != m_changed.end()) {
			string name = m_paths[op];
			
			portFile file;
			if (file.create(name)) {
				string buff = g_pack->save(mi->second);
				file.writes(buff);
				file.close();
			}
		}
		
		delete mi->second;
	}
}

bool orcaOnce::find(orcaObject* module, int id, orcaData& out)
{
	once_map::iterator mi = m_map.find(module);
	if (mi == m_map.end()) {
		return false;
	}

	orcaMap* ip = mi->second;
	orcaData key = id;
	if (ip->has_key(key)) {
		out = ip->at(key);
		return true;
	}

	return false;
}

void orcaOnce::add(orcaObject* module, int id, orcaData val)
{
	orcaMap* ip;
	once_map::iterator mi = m_map.find(module);
	if (mi == m_map.end()) {
		ip = new orcaMap;
		m_map[module] = ip;
	}
	else {
		ip = mi->second;
	}

	orcaData key = id;
	(*ip).update(key, val);

	m_changed.insert(module);
}

void orcaOnce::load(orcaObject* module, orcaMap* mp)
{
	m_map[module] = mp;
}

void orcaOnce::reg(orcaObject* op, string& path)
{
	m_paths[op] = path;
}
	

