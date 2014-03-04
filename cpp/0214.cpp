#include <iostream>
#include <stdlib.h>
#include <string.h>

int main()
{
	char* name = "Andy";
	char* cpname = strdup(name);
	std::cout << cpname << std::endl;

	std::cout << sizeof(*name) << std::endl;
	std::cout << strlen(name) << std::endl;
	char* subname = strndup(name, strlen(name) - 1);
	std::cout << subname << std::endl;

	// DO NOT Forget to free memory allocated by strdup/strndup
	free(cpname);
	free(subname);

	return 0;	
}
