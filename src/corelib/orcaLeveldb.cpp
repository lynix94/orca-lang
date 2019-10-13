
#include "orcaLeveldb.h"
#include "orcaException.h"
#include "orcaTuple.h"






orcaLeveldbIterator::orcaLeveldbIterator(leveldb::DB* db, leveldb::Iterator* it, bool is_begin, bool is_iter2)
{
	set_name("leveldb_iterator");
	insert_native_function("next", (object_fp)&orcaLeveldbIterator::ex_next);
	insert_native_function("prev", (object_fp)&orcaLeveldbIterator::ex_prev);
	insert_native_function("key", (object_fp)&orcaLeveldbIterator::ex_key);
	insert_native_function("value", (object_fp)&orcaLeveldbIterator::ex_value);
	insert_native_function("erase", (object_fp)&orcaLeveldbIterator::ex_erase);
	insert_native_function("==", (object_fp)&orcaLeveldbIterator::ex_eq);
	insert_native_function("<", (object_fp)&orcaLeveldbIterator::ex_lt);

	this->db = db;
	this->it = it;
	this->is_iter2 = is_iter2;
	this->is_begin = is_begin;
}

orcaObject* orcaLeveldbIterator::v_clone()
{
	orcaLeveldbIterator* ip = new orcaLeveldbIterator((void*)NULL);
	ip->it = it;
	return ip;
}

orcaData orcaLeveldbIterator::operator()(orcaVM* vm, int n)
{
	if (n > 0) {
		string value = vm->get_param(0).String();

		leveldb::Status s = db->Put(leveldb::WriteOptions(), it->key().ToString(), value);
		if (s.ok() == false) {
			throw orcaException(vm, "leveldb.put", s.ToString());
		}

		return NIL;
	}

	if (is_begin || it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	orcaTuple* tp = new orcaTuple(2);
	tp->update(0, it->key().ToString());
	tp->update(1, it->value().ToString());
	return tp;
}

orcaData orcaLeveldbIterator::ex_key(orcaVM* vm, int n)
{
	if (is_begin || it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	return it->key().ToString();
}

orcaData orcaLeveldbIterator::ex_value(orcaVM* vm, int n)
{
	if (is_begin || it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	return it->value().ToString();
}

orcaData orcaLeveldbIterator::ex_next(orcaVM* vm, int n)
{
	if (it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	if (is_begin) {
		is_begin = false;
	}
	else {
		it->Next();
	}

	if (it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	if (is_iter2) {
		orcaTuple* tp = new orcaTuple(2);
		tp->update(0, it->key().ToString());
		tp->update(1, it->value().ToString());
		return tp;
	}

	return it->key().ToString();
}

orcaData orcaLeveldbIterator::ex_prev(orcaVM* vm, int n)
{
	if (is_begin || it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	it->Prev();
	if (it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	if (is_iter2) {
		orcaTuple* tp = new orcaTuple(2);
		tp->update(0, it->key().ToString());
		tp->update(1, it->value().ToString());
		return tp;
	}

	return it->value().ToString();
}

orcaData orcaLeveldbIterator::ex_eq(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);


	orcaLeveldbIterator* ip = castobj<orcaLeveldbIterator>(vm->get_param(0));
	if (ip == NULL) {
		throw orcaException(vm, "orca.type", "invalid iterator");
	}

	if (it->Valid() && ip->it->Valid()) {
		if (is_begin == ip->is_begin) {
			return it->key().ToString() == ip->it->key().ToString();
		}
		else {
			return false;
		}
	}

	if (!it->Valid() && !it->Valid()) {
		return true;
	}

	return false;
}

orcaData orcaLeveldbIterator::ex_lt(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);


	orcaLeveldbIterator* ip = castobj<orcaLeveldbIterator>(vm->get_param(0));
	if (ip == NULL) {
		throw orcaException(vm, "orca.type", "invalid iterator");
	}

	if (it->Valid() && ip->it->Valid()) {
		if (is_begin == ip->is_begin) {
			return it->key().ToString() < ip->it->key().ToString();
		}
	}

	return false;
}

orcaData orcaLeveldbIterator::ex_erase(orcaVM* vm, int n)
{
	if (is_begin || it->Valid() == false) {
		throw orcaException(vm, "orca.iter.end", "done");
	}

	leveldb::Status s = db->Delete(leveldb::WriteOptions(), it->key().ToString());
	if (s.ok() == false) {
		throw orcaException(vm, "leveldb.get", s.ToString());
	}

	return true;
}


orcaLeveldbHandle::orcaLeveldbHandle(leveldb::DB* db)
{
	set_name("leveldb_handle");
	insert_native_function("put", (object_fp)&orcaLeveldbHandle::ex_put);
	insert_native_function("get", (object_fp)&orcaLeveldbHandle::ex_get);
	insert_native_function("erase_key", (object_fp)&orcaLeveldbHandle::ex_erase_key);
	insert_native_function("iter", (object_fp)&orcaLeveldbHandle::ex_iter);
	insert_native_function("iter2", (object_fp)&orcaLeveldbHandle::ex_iter2);
	insert_native_function("find", (object_fp)&orcaLeveldbHandle::ex_find);
	insert_native_function("lower_bound", (object_fp)&orcaLeveldbHandle::ex_lower_bound);
	insert_native_function("upper_bound", (object_fp)&orcaLeveldbHandle::ex_upper_bound);
	insert_native_function("first", (object_fp)&orcaLeveldbHandle::ex_first);
	insert_native_function("last", (object_fp)&orcaLeveldbHandle::ex_last);
	insert_native_function("end", (object_fp)&orcaLeveldbHandle::ex_end);
	this->db = db;
}

orcaObject* orcaLeveldbHandle::v_clone()
{
	orcaLeveldbHandle* sp = new orcaLeveldbHandle((void*)NULL);
	sp->db = db;
	return sp;
}

orcaData orcaLeveldbHandle::ex_put(orcaVM* vm, int n)
{
	if (n < 2) vm->need_param(2);

	string key = vm->get_param(0).String();
	string value = vm->get_param(1).String();

	leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
	if (s.ok() == false) {
		throw orcaException(vm, "leveldb.put", s.ToString());
	}

	return true;
}

orcaData orcaLeveldbHandle::ex_get(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);

	string key = vm->get_param(0).String();
	string value;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
	if (s.ok() == false) {
		throw orcaException(vm, "leveldb.get", s.ToString());
	}

	return value;
}

orcaData orcaLeveldbHandle::ex_erase_key(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);

	string key = vm->get_param(0).String();

	leveldb::Status s = db->Delete(leveldb::WriteOptions(), key);
	if (s.ok() == false) {
		throw orcaException(vm, "leveldb.get", s.ToString());
	}

	return true;
}

orcaData orcaLeveldbHandle::ex_iter(orcaVM* vm, int n)
{
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToFirst();

	return new orcaLeveldbIterator(db, it, true);
}

orcaData orcaLeveldbHandle::ex_iter2(orcaVM* vm, int n)
{
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToFirst();

	return new orcaLeveldbIterator(db, it, true, true);
}

orcaData orcaLeveldbHandle::ex_find(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);
	string key = vm->get_param(0).String();

	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(key);
	if (!it->Valid()) {
		return end_iterator();
	}

	if (it->key().ToString() != key) {
		return end_iterator();
	}

	return new orcaLeveldbIterator(db, it);
}

orcaData orcaLeveldbHandle::ex_lower_bound(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);
	string key = vm->get_param(0).String();

	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(key);
	if (!it->Valid()) {
		return end_iterator();
	}

	return new orcaLeveldbIterator(db, it);
}

orcaData orcaLeveldbHandle::ex_upper_bound(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);
	string key = vm->get_param(0).String();

	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(key);
	if (!it->Valid()) {
		return end_iterator();
	}

	if (it->key().ToString() == key) {
		it->Next();
		if (!it->Valid()) {
			return end_iterator();
		}
	}

	return new orcaLeveldbIterator(db, it);
}

orcaData orcaLeveldbHandle::ex_first(orcaVM* vm, int n)
{
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToFirst();
	if (!it->Valid()) {
		return end_iterator();
	}

	return new orcaLeveldbIterator(db, it);
}

orcaData orcaLeveldbHandle::ex_last(orcaVM* vm, int n)
{
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToLast();
	if (!it->Valid()) {
		return end_iterator();
	}

	return new orcaLeveldbIterator(db, it);
}

orcaData orcaLeveldbHandle::ex_end(orcaVM* vm, int n)
{
	return end_iterator();
}


orcaLeveldbIterator* orcaLeveldbHandle::end_iterator()
{
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToLast();
	if (it->Valid()) {
		it->Next();
	}

	return new orcaLeveldbIterator(db, it);
}


orcaData orcaLeveldb::ex_open(orcaVM* vm, int n)
{
	if (n < 1) vm->need_param(1);

	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status s = leveldb::DB::Open(options, vm->get_param(0).String(), &db);
	if (s.ok() == false) {
		throw orcaException(vm, "leveldb.open", s.ToString());
	}

	orcaLeveldbHandle* hp = new orcaLeveldbHandle(db);
	return hp;
}




