/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaQueue.cpp - tuple type

  Copyright (C) 2009~ Lee, Ki-Yeul

**********************************************************************/

#include <boost/lexical_cast.hpp>

#include "orcaQueue.h"
#include "orcaTuple.h"

orcaQueue::orcaQueue()
{ 
	set_name("queue"); 
	insert_native_function("init", (object_fp)&orcaQueue::ex_init);
	insert_native_function("size", (object_fp)&orcaQueue::ex_size);
	insert_native_function("cap", (object_fp)&orcaQueue::ex_cap);
	insert_native_function("->", (object_fp)&orcaQueue::ex_channel_out);
	insert_native_function("<-", (object_fp)&orcaQueue::ex_channel_in);
	insert_native_function("push", (object_fp)&orcaQueue::ex_push);
	insert_native_function("pop", (object_fp)&orcaQueue::ex_pop);
}


orcaData orcaQueue::ex_init(orcaVM* vm, int n) 
{
	if (n == 0) {
		m_cap = 0;
	} else {
		m_cap = vm->get_param(0).Integer(); 
	}

	return NIL;
}

orcaData orcaQueue::ex_size(orcaVM* vm, int n) 
{
	return m_value.size();
}

orcaData orcaQueue::ex_cap(orcaVM* vm, int n) 
{
	return m_cap;
}


void orcaQueue::string_(orcaVM* vm, string& str) 
{
	list<orcaData>::iterator it = m_value.begin();

	str += "[ ";
	while(it!=m_value.end()) {
		if (is<TYPE_STR>(*it)) str += "'";
		(*it).string_(vm, str);
		if (is<TYPE_STR>(*it)) str += "'";

		++it;
		if (it!=m_value.end()) str+= ",";
	}

	str += " ]";
}
void orcaQueue::dump() 
{ 
	list<orcaData>::iterator it = m_value.begin();

	printf("[ ");

	for(; it!=m_value.end(); ++it) {
		(*it).dump();
	}

	printf(" ]\n");
}

orcaData orcaQueue::ex_channel_out(orcaVM* vm, int n) 
{
	if (n<1) vm->need_param();

	int count = vm->get_param(0).Integer();
	if (count == 0) { // argv
		count = m_value.size();
	}

	mutex.lock();
	if (m_value.empty()) {
		getable_cond.wait(&mutex);
	}

	orcaTuple* tup = new orcaTuple();
	for (int i=0; i<count && !m_value.empty(); i++) {
		list<orcaData>::iterator it = m_value.begin();
		tup->push_back(*it);
		(*it).rc_dec();
		m_value.pop_front();
	}
	putable_cond.signal();
	mutex.unlock();

	return tup;
}

orcaData orcaQueue::ex_channel_in(orcaVM* vm, int n) 
{
	for (int i=0; i<n; i++) {
		mutex.lock();
		if (m_cap > 0 && m_value.size() >= m_cap) {
			putable_cond.wait(&mutex);
		}

		orcaData val = vm->get_param(i);
		m_value.push_back(val);
		val.rc_inc();
		getable_cond.signal();
		mutex.unlock();
	}

	return this;
}



orcaData orcaQueue::ex_pop(orcaVM* vm, int n) 
{
	double tmout = 0;
	if (n > 0) {
		tmout = vm->get_param(0).Double();
	}

	mutex.lock();
	if (m_value.empty()) {
		if (tmout == 0) {
			getable_cond.wait(&mutex);
		}
		else if (tmout < 0) {
			mutex.unlock();
			return NIL;
		}
		else {
			if (getable_cond.wait(&mutex, tmout * (1000*1000*1000)) == false) {
				mutex.unlock();
				return NIL;
			}
		}
	}

	orcaData d = *m_value.begin();
	d.rc_dec();
	m_value.pop_front();
	putable_cond.signal();
	mutex.unlock();

	return d;
}

orcaData orcaQueue::ex_push(orcaVM* vm, int n) 
{
	if (n<1) vm->need_param();

	double tmout = 0;
	orcaData d = vm->get_param(0);
	if (n >= 2) {
		tmout = vm->get_param(1).Double();
	}

	mutex.lock();
	if (m_cap > 0 && m_value.size() >= m_cap) {
		if (tmout == 0) {
			putable_cond.wait(&mutex);
		}
		else if (tmout < 0) {
			mutex.unlock();
			return false;
		}
		else {
			if (putable_cond.wait(&mutex, tmout * (1000*1000*1000)) == false) {
				mutex.unlock();
				return false;
			}
		}
	}

	m_value.push_back(d);
	d.rc_inc();
	getable_cond.signal();
	mutex.unlock();

	return true;
}



