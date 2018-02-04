/**********************************************************************

  orcaSwitchStack.h - class for handling "switch statement"

  Copyright (C) 2009- Lee, Ki-Yeul

**********************************************************************/

#ifndef _DEF_ORCA_SWITCH_STACK
#define _DEF_ORCA_SWITCH_STACK

class orcaVM;

class orcaSwitchStack
{
public:
	orcaSwitchStack(orcaVM* vm) : m_vm(vm) {};

	struct SWITCH 
	{
		orcaData lhs;
	};

	bool push(orcaData& d)
	{
		SWITCH sw;
		sw.lhs = d;
		m_stack.push_back(sw);
	};

	SWITCH* top()
	{
		if (m_stack.empty()) {
			return NULL;
		}

		SWITCH *sw = &m_stack[m_stack.size()-1];
		return sw;
	};

	void pop()
	{
		m_stack.pop_back();
	};

	bool compare(orcaData &rhs)
	{
		SWITCH* sw = top();
		return sw->lhs == rhs;
	};

private:
	vector<SWITCH> m_stack;
	orcaVM* m_vm;
};


#endif


