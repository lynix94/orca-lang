/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaMap.h - map type

  Copyright (C) 2009 Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_MAP
#define _DEF_ORCA_MAP

#include "orcaObject.h"
#include "orcaVM.h"
#include "orcaLocal.h"

#define TO_MAP(a)	static_cast<orcaMap*>(a)

class orcaForStack;
class orcaMap;


struct data_cmp : public binary_function<orcaData, orcaData, bool>
{
	bool operator()(orcaData l, orcaData r) const;
};

typedef map<orcaData, orcaData, data_cmp>::iterator orcamap_iterator;


class LIBORCA_API orcaMap : public orcaObject
{
friend class orcaForStack;
friend class orcaMapIter;

public:
	orcaMap();
	orcaMap(void* vp);
	orcaObject* v_clone();
	virtual ~orcaMap();

	// internal
	orcaData& at(orcaData& key); 
	orcaData slice(orcaData& start, orcaData& end, bool include_right);
	void update(orcaData& key, orcaData& val);
	bool has_key(orcaData& key);

	virtual void string_(orcaVM* vm, string& str);
	virtual void repr(orcaVM* vm, string& str);
	void dump(); 

	// static
	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_keys(orcaVM* vm, int n);
	orcaData ex_values(orcaVM* vm, int n);
	orcaData ex_has_key(orcaVM* vm, int n);
	orcaData ex_find(orcaVM* vm, int n);
	orcaData ex_lower_bound(orcaVM* vm, int n);
	orcaData ex_upper_bound(orcaVM* vm, int n);
	orcaData ex_iter(orcaVM* vm, int n);
	orcaData ex_first(orcaVM* vm, int n);
	orcaData ex_last(orcaVM* vm, int n);
	orcaData ex_end(orcaVM* vm, int n);
	orcaData ex_erase_key(orcaVM* vm, int n);
	orcaData ex_empty(orcaVM* vm, int n);
	orcaData ex_clear(orcaVM* vm, int n);

	// get, set
	virtual orcaData operator_eq(orcaVM* vm, orcaData& p);

	orcaData& get(orcaData& param) 
	{
		return m_value[param];
	}

	void set(orcaData& key, orcaData& val) 
	{
		m_value[key] = val;
	}

	orcamap_iterator find(orcaData key)
	{
		return m_value.find(key);
	}

	orcamap_iterator begin() 
	{
		return m_value.begin();
	}

	orcamap_iterator end() 
	{
		return m_value.end();
	}

	int get_timestamp()
	{
		return m_timestamp;
	}
	
	void inc_timestamp()
	{
		m_timestamp++;
	}

protected:
	map<orcaData, orcaData, data_cmp> m_value;
	static cp_map<orcaData>::Type m_static_map;

	int m_timestamp;
};

#endif

