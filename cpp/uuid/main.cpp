#include "my_uuid.h"
#include <iostream>

int main()
{
	MyUuid myuuid;
	std::cout << "uuid:" << myuuid.Uuid() << std::endl;
	std::cout << "uuid string:" << myuuid.UuidString() << std::endl;

	std::cout << myuuid.NewUuid() << std::endl;

	return 0;
}
