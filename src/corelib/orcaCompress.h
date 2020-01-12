
#ifndef _DEF_ORCA_COMPRESS
#define _DEF_ORCA_COMPRESS

#include "porting.h"
#include "orcaUnsafe.h"

struct float64_diff
{
	float64_diff();
	size_t size();
	void dump();

	int get_leading_zeros(unsigned long long value);
	int get_meaning_bits(unsigned long long value, int leading_zeros);
	void float64_append(double value);
	int uncompress(vector<double>& result, int until = INT_MAX);

	orcaBitStream bs;
	long long last_lvalue;
	int count;
	int last_leading_zeros;
	int last_meaning_bits;
};


struct int64_diff
{
	int64_diff();
	size_t size();
	void dump();

	void int64_append(long long value);
	void diff_diff_append(long long value);
	int uncompress(vector<long long>& result, int until = INT_MAX);

	orcaBitStream bs;
	long long last_value;
	long long last_diff;
	int count;
};


class orcaTsDiff : public orcaObject 
{
public:
	orcaTsDiff(void* vp) {}
	orcaTsDiff()
	{
		set_name("tsdiff");
		insert_native_function("init", (object_fp)&orcaTsDiff::ex_init);
		insert_native_function("count", (object_fp)&orcaTsDiff::ex_count);
		insert_native_function("size", (object_fp)&orcaTsDiff::ex_size);
		insert_native_function("push_back", (object_fp)&orcaTsDiff::ex_push_back);
		insert_native_function("uncompress", (object_fp)&orcaTsDiff::ex_uncompress);
	}

	~orcaTsDiff() { }

	orcaObject* v_clone()
	{
		orcaTsDiff* op = new orcaTsDiff(NULL);
		return op;
	}

	orcaData ex_init(orcaVM* vm, int n);
	orcaData ex_count(orcaVM* vm, int n);
	orcaData ex_size(orcaVM* vm, int n);
	orcaData ex_push_back(orcaVM* vm, int n);
	orcaData ex_uncompress(orcaVM* vm, int n);

	int count();

private:
	int ts_precision; // -1: double, 0: integer, >1: per n
	int precision; // -1: double, 0: integer, >1: per n

	int64_diff its;
	float64_diff dts;
	int64_diff iv;
	float64_diff dv;
};




class orcaCompress : public orcaObject 
{
public:
	DEFAULT_NATIVE_DEFINE(orcaCompress);

	orcaCompress() 
	{
		insert_member("tsdiff", new orcaTsDiff());
	}
};


#endif


