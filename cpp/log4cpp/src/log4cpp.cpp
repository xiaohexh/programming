#include <iostream>
#include "Priority.hh"

int main()
{
	log4cpp::Priority obj;
	std::cout << obj.getPriorityValue("EMERG") << std::endl;

	return 0;
}
