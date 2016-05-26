// sample.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "sample.h"


extern "C" SAMPLE_API void samplefoo()
{
	printf("foo called\n");
}


class sample : public orcaObject
{
public: 
	orcaData operator()(orcaVM* vm, int param_n) {
		printf("sample called\n");

		int a, b;
		a=vm->get_param(0).Integer();
		b=vm->get_param(1).Integer();

		return a+b;
	}
};


extern "C" SAMPLE_API void* get_sample() 
{
	sample* sp = new sample();
	return sp;
}
