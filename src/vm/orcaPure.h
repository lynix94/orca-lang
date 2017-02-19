/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaPure.h - handling pure function

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_PURE
#define _DEF_ORCA_PURE

#include "porting.h"

#include <vector>
#include <map>

#include "orcaData.h"
#include "orcaUtil.h"

class orcaObject;
class orcaStack;

using namespace std;


struct lru_t
{
	orcaObject* op;
	vector<orcaData> param;
	orcaData result;

	bool operator<(const lru_t& rhs) const
	{
		if ((void*)op < (void*)rhs.op)
			return true;

		if (rhs.param.size() < param.size())
			return true;

		for (int i=0; i<param.size(); i++) {
			if (param[i] < rhs.param[i])
				return true;
		}

		return false;
	}
};



class orcaPure
{
public:
	orcaPure(orcaVM* vm, int max=10000) : m_vm(vm), m_max(max) {}
	~orcaPure();

	bool find(orcaObject* op, orcaStack* sp, int n, orcaData& ret);
	void add(orcaObject* op, vector<orcaData>& param, orcaData result);

private:
	orcaVM* m_vm;
	portMutex m_mutex;
	orca_lru<lru_t, lru_t> m_lru;

	int m_max;
};

#endif


