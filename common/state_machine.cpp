#include "state_machine.h"

State_Machine* State_Machine::intance_ = GetIntance();
static State_Machine::Destory destory;

State_Machine::State_Machine(QObject* parent)
{
}
State_Machine::~State_Machine()
{
}

State_Machine* State_Machine::GetIntance()
{
	if (nullptr == intance_)
	{
		intance_ = new State_Machine;
	}
	return intance_;
}
