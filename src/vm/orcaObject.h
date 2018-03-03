/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

/**********************************************************************

  orcaObject.h - base class of all orca object

  Copyright (C) 2009-2011 Lee, Ki-Yeul

**********************************************************************/


#ifndef _DEF_ORCA_OBJECT
#define _DEF_ORCA_OBJECT

#include <vector>
#include <string>

#include "orcaData.h"
#include "orcaVM.h"

#define DEFAULT_NATIVE_DEFINE(name)		\
      name(void* vp) { }				\
      virtual ~name() { }				\
      orcaObject* v_clone() {			\
          return new name((void*)NULL);	\
      }									\
      
	
         
using namespace std;

class orcaObject;
struct orcaData;

class LIBORCA_API orcaObject : public RC_Object
{

friend class orcaVM;
friend class orcaObjectParents;
friend class orcaObjectParentsIter;
friend class orcaObjectMembers;
friend class orcaObjectMembersIter;

public:
	orcaObject();
	orcaObject(orcaObject* o);
	virtual ~orcaObject();

	// execution
	virtual orcaData operator()(orcaVM* vm, int param_n);

	// object management
	orcaObject* clone(orcaObject* owner = NULL);
	virtual orcaObject* v_clone();
	void make_original();
	orcaObject* make_super(orcaObject* o);
	void set_flag(char flag);
	char get_flag();
	bool is_init();
	bool is_native();

	// member management
	bool insert_member(const char* name, orcaData d);
	bool remove_member(const char* name);
	bool insert_static(const char* name, orcaData d);
	bool insert_native_function(const char* name, object_fp func);
	bool insert_static_native_function(const char* name, object_fp func);
	bool insert_parent(orcaObject* o);	// compile time
	bool insert_parent_runtime(orcaObject* o); 
	bool remove_parent(orcaObject* o); 
	bool has_parent(orcaObject* o); 

	orcaData get_member_sub(const char* name, bool last);
	orcaData get_member(const char* name);
	orcaData get_member_last(const char* name);
	bool has_member(const char* name);
	bool has_member(const char* name, orcaData& d);
	bool has_static_member(const char* name, orcaData& d);
	orcaData update_member(const char* name, orcaData d);

	// operator
	virtual orcaData operator_mul(orcaVM* vm, orcaData& p);
	virtual orcaData operator_add(orcaVM* vm, orcaData& p);
	virtual orcaData operator_sub(orcaVM* vm, orcaData& p);
	virtual orcaData operator_sub_rev(orcaVM* vm, orcaData& p);
	virtual orcaData operator_div(orcaVM* vm, orcaData& p);
	virtual orcaData operator_div_rev(orcaVM* vm, orcaData& p);
	virtual orcaData operator_lt(orcaVM* vm, orcaData& p);
	virtual orcaData operator_le(orcaVM* vm, orcaData& p);
	virtual orcaData operator_gt(orcaVM* vm, orcaData& p);
	virtual orcaData operator_ge(orcaVM* vm, orcaData& p);
	virtual orcaData operator_eq(orcaVM* vm, orcaData& p);
	virtual orcaData operator_neq(orcaVM* vm, orcaData& p);
	virtual orcaData operator_and(orcaVM* vm, orcaData& p);
	virtual orcaData operator_or(orcaVM* vm, orcaData& p);

	virtual orcaData operator_get(orcaVM* vm, orcaData& p);
	virtual orcaData operator_get_last(orcaVM* vm, orcaData& p);
	virtual orcaData operator_set(orcaVM* vm, const char* name, orcaData& p);
	virtual orcaData operator_get_at(orcaVM* vm, orcaData& at);
	virtual orcaData operator_set_at(orcaVM* vm, orcaData& at, orcaData& val);

	virtual string pack_save();
	virtual void pack_load(string& str);

	// printing & debugging
	virtual void string_(orcaVM* vm, string& str);
	virtual void repr(orcaVM* vm, string& str);
	void dump();
	string dump_str();
	virtual char* dump(char* buff);
	void member_dump();

	void set_name(const char* name);
	const char* get_name();
	string get_path_name();
	const char* get_code();
	void set_code(const char* cp);

	bool issubclassof(orcaObject* o);
	bool isinstanceof(orcaObject* o);

	orcaObject* get_original()
	{
		return m_original;
	}

	void set_original(orcaObject* op)
	{
		m_original = op;
	}

private:
	int get_frame_size();
	int get_argument_size();
	char get_flag_argv();

protected:
	cp_map<orcaData>::Type *m_static;
	cp_map<orcaData>::Type m_member;

	orcaObject* m_owner;
	orcaObject* m_base;

private:
	list<orcaObject*>* m_parent;
	const char* m_name;
	const char* m_code;
	orcaObject* m_original;
	int m_flag;

public: // for pack
	cp_map<orcaData>::Type* get_static() 
	{
		return m_static;
	}

	cp_map<orcaData>::Type* get_member() 
	{
		return &m_member;
	}	

	list<orcaObject*>* get_parent() 
	{
		return m_parent;
	}	

	orcaObject* get_owner();
};

template <typename T>
T* original()
{
	T* tp = new T((void*)NULL);
	tp->make_original();
	return tp;
}


#endif



