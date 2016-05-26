/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaStack.cpp - impl. of orca stack frame

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#include "orcaStack.h"


orcaStack::orcaStack(orcaLocal* local) : m_sp(-1), m_size(1024), m_local(local) 
{ 
	m_frame = new orcaData[m_size];
}

orcaStack::~orcaStack()
{ 
	delete[] m_frame;
}

void orcaStack::more()
{
	orcaData* tmp = new orcaData[m_size*2];
	copy(&m_frame[0], &m_frame[m_size], &tmp[0]);
	m_size *= 2;
	delete[] m_frame;

	m_frame = tmp;
}

void orcaStack::dump()
{
	printf("# orcaStack Dump: %d\n", m_sp);
	for(int i=m_sp; i>=0; i--) {
		printf("  ");
		m_frame[i].dump();
	}
}

