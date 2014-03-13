#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

std::string& StateMachine::Name() const
{
	return m_sName;
}

int StateMachine::Id() const
{
	return m_iId;
}
