
#ifndef _DEF_ORCA_UNSAFE
#define _DEF_ORCA_UNSAFE

#include "porting.h"
#include "orcaObject.h"

class orcaPointer : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaPointer);

	orcaPointer() 
	{
		set_name("pointer");
		insert_static_native_function("int", (object_fp)&orcaPointer::ex_int32);
		insert_static_native_function("int8", (object_fp)&orcaPointer::ex_int8);
		insert_static_native_function("int16", (object_fp)&orcaPointer::ex_int16);
		insert_static_native_function("int32", (object_fp)&orcaPointer::ex_int32);
		insert_static_native_function("int64", (object_fp)&orcaPointer::ex_int64);
		insert_static_native_function("uint", (object_fp)&orcaPointer::ex_uint32);
		insert_static_native_function("uint8", (object_fp)&orcaPointer::ex_uint8);
		insert_static_native_function("uint16", (object_fp)&orcaPointer::ex_uint16);
		insert_static_native_function("uint32", (object_fp)&orcaPointer::ex_uint32);
		insert_static_native_function("uint64", (object_fp)&orcaPointer::ex_uint64);
		insert_static_native_function("float32", (object_fp)&orcaPointer::ex_float32);
		insert_static_native_function("float64", (object_fp)&orcaPointer::ex_float64);
		insert_static_native_function("str", (object_fp)&orcaPointer::ex_str);
	}

	template<typename T> T int_helper(orcaVM* vm, int n) 
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
			return v;
		}
	}

	template<typename T> T bigint_helper(orcaVM* vm, int n, int size) 
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
					return ret;
				}
				else if (d > INT_MAX) {
					string src = get_bn_string(p.bn());
					long long ret = atoll(src.c_str());
					if (size == 4) { // uint32
						*((unsigned int*)(cp + index)) = (unsigned int)ret;
						return ret;
					}
					else {
						*((long long*)(cp + index)) = ret;
						return ret;
					}
				}
			}

			*((int*)(cp + index)) = p.Integer();
			return p.Integer();
		}
	}


	template<typename T> T float_helper(orcaVM* vm, int n) 
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
			return v;
		}
	}

	orcaData ex_str(orcaVM* vm, int n) 
	{
		if (n < 2) vm->need_param();

		orcaData p = vm->get_param(0);
		if (!is<TYPE_STR>(p)) {
			throw orcaException(vm, "unsafe.pointer", "not a pointer type");
		}

		char *cp = (char*)p.so()->s.c_str();
		int index = vm->get_param(1).Integer();

		if (n < 3) {
			char* ret = cp + index;
			return ret;
		}
		else {
			string str = vm->get_param(2).String();
			memcpy(cp + index, str.c_str(), str.length()+1);
			return NIL;
		}
	}


	orcaData ex_int8(orcaVM* vm, int n) 
	{
		return int_helper<char>(vm, n);
	}

	orcaData ex_int16(orcaVM* vm, int n) 
	{
		return int_helper<short>(vm, n);
	}

	orcaData ex_int32(orcaVM* vm, int n) 
	{
		return int_helper<int>(vm, n);
	}

	orcaData ex_int64(orcaVM* vm, int n) 
	{
		return bigint_helper<int>(vm, n, 8);
	}

	orcaData ex_uint8(orcaVM* vm, int n) 
	{
		return int_helper<unsigned char>(vm, n);
	}

	orcaData ex_uint16(orcaVM* vm, int n) 
	{
		return int_helper<unsigned short>(vm, n);
	}

	orcaData ex_uint32(orcaVM* vm, int n) 
	{
		return bigint_helper<int>(vm, n, 4);
	}

	orcaData ex_uint64(orcaVM* vm, int n) 
	{
		return bigint_helper<int>(vm, n, 8);
	}

	orcaData ex_float32(orcaVM* vm, int n) 
	{
		return float_helper<float>(vm, n);
	}

	orcaData ex_float64(orcaVM* vm, int n) 
	{
		return float_helper<double>(vm, n);
	}
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

	orcaStruct(orcaData p, int i) 
	{
		set_name("struct");
		insert_native_function("int", (object_fp)&orcaStruct::ex_int32);
		insert_native_function("int8", (object_fp)&orcaStruct::ex_int8);
		insert_native_function("int16", (object_fp)&orcaStruct::ex_int16);
		insert_native_function("int32", (object_fp)&orcaStruct::ex_int32);
		insert_native_function("int64", (object_fp)&orcaStruct::ex_int64);
		insert_native_function("uint", (object_fp)&orcaStruct::ex_uint32);
		insert_native_function("uint8", (object_fp)&orcaStruct::ex_uint8);
		insert_native_function("uint16", (object_fp)&orcaStruct::ex_uint16);
		insert_native_function("uint32", (object_fp)&orcaStruct::ex_uint32);
		insert_native_function("uint64", (object_fp)&orcaStruct::ex_uint64);
		insert_native_function("float32", (object_fp)&orcaStruct::ex_float32);
		insert_native_function("float64", (object_fp)&orcaStruct::ex_float64);
		insert_native_function("str", (object_fp)&orcaStruct::ex_str);
		insert_native_function(".", (object_fp)&orcaStruct::ex_at);
		insert_native_function(".=", (object_fp)&orcaStruct::ex_set_at);
		insert_native_function("pointer", (object_fp)&orcaStruct::ex_pointer);

		if (!is<TYPE_STR>(p)) {
			throw orcaException(NULL, "unsafe.pointer", "not a pointer type");
		}

		data = p;
		index = i;

		data.rc_inc();
		cp = (char*)data.so()->s.c_str();
	}

	~orcaStruct()
	{
		data.rc_dec();
	}

	orcaStruct* v_clone()
	{
		orcaStruct *sp = new orcaStruct(data, index);
		return sp;
	}

	orcaData attr_helper(orcaVM* vm, int n, attr_e e)
	{
		if (n < 2) vm->need_param();

		string name = vm->get_param(0).String();
		int index = vm->get_param(1).Integer();

		attr[name] = pair<int, attr_e>(index, e);
	}

	orcaData ex_int8(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_INT8);
	}

	orcaData ex_int16(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_INT16);
	}

	orcaData ex_int32(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_INT32);
	}

	orcaData ex_int64(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_INT64);
	}

	orcaData ex_uint8(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_UINT8);
	}

	orcaData ex_uint16(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_UINT16);
	}

	orcaData ex_uint32(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_UINT32);
	}

	orcaData ex_uint64(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_UINT64);
	}

	orcaData ex_float32(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_FLOAT32);
	}

	orcaData ex_float64(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_FLOAT64);
	}

	orcaData ex_str(orcaVM* vm, int n) 
	{
		return attr_helper(vm, n, E_STRING);
	}

	orcaData ex_at(orcaVM* vm, int n) 
	{
		if (n < 1) vm->need_param();

		string name = vm->get_param(0).String();
		attr_t::iterator it = attr.find(name);
		if (it == attr.end()) {
			throw orcaException(vm, "unsafe.struct", "attr not found");
		}

		pair<int, attr_e> t = it->second;
		int index = t.first;
		attr_e type = t.second;

		switch (type)
		{
		case E_INT8:
			return *((char*)(cp + index));

		case E_INT16:
			return *((short*)(cp + index));

		case E_INT32:
			return *((int*)(cp + index));

		case E_INT64:
			return *((long long*)(cp + index));

		case E_UINT8:
			return *((unsigned char*)(cp + index));

		case E_UINT16:
			return *((unsigned short*)(cp + index));

		case E_UINT32: {
				unsigned int ret = *((unsigned int*)(cp + index));
				if (ret <= INT_MAX) {
					return (int)ret;
				}

				return (long long)ret;
			}

		case E_UINT64: {
				unsigned long long ret = *((unsigned long long*)(cp + index));
				if (ret <= LLONG_MAX) {
					return (long long)ret;
				}

				char buff[64];
				sprintf(buff, "%llu", ret);
				mpz_t bn;
				mpz_init(bn);
				mpz_set_str(bn, buff, 0);
				return bn;
			}

		case E_FLOAT32:
			return *((float*)(cp + index));

		case E_FLOAT64:
			return *((double*)(cp + index));

		case E_STRING:
			return cp + index;


		default:
			return NIL;
		}

		return NIL;
	}

	orcaData ex_set_at(orcaVM* vm, int n) 
	{

		if (n < 2) vm->need_param();

		string name = vm->get_param(0).String();
		orcaData value = vm->get_param(1);

		attr_t::iterator it = attr.find(name);
		if (it == attr.end()) {
			throw orcaException(vm, "unsafe.struct", "attr not found");
		}

		pair<int, attr_e> t = it->second;
		int index = t.first;
		attr_e type = t.second;

		switch (type)
		{
		case E_INT8:
			*((char*)(cp + index)) = (char)value.Integer();
			break;

		case E_INT16:
			*((short*)(cp + index)) = (short)value.Integer();
			break;

		case E_INT32:
			*((int*)(cp + index)) = value.Integer();
			break;

		case E_INT64:
			if (is<TYPE_BIGNUM>(value)) {
				double d = get_bn_double(value.bn());
				if (d > LLONG_MAX) {
					throw orcaException(vm, "unsafe.struct", "big int exceed limit");
				}
				else {
					string src = get_bn_string(value.bn());
					long long ret = atoll(src.c_str());
					*((long long*)(cp + index)) = ret;
				}
			}
			else {
				*((long long*)(cp + index)) = value.Integer();
			}
			break;

		case E_UINT8:
			*((unsigned char*)(cp + index)) = (unsigned char)value.Integer();
			break;

		case E_UINT16:
			*((unsigned short*)(cp + index)) = (unsigned short)value.Integer();
			break;

		case E_UINT32:
			if (is<TYPE_BIGNUM>(value)) {
				double d = get_bn_double(value.bn());
				if (d > UINT_MAX) {
					throw orcaException(vm, "unsafe.struct", "big int exceed limit");
				}
				else {
					string src = get_bn_string(value.bn());
					long long ret = atoll(src.c_str());
					*((unsigned int*)(cp + index)) = (unsigned int)ret;
				}
			}
			else {
				*((unsigned int*)(cp + index)) = value.Integer();
			}
			break;

		case E_UINT64:
			if (is<TYPE_BIGNUM>(value)) {
				double d = get_bn_double(value.bn());
				if (d > ULLONG_MAX) {
					throw orcaException(vm, "unsafe.struct", "big int exceed limit");
				}
				else {
					string src = get_bn_string(value.bn());
					char* stop;
					unsigned long long ret = strtoull(src.c_str(), &stop, 10);
					*((unsigned long long*)(cp + index)) = ret;
				}
			}
			else {
				*((unsigned long long*)(cp + index)) = value.Integer();
			}
			break;

		case E_STRING: {
				string str = value.String();
				memcpy(cp + index, str.c_str(), str.length()+1);
				break;
			}
			break;

		default:
			return false;
		}

		return true;
	}

	orcaData ex_pointer(orcaVM* vm, int n) 
	{
		return data;
	}


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


