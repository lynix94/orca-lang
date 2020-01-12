
#include "orcaUnsafe.h"
#include "orcaException.h"


orcaPointer::orcaPointer() 
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



orcaData orcaPointer::ex_str(orcaVM* vm, int n) 
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

orcaData orcaPointer::ex_int8(orcaVM* vm, int n) 
{
	return int_cast_helper<char>(vm, n);
}

orcaData orcaPointer::ex_int16(orcaVM* vm, int n) 
{
	return int_cast_helper<short>(vm, n);
}

orcaData orcaPointer::ex_int32(orcaVM* vm, int n) 
{
	return int_cast_helper<int>(vm, n);
}

orcaData orcaPointer::ex_int64(orcaVM* vm, int n) 
{
	return bigint_cast_helper<int>(vm, n, 8);
}

orcaData orcaPointer::ex_uint8(orcaVM* vm, int n) 
{
	return int_cast_helper<unsigned char>(vm, n);
}

orcaData orcaPointer::ex_uint16(orcaVM* vm, int n) 
{
	return int_cast_helper<unsigned short>(vm, n);
}

orcaData orcaPointer::ex_uint32(orcaVM* vm, int n) 
{
	return bigint_cast_helper<int>(vm, n, 4);
}

orcaData orcaPointer::ex_uint64(orcaVM* vm, int n) 
{
	return bigint_cast_helper<int>(vm, n, 8);
}

orcaData orcaPointer::ex_float32(orcaVM* vm, int n) 
{
	return float_cast_helper<float>(vm, n);
}

orcaData orcaPointer::ex_float64(orcaVM* vm, int n) 
{
	return float_cast_helper<double>(vm, n);
}








orcaStruct::orcaStruct(orcaData p, int i) 
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

orcaData orcaStruct::ex_at(orcaVM* vm, int n) 
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

orcaData orcaStruct::ex_set_at(orcaVM* vm, int n) 
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


orcaData orcaStruct::attr_helper(orcaVM* vm, int n, attr_e e)
{
	if (n < 2) vm->need_param();

	string name = vm->get_param(0).String();
	int index = vm->get_param(1).Integer();

	attr[name] = pair<int, attr_e>(index, e);
}

orcaData orcaStruct::ex_int8(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_INT8);
}

orcaData orcaStruct::ex_int16(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_INT16);
}

orcaData orcaStruct::ex_int32(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_INT32);
}

orcaData orcaStruct::ex_int64(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_INT64);
}

orcaData orcaStruct::ex_uint8(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_UINT8);
}

orcaData orcaStruct::ex_uint16(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_UINT16);
}

orcaData orcaStruct::ex_uint32(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_UINT32);
}

orcaData orcaStruct::ex_uint64(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_UINT64);
}

orcaData orcaStruct::ex_float32(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_FLOAT32);
}

orcaData orcaStruct::ex_float64(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_FLOAT64);
}

orcaData orcaStruct::ex_str(orcaVM* vm, int n) 
{
	return attr_helper(vm, n, E_STRING);
}

orcaData orcaStruct::ex_pointer(orcaVM* vm, int n) 
{
	return data;
}



orcaBitStream::orcaBitStream() : bit_size(0)
{
	set_name("bitstream");
	insert_native_function("hexdump", (object_fp)&orcaBitStream::ex_hexdump);
	insert_native_function("size", (object_fp)&orcaBitStream::ex_size);
	insert_native_function("bitget", (object_fp)&orcaBitStream::ex_bitget);
	insert_native_function("bitset", (object_fp)&orcaBitStream::ex_bitset);
	insert_native_function("bitappend", (object_fp)&orcaBitStream::ex_bitappend);
}


long long orcaBitStream::bitget(int bit_idx, int size)
{
	long long ret = 0;
	for (int i=0; i<size; i++) {
		int byte_idx = bit_idx/8;
		int bit_offset = bit_idx%8;

		char b = data[byte_idx];
		if (b & ((long long)1 << bit_offset)) {
			ret |= ((long long)1 << i);
		}
		bit_idx++;
	}

	return ret;
}

void orcaBitStream::bitset(int bit_idx, int size, long long value)
{
	for (int i=0; i<size; i++) {
		int byte_idx = bit_idx/8;
		int bit_offset = bit_idx%8;

		char b = data[byte_idx];
		if (value & ((long long)1 << i)) {
			data[byte_idx] = b | ((long long)1 << bit_offset);
		} else {
			data[byte_idx] = b & ~((long long)1 << bit_offset);
		}

		bit_idx++;
	}
}

size_t orcaBitStream::bitappend(int size, long long value)
{
	//printf("bitappend: %d, %lld, at:%d\n", size, value, bit_size);
	for (int i=0; i<size; i++) {
		int byte_idx = bit_size/8;
		int bit_offset = bit_size%8;

		if (bit_offset == 0) {
			if (value & ((long long)1 << i)) {
				data.push_back(1);
			}
			else {
				data.push_back(0);
			}
		}
		else {
			char b = data[byte_idx];
			if (value & ((long long)1 << i)) {
				data[byte_idx] = b | ((long long)1 << bit_offset);
			}
		}

		bit_size++;
	}

	return bit_size;
}

orcaData orcaBitStream::ex_size(orcaVM* vm, int n)
{
	if (bit_size < INT_MAX) {
		return (int)bit_size;
	}

	return bit_size;
}


orcaData orcaBitStream::ex_bitget(orcaVM* vm, int n)
{
	if (n < 2) vm->need_param(2);

	int index = vm->get_param(0).Integer();
	int size = vm->get_param(1).Integer();

	long long ret = bitget(index, size);
	if (ret < INT_MAX) {
		return (int)ret; // return as int
	}

	return ret; // return as bignum
}


orcaData orcaBitStream::ex_bitset(orcaVM* vm, int n)
{
	if (n < 3) vm->need_param(3);

	int index = vm->get_param(0).Integer();
	int size = vm->get_param(1).Integer();
	orcaData value = vm->get_param(2);

	if (is<TYPE_INT>(value)) {
		bitset(index, size, value.Integer());
	}
	else if (is<TYPE_BIGNUM>(value)) {
		double d = get_bn_double(value.bn());
		if (d > LLONG_MAX) {
			throw orcaException(vm, "unsiafe.bit", "exceed long64");
		}

		long long ll = boost::lexical_cast<long long>(get_bn_string(value.bn()));
		bitset(index, size, ll);
	}
	else {
		throw orcaException(vm, "unsiafe.bit", "not an integer type");
	}

	return NIL;
}


orcaData orcaBitStream::ex_bitappend(orcaVM* vm, int n)
{
	if (n < 2) vm->need_param(2);

	int size = vm->get_param(0).Integer();
	orcaData value = vm->get_param(1);

	long long ll;
	if (is<TYPE_INT>(value)) {
		ll = value.Integer();
	}
	else if (is<TYPE_BIGNUM>(value)) {
		double d = get_bn_double(value.bn());
		if (d > LLONG_MAX) {
			throw orcaException(vm, "unsiafe.bit", "exceed long64");
		}

		ll = boost::lexical_cast<long long>(get_bn_string(value.bn()));
	}
	else {
		throw orcaException(vm, "unsiafe.bit", "not an integer type");
	}

	bitappend(size, ll);
	if (bit_size < INT_MAX) {
		return (int)bit_size;
	}

	return bit_size;
}

orcaData orcaBitStream::ex_hexdump(orcaVM* vm, int n)
{
	for (int i=0; i<data.size(); i++) {
		printf("%02x ", (unsigned char)data[i]);
	}
	printf("\n");
	return NIL;
}



