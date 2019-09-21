/* vim: set fdc=2 foldmethod=marker ts=4 tabstop=4 sw=4 sts=4 : */

#include <leveldb/db.h>

#include "orcaObject.h"
class orcaLeveldbIterator : public orcaObject 
{
public:
	orcaLeveldbIterator(leveldb::DB* db, leveldb::Iterator* it, bool is_begin = false, bool is_iter2 = false);

	virtual ~orcaLeveldbIterator() {}
	orcaLeveldbIterator(void* vp) { }
	orcaObject* v_clone();

	orcaData operator()(orcaVM* vm, int n);
	orcaData ex_next(orcaVM* vm, int n);
	orcaData ex_prev(orcaVM* vm, int n);
	orcaData ex_eq(orcaVM* vm, int n);

private:
	leveldb::DB *db;
	leveldb::Iterator *it;
	bool is_iter2;
	bool is_end;
	bool is_begin;
};


class orcaLeveldbHandle : public orcaObject 
{
public:
	orcaLeveldbHandle(leveldb::DB* db);
	virtual ~orcaLeveldbHandle() {}
	orcaLeveldbHandle(void* vp) { }
	orcaObject* v_clone();

	orcaData ex_put(orcaVM* vm, int n);
	orcaData ex_get(orcaVM* vm, int n);
	orcaData ex_del(orcaVM* vm, int n);
	orcaData ex_iter(orcaVM* vm, int n);
	orcaData ex_iter2(orcaVM* vm, int n);
	orcaData ex_find(orcaVM* vm, int n);

	orcaData ex_lower_bound(orcaVM* vm, int n);
	orcaData ex_upper_bound(orcaVM* vm, int n);
	orcaData ex_first(orcaVM* vm, int n);
	orcaData ex_last(orcaVM* vm, int n);
	orcaData ex_end(orcaVM* vm, int n);

	orcaLeveldbIterator* end_iterator();

private:
	leveldb::DB *db;
};


class orcaLeveldb : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaLeveldb);
	orcaLeveldb()
	{
		set_name("leveldb");
		insert_native_function("open", (object_fp)&orcaLeveldb::ex_open);
	}

	orcaData ex_open(orcaVM* vm, int n);
};


