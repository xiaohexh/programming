#include "file_sys.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>

int FileSys::MakeDir(const char *pPath, mode_t iMode)
{

}

int FileSys::StrtoKCPP(char* str, const char* sep)
{
	std::string origin(str);
	std::string del(sep)
	std::cout << count(origin.begin(), origin.end(), del) << std::endl;
	//std::cout << "xx :" << counter << std::endl;
	return 0;
}

int FileSys::StrtoK(char* str, const char* sep)
{
	char origin[20] = "Andy,Chris,Jenny";
    char *name[5];

    int	count = 0;
    int	index = 0;
    char* buf = origin;
	std::cout << "buf : " << buf << std::endl;

    while (NULL != (name[index] = strtok(buf, sep)))
	{
        buf = name[index];
		std::cout << "buf : " << buf << std::endl;
        while (NULL != (name[index] = strtok(buf," ")))
		{
            ++ index;
            buf = NULL;
        }
        name[index++] = "***"; //表现分割
        buf = NULL;
    }

    std::cout << "name[0]:" << name[0] << std::endl;
    std::cout << "name[1]:" << name[1] << std::endl;
    std::cout << "name[2]:" << name[2] << std::endl;
    return count;
}
