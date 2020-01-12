
#ifndef _DEF_ORCA_UNSAFE
#define _DEF_ORCA_UNSAFE

#include <boost/lexical_cast.hpp>

#include "porting.h"
#include "orcaObject.h"
#include "orcaException.h"


class orcaBitStream : public orcaObject 
{
public:
	orcaBitStream(void* vp) : bit_size(0) { }
	orcaBitStream();
	~orcaBitStream() { }

	orcaObject* v_clone()
	{
		orcaBitStream* op = new orcaBitStream(NULL);
		return op;
	}

	size_t size()
	{
		return bit_size;
	}

	long long bitget(int bit_idx, int size);
	void bitset(int bit_idx, int size, long long value);
	size_t bitappend(int size, long long value);

	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_bitget(orcaVM* vm, int n);
	orcaData ex_bitset(orcaVM* vm, int n);
	orcaData ex_bitappend(orcaVM* vm, int n);
	orcaData ex_hexdump(orcaVM* vm, int n);

private:
	vector<char> data;
	size_t bit_size;
};


class orcaPointer : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaPointer);
	orcaPointer();

	orcaData ex_str(orcaVM* vm, int n);
	orcaData ex_int8(orcaVM* vm, int n);
	orcaData ex_int16(orcaVM* vm, int n);
	orcaData ex_int32(orcaVM* vm, int n);
	orcaData ex_int64(orcaVM* vm, int n);
	orcaData ex_uint8(orcaVM* vm, int n);
	orcaData ex_uint16(orcaVM* vm, int n);
	orcaData ex_uint32(orcaVM* vm, int n);
	orcaData ex_uint64(orcaVM* vm, int n);
	orcaData ex_float32(orcaVM* vm, int n);
	orcaData ex_float64(orcaVM* vm, int n);

	template<typename T> T int_cast_helper(orcaVM* vm, int n) /*{{{*/
	{
		if (n < 2) vm->need_param();

		orcaData p = vm->get_param(0);
		if (!is<TYPE_STR>(p)) {
			throw orcaException(vm, "unsafe.pointer", "not a pointer type");
		}

		char *cp = (char*)p.so()->s.c_str();
		int index = vm->get_param(1).Integer();

		if (n < 3) {
			T ret = *((T*)(cp + index));
			return ret;
		}
		else {
			T v = vm->get_param(2).Integer();
			*((T*)(cp + index)) = v;
			return 0;
		}
	}
/*}}}*/

	template<typename T> T bigint_cast_helper(orcaVM* vm, int n, int size) /*{{{*/
	{
		if (n < 2) vm->need_param();

		orcaData p = vm->get_param(0);
		if (!is<TYPE_STR>(p)) {
			throw orcaException(vm, "unsafe.pointer", "not a pointer type");
		}

		char *cp = (char*)p.so()->s.c_str();
		int index = vm->get_param(1).Integer();

		if (n < 3) {
			T ret = *((T*)(cp + index));
			if (ret > LLONG_MAX) {
				return (unsigned long long)ret;
			}

			if (ret > INT_MAX) {
				return (long long)ret;
			}

			return (int)ret;
		}
		else {
			orcaData p = vm->get_param(2);

			if (is<TYPE_BIGNUM>(p)) {
				double d = get_bn_double(p.bn());
				if (d > ULLONG_MAX) {
					throw orcaException(vm, "unsafe.struct", "big int exceed limit");
				}
				else if (d > LLONG_MAX) {
					string src = get_bn_string(p.bn());
					char* stop;
					unsigned long long ret = strtoull(src.c_str(), &stop, 10);
					*((unsigned long long*)(cp + index)) = ret;
				}
				else if (d > INT_MAX) {
					string src = get_bn_string(p.bn());
					long long ret = atoll(src.c_str());
					if (size == 4) { // uint32
						*((unsigned int*)(cp + index)) = (unsigned int)ret;
					}
					else {
						*((long long*)(cp + index)) = ret;
					}
				}
			}

			*((int*)(cp + index)) = p.Integer();
			return 0;
		}
	}
/*}}}*/

	template<typename T> T float_cast_helper(orcaVM* vm, int n) /*{{{*/
	{
		if (n < 2) vm->need_param();

		orcaData p = vm->get_param(0);
		if (!is<TYPE_STR>(p)) {
			throw orcaException(vm, "unsafe.pointer", "not a pointer type");
		}

		char *cp = (char*)p.so()->s.c_str();
		int index = vm->get_param(1).Integer();

		if (n < 3) {
			T ret = *((T*)(cp + index));
			return ret;
		}
		else {
			T v = T(vm->get_param(2).Double());
			*((T*)(cp + index)) = v;
			return 0;
		}
	}
/*}}}*/

};

class orcaStruct : public orcaObject 
{
public:
	enum attr_e
	{
		E_NIL = 0,
		E_INT8, E_INT16, E_INT32, E_INT64,
		E_UINT8, E_UINT16, E_UINT32, E_UINT64,
		E_FLOAT32, E_FLOAT64,
		E_STRING
	};
	typedef map<string, pair<int, attr_e> > attr_t;

	orcaStruct(orcaData p, int i);
	~orcaStruct()
	{
		data.rc_dec();
	}

	orcaStruct* v_clone()
	{
		orcaStruct *sp = new orcaStruct(data, index);
		return sp;
	}

	orcaData attr_helper(orcaVM* vm, int n, attr_e e);
	orcaData ex_int8(orcaVM* vm, int n);
	orcaData ex_int16(orcaVM* vm, int n);
	orcaData ex_int32(orcaVM* vm, int n);
	orcaData ex_int64(orcaVM* vm, int n);
	orcaData ex_uint8(orcaVM* vm, int n);
	orcaData ex_uint16(orcaVM* vm, int n);
	orcaData ex_uint32(orcaVM* vm, int n);
	orcaData ex_uint64(orcaVM* vm, int n);
	orcaData ex_float32(orcaVM* vm, int n);
	orcaData ex_float64(orcaVM* vm, int n);
	orcaData ex_str(orcaVM* vm, int n);
	orcaData ex_at(orcaVM* vm, int n);
	orcaData ex_set_at(orcaVM* vm, int n);
	orcaData ex_pointer(orcaVM* vm, int n);

	attr_t attr;
	orcaData data;
	int index;
	char* cp;
};

class orcaUnsafe : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaUnsafe);

	orcaUnsafe() 
	{
		insert_static("pointer", new orcaPointer());
		insert_member("bitstream", new orcaBitStream());
		insert_static_native_function("struct", (object_fp)&orcaUnsafe::ex_struct);
	}

	orcaData ex_struct(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		orcaData p = vm->get_param(0);
		int index = 0;
		if (n >= 2) {
			index = vm->get_param(1).Integer();
		}

		orcaStruct *sp = new orcaStruct(p, index);
		return sp;
	}
};


#endif


