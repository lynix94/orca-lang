/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaListIter.h - list type iterator

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaListIter.h"
#include "orcaSbf.h"
#include "orcaException.h"

orcaListIter::orcaListIter(orcaList* lp, list<orcaData>::iterator li)
{
	m_lp = lp;
	m_timestamp = lp->get_timestamp();
	m_iter = li;
	m_type = LIST_STL;

	m_curr = 0;
}


orcaListIter::orcaListIter(orcaSbf* lp)
{
	m_lp = lp;
	m_timestamp = lp->get_timestamp();
	m_type = LIST_SBF;
	m_curr = 0;
}


orcaListIter orcaListIter::operator++(int dummy)
{
	if (valid() == false) {
		throw orcaException(NULL, "orca.list", "invalid iterator-timestamp");
	}

	orcaListIter iter = *this;
	switch(m_type)
	{
	case LIST_STL:
		++m_iter;
		break;

	case LIST_SBF:
		++m_curr;
		if (static_cast<orcaSbf*>(m_lp)->eof(m_curr)) {
			m_curr = -1;
		}
		break;
	}

	return iter;
}

orcaListIter& orcaListIter::operator++()
{
	if (valid() == false) {
		throw orcaException(NULL, "orca.list", "invalid iterator-timestamp");
	}

	switch(m_type)
	{
	case LIST_STL:
		++m_iter;
		break;

	case LIST_SBF:
		++m_curr;
		if (static_cast<orcaSbf*>(m_lp)->eof(m_curr)) {
			m_curr = -1;
		}

		break;
	}

	return *this;	
}

orcaListIter orcaListIter::operator--(int dummy)
{
	if (valid() == false) {
		throw orcaException(NULL, "orca.list", "invalid iterator-timestamp");
	}

	orcaListIter iter = *this;
	switch(m_type)
	{
	case LIST_STL:
		--m_iter;
		break;

	case LIST_SBF:
		--m_curr;
		if (static_cast<orcaSbf*>(m_lp)->eof(m_curr)) {
			m_curr = -1;
		}

		break;
	}

	return iter;
}

orcaListIter& orcaListIter::operator--()
{
	if (valid() == false) {
		throw orcaException(NULL, "orca.list", "invalid iterator-timestamp");
	}

	switch(m_type)
	{
	case LIST_STL:
		--m_iter;
		break;

	case LIST_SBF:
		--m_curr;
		if (static_cast<orcaSbf*>(m_lp)->eof(m_curr)) {
			m_curr = -1;
		}
		break;
	}

	return *this;
}

orcaData& orcaListIter::operator*()
{
	if (valid() == false) {
		throw orcaException(NULL, "orca.list", "invalid iterator-timestamp");
	}

	switch(m_type)
	{
	case LIST_STL:
		return *m_iter;
		break;

	case LIST_SBF:
		return static_cast<orcaSbf*>(m_lp)->at(m_curr);
		break;
	}

	return NIL;
}

bool orcaListIter::operator==(const orcaListIter& rhs)
{
	switch(m_type)
	{
	case LIST_STL:
		return this->m_iter == rhs.m_iter;
		break;

	case LIST_SBF:
		return this->m_curr == rhs.m_curr;
		break;
	}

	return false;
}

bool orcaListIter::operator!=(const orcaListIter& rhs)
{
	return !(*this == rhs);
}


void orcaListIter::set_idx(int idx)
{
	m_curr = idx;
}

LIST_TYPE orcaListIter::get_type()
{
	return m_type;
}

bool orcaListIter::valid()
{
	if (m_timestamp < m_lp->get_timestamp()) {
		return false;
	}

	return true;
}


void orcaListIter::raw_erase()
{
	if (valid() == false) {
		throw orcaException(NULL, "orca.list", "invalid iterator-timestamp");
	}

	if (m_type != LIST_STL) {
		throw orcaException(NULL, "orca.list", "invalid erase");
	}

	if (m_iter == m_lp->m_value.end()) {
		throw orcaException(NULL, "orca.list", "invalid iterator");
	}

	list<orcaData>::iterator old = m_iter++;

	(*old).rc_dec();
	m_lp->m_value.erase(old);
	m_lp->inc_timestamp();
	m_timestamp++;
}

void orcaListIter::raw_insert(orcaData d)
{
	if (valid() == false) {
		throw orcaException(NULL, "orca.list", "invalid iterator-timestamp");
	}

	if (m_type != LIST_STL) {
		throw orcaException(NULL, "orca.list", "invalid insert");
	}
	
	d.rc_inc();
	m_lp->m_value.insert(m_iter, d);
	m_lp->inc_timestamp();
	m_timestamp++;
}

