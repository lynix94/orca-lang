/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaPure.cpp - handling pure function

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaPure.h"
#include "orcaObject.h"
#include "orcaStack.h"
#include "orcaUtil.h"

orcaPure::~orcaPure()
{

	lru_t r;
	while(m_lru.victimize(&r)) {
		for (int i=0; i<r.param.size(); i++)
			r.param[i].rc_dec();

		r.result.rc_dec();
	}
}

bool orcaPure::find(orcaObject* op, orcaStack* sp, int n, orcaData& ret)
{
	lru_t l;
	l.op = op;
	for (int i=0; i<n; i++)
		l.param.push_back(sp->at(i));

	m_mutex.lock();
	orca_lru<lru_t, lru_t>::lru_item* i = m_lru.touch(l);
	if (i == NULL) {
		m_mutex.unlock();
		return false;
	}

	ret = i->item.result;
	m_mutex.unlock();
	return true;;
}

void orcaPure::add(orcaObject* op, vector<orcaData>& param, orcaData result)
{
	m_mutex.lock();

	lru_t l;
	l.op = op;
	l.param = param;
	l.result = result;
	m_lru.insert(l, l);

	for (int i=0; i<param.size(); i++)
		param[i].rc_inc();

	l.result.rc_inc();

	if (m_lru.size() > m_max) {
		lru_t r;
		if (m_lru.victimize(&r)) {
			for (int i=0; i<r.param.size(); i++)
				r.param[i].rc_dec();

			r.result.rc_dec();
		}
	}
	m_mutex.unlock();
}

