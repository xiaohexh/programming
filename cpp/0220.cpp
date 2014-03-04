#include <iostream>
#include <string.h>

static const char* HELP_MSG[] =
{
	"-i,--index		index,		worker",
	"-h,--help					show help",
	"-c,--config	configfile,	indicate file"
};

int main()
{
	int len = sizeof(HELP_MSG) / sizeof(HELP_MSG[0]);
	std::cout << "len:" << len << std::endl;
	for(int i = 0; i < len; ++i)
		std::cout << HELP_MSG[i] << std::endl;

	const char *name_1 = "Chris Xiao";
	const char *name_2 = "chris yiao";
	int cmp_len = 6;
	if(0 == strncasecmp(name_1, name_2, cmp_len))
	{
		std::cout << "Pre " << cmp_len << " characters are Same" << std::endl;
	}
	else
	{
		std::cout << "Pre " << cmp_len << " characters are Different" << std::endl;
	}

	return 0;
}
