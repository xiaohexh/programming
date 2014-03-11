#include <iostream>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

const int UUIDLEN = 37;

int main()
{
	uuid_t	uu;
	char	uu_str[UUIDLEN];
	memset(uu_str, '\0', UUIDLEN);
	uuid_generate(uu);
	uuid_unparse(uu, uu_str);

	std::cout << "uuid length:" << strlen(uu_str) << std::endl;

	std::cout << "uuid generated:" << uu << std::endl;
	std::cout << "uuid generated:" << uu_str << std::endl;

	uuid_t	dst;
	uuid_parse(uu_str, dst);
	std::cout << "uuid generated:" << dst << std::endl;

	return 0;
}
