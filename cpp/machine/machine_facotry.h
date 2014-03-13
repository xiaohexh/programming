#include "state_machine.h"

typedef StateMachine *(*MachineCreate_t)();

class MachineFactory
{
public:
	MachineFactory();
};
