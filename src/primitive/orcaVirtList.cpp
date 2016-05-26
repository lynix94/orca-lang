/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaVirtList.cpp - virtual list for decode

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaVirtList.h"
#include "orcaException.h"

// internal
orcaData& orcaVirtList::at(int idx)
{
	if (idx >= 0)
		return m_lp->at(idx + m_head);

	int len = m_lp->size();
	idx = len + idx;
	if (idx < m_head) {
		throw orcaException(NULL, "orca.index", string("out of index. size: ") + 
				boost::lexical_cast<string>(len - m_head) + " index: " + 
				boost::lexical_cast<string>(idx + len));
	}
	
	return m_lp->at(idx);
}

orcaListIter orcaVirtList::begin() 
{
	return m_begin;
}

orcaListIter orcaVirtList::end() 
{
	return m_lp->end();
}

int orcaVirtList::size()
{
	return m_lp->size() - m_head;
}

void orcaVirtList::init(orcaList* lp)
{
	m_lp = lp;
	m_head = 1;

	m_begin = lp->begin();
	++m_begin;

	lp->rc_inc();
}

orcaVirtList* orcaVirtList::cut_head()
{
	orcaVirtList* lp = new orcaVirtList();
	lp->m_lp = m_lp;
	m_lp->rc_inc();

	lp->m_begin = m_begin;
	++lp->m_begin;

	lp->m_head = m_head + 1;
	return lp;
}

orcaData orcaVirtList::slice(int start, int end, bool include_right) 
{
	int len = size();
	bool reverse;

	if (start < 0) start += len;
	if (end < 0) end += len;

	if (start <= end) {
		reverse = false;
	}
	else {
		reverse = true;
		int tmp = start;
		start = end;
		end = tmp;
	}

	return m_lp->slice(start + m_head, end, include_right);
}

