#include <math.h>

#include "orcaCompress.h"
#include "orcaList.h"
#include "orcaTuple.h"

float64_diff::float64_diff()
{
	count = 0;
	last_lvalue = 0;
	last_leading_zeros = 0;
	last_meaning_bits = 64;
}

size_t float64_diff::size()
{
	return bs.size();
}

void float64_diff::dump()
{
	bs.ex_hexdump(NULL, 0);
}


int float64_diff::get_leading_zeros(unsigned long long value)
{
	for (int i=0; i<64; i++) {
		if (value & 0x8000000000000000) {
			return i;
		}

		value <<= 1;
	}

	return 64;
}

int float64_diff::get_meaning_bits(unsigned long long value, int leading_zeros)
{
	int tail = 0;
	for (; tail<64; tail++) {
		if (value & 0x01) {
			break;
		}

		value >>= 1;
	}

	return 64 - leading_zeros - tail;
}

// timestamp
// 0: same
// 10: leading zero, meaningfull is same, sotre xor value
//    10XXXX (same leanth with prev)
// 11: leading zero 5bit, meaningfull length is 6bit, then xor value
//    11ZZZZZMMMMMMXXXXXXXXXX (leading zero 32, meaningfull 64)
void float64_diff::float64_append(double value)
{
	unsigned long long lvalue = *(unsigned long long*)&value;

	//printf("# float64 append(size:%d): %016llx, %f (last:%016llx)\n", count, lvalue, value, last_lvalue);
	do {
		if (count == 0) {
			bs.bitappend(64, lvalue);
			break;
		}

		unsigned long long diff = lvalue ^ last_lvalue;
		if (diff == 0) {
			//printf("# 00 append: 0\n");
			bs.bitappend(1, 0);
			break;
		}

		int leading_zeros = get_leading_zeros(diff);
		int meaning_bits = get_meaning_bits(diff, leading_zeros);
		int tail = 64 - leading_zeros - meaning_bits;
		diff >>= tail;

		//printf("diff: %016llx, z:%d-%d, m:%d-%d\n", diff, leading_zeros, last_leading_zeros, meaning_bits, last_meaning_bits);

		if (leading_zeros == last_leading_zeros &&
			meaning_bits == last_meaning_bits)
		{
			//printf("# 01 append: z:%d, m:%d, %016llx\n", leading_zeros, meaning_bits, diff);
			bs.bitappend(2, 1); // 01
			bs.bitappend(last_meaning_bits, diff);
		}
		else {
			//printf("# 11 append: z:%d, m:%d, %016llx\n", leading_zeros, meaning_bits, diff);
			bs.bitappend(2, 3); // 11
			bs.bitappend(5, leading_zeros);
			bs.bitappend(6, meaning_bits);
			bs.bitappend(meaning_bits, diff);

			last_leading_zeros = leading_zeros;
			last_meaning_bits = meaning_bits;
		}
	} while(false);
	
	count++;
	last_lvalue = lvalue;
}

int float64_diff::uncompress(vector<double>& result, double until, int limit)
{
	if (limit > count) {
		limit = count;
	}

	//printf("# uncompress: %d\n", count);
	int idx = 0;
	int c = 0;

	unsigned long long first_value = bs.bitget(idx, 64);
	//printf("# first: %lld, %f\n", first_value, *(double*)&first_value);
	result.push_back(*(double*)&first_value);
	c++, idx += 64;
	if (c > limit) {
		return c;
	}

	int last_leading_zeros = 0;
	int last_meaning_bits = 64;
	unsigned long long last_value = first_value;
	unsigned long long diff;
	unsigned long long value;

	do {
		char tag = bs.bitget(idx, 2);
		if ((tag & 0x01) == 0) { // x0. same diff_diff
			diff = 0;
			value = last_value;
			idx += 1;
		}
		else if (tag == 1) { // 01. same leading zeros, meaning bits
			diff = bs.bitget(idx+2, last_meaning_bits);

			int tail = 64 - last_leading_zeros - last_meaning_bits;
			diff <<= tail;

			value = last_value ^ diff;
			idx += (2+last_meaning_bits);
		}
		else if (tag == 3) { // 11
			idx += 2;
			int leading_zeros = bs.bitget(idx, 5);
			idx += 5;
			int meaning_bits = bs.bitget(idx, 6);
			idx += 6;
			diff = bs.bitget(idx, meaning_bits);
			idx += meaning_bits;

			int tail = 64 - leading_zeros - meaning_bits;
			diff <<= tail;

			last_leading_zeros = leading_zeros;
			last_meaning_bits = meaning_bits;;

			value = last_value ^ diff;
		}
		else {
			// error
		}

		//printf("## tag: %d, diff: %016llx, value: %016llx, value: %f\n", tag & 0x03, diff, value, *(double*)&value);

		if (until >= 0 && *(double*)&value >= until) {
			break;
		}

		result.push_back(*(double*)&value);
		last_value = value;
		c++;
	} while(c < limit);
}



int64_diff::int64_diff()
{
	count = 0;
	last_value = 0;
	last_diff = 0;
}

size_t int64_diff::size()
{
	return bs.size();
}

void int64_diff::dump()
{
	bs.ex_hexdump(NULL, 0);
}

void int64_diff::int64_append(long long value)
{
	//printf("# int64 append(size:%d): %lld\n", count, value);
	if (count == 0) {
		bs.bitappend(64, value);
	}
	else if (count == 1) {
		last_diff = value - last_value;
		bs.bitappend(64, value);
	}
	else {
		long long diff = value - last_value;
		long long diff_diff = diff - last_diff;
		last_diff = diff;
		diff_diff_append(diff_diff);
	}
	
	count++;
	last_value = value;
}

// timestamp
// 0: same
// 10xx xxxx: -63 ~ 64, 6bit
// 110x xxxx xxxx xxxx: -8191, 8192, 13bit
// 1110 xxxx xxxx xxxx xxxx xxxx xxxx xxxx: -268435455, 268435456, 28bit
// 1111 xxxx*: 64bit
void int64_diff::diff_diff_append(long long value)
{
	if (value == 0) {
		bs.bitappend(1, 0);
		return;
	}

	if (value > -63 && value < 64) {
		bs.bitappend(2, 1); // 01
		bs.bitappend(6, value);
		return;
	}
	
	if (value > -8191 && value < 8192) {
		bs.bitappend(3, 3); //  011
		bs.bitappend(13, value);
		return;
	}
	
	if (value > -268435455 && value < 268435456) {
		bs.bitappend(4, 7); // 0111
		bs.bitappend(28, value);
		return;
	}

	bs.bitappend(4, 15); // 1111
	bs.bitappend(64, value);
}

int int64_diff::uncompress(vector<long long>& result, long long until, int limit)
{
	if (limit > count) {
		limit = count;
	}

	//printf("# uncompress: %d\n", count);
	int idx = 0;
	int c = 0;

	long long first_value = bs.bitget(idx, 64);
	//printf("# first: %lld\n", first_value);
	result.push_back(first_value);
	c++, idx += 64;
	if (c > limit) {
		return c;
	}

	long long second_value = bs.bitget(idx, 64);
	//printf("# second: %lld\n", second_value);
	result.push_back(second_value);
	c++, idx += 64;
	if (c > limit) {
		return c;
	}

	long long last_value = second_value;
	long long last_diff = second_value - first_value;

	long long diff_diff;
	do {
		char tag = bs.bitget(idx, 4);
		if ((tag & 0x01) == 0) { // same diff_diff
			diff_diff = 0;
			idx+=1;
		}
		else if ((tag & 0x03) == 1) { // xx01
			diff_diff = bs.bitget(idx+2, 6);
			if (diff_diff & 0x20) {
				diff_diff = (long long)(0xFFFFFFFFFFFFFFC0) | diff_diff;
			}
			idx+=8;
		}
		else if ((tag & 0x07) == 3) { // x011
			diff_diff = bs.bitget(idx+3, 13);
			if (diff_diff & 0x1000) {
				diff_diff = (long long)(0xFFFFFFFFFFFFE000) | diff_diff;
			}
			idx+=16;
		}
		else if ((tag & 0x0F) == 7) { // 0111
			diff_diff = bs.bitget(idx+4, 28);
			if (diff_diff & 0x10000000000000) {
				diff_diff = (long long)(0xFFFFFFFFF0000000) | diff_diff;
			}
			idx+=32;
		}
		else if ((tag & 0x0F) == 15) { // 1111
			diff_diff = bs.bitget(idx+4, 64);
			idx+=4+64;
		}
		else {
			// error
		}

		long long diff = last_diff + diff_diff;
		long long value = last_value + diff;

		//printf("## diff_diff: %lld, diff: %lld, value: %lld, idx:%d, last_diff: %lld, last_value: %lld\n", diff_diff, diff, value, idx, last_diff, last_value);

		if (until >= 0 && value >= until) {
			break;
		}

		result.push_back(value);
		last_value = value;
		last_diff = diff;
		c++;
	} while(c < limit);
}



orcaData orcaTsDiff::ex_init(orcaVM* vm, int n)
{
	if (n == 0) {
		ts_precision = 3;
		precision = -1;
	}

	if (n >= 1) {
		ts_precision = vm->get_param(0).Integer();
		if (ts_precision > 6) {
			throw orcaException(vm, "precision should be lower than 6");
		}
	}

	if (n >= 2) {
		precision = vm->get_param(1).Integer();
		if (precision > 6) {
			throw orcaException(vm, "precision should be lower than 6");
		}
	}

	return NIL;
}

int orcaTsDiff::count()
{
	if (ts_precision >= 0) {
		return its.count;
	}
	else {
		return dts.count;
	}
}

orcaData orcaTsDiff::ex_count(orcaVM* vm, int n)
{
	return count();
}

orcaData orcaTsDiff::ex_size(orcaVM* vm, int n)
{
	return its.size() + dts.size() + iv.size() + dv.size();
}

orcaData orcaTsDiff::ex_push_back(orcaVM* vm, int n)
{
	if (n != 2) {
		vm->need_param(2);
	}

	if (ts_precision == 0) {
		its.int64_append(vm->get_param(0).Integer());
	}
	else if (ts_precision > 0) {
		double d = vm->get_param(0).Double();
		d *= pow(10, precision);
		long long v = (long long)d;
		its.int64_append(v);
	}
	else {
		dts.float64_append(vm->get_param(0).Double());
	}

	if (precision == 0) {
		iv.int64_append(vm->get_param(1).Integer());
	}
	else if (precision > 0) {
		double d = vm->get_param(1).Double();
		d *= pow(10, precision);
		long long v = (long long)d;
		iv.int64_append(v);
	}
	else {
		dv.float64_append(vm->get_param(1).Double());
	}
	
	return NIL;
}

orcaData orcaTsDiff::ex_uncompress(orcaVM* vm, int n)
{
	double until = -1;
	int limit = INT_MAX;

	if (n >= 1) {
		until = vm->get_param(0).Double();
	}
	if (n >= 2) {
		limit = vm->get_param(1).Integer();
	}

	vector<long long> its_result;
	vector<double> dts_result;
	if (ts_precision == 0) {
		its.uncompress(its_result, (long long)until, limit);
		limit = its_result.size();
	}
	else if (ts_precision > 0) {
		its.uncompress(its_result, (long long)until, limit);
		limit = its_result.size();
		for (int i=0; i<count(); i++) {
			double d = (double)its_result[i] / pow(10, ts_precision);
			dts_result.push_back(d);
		}
	}
	else {
		dts.uncompress(dts_result, until, limit);
		limit = dts_result.size();
	}

	vector<long long> iresult;
	vector<double> dresult;
	if (precision == 0) {
		iv.uncompress(iresult, -1, limit);
	}
	else if (precision > 0) {
		iv.uncompress(iresult, -1, limit);

		for (int i=0; i<count(); i++) {
			double d = (double)iresult[i] / pow(10, precision);
			dresult.push_back(d);
		}
	}
	else {
		dv.uncompress(dresult, -1, limit);
	}

	orcaList *lp = new orcaList();
	for (int i=0; i<limit; i++) {
		orcaTuple *tp = new orcaTuple(2);

		if (ts_precision == 0) {
			tp->update(0, its_result[i]);
		}
		else {
			tp->update(0, dts_result[i]);
		}

		if (precision == 0) {
			tp->update(1, iresult[i]);
		}
		else {
			tp->update(1, dresult[i]);
		}

		lp->push_back(tp);
	}
	
	return lp;
}





