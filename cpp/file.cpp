#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

const std::string gFileName("/home/admin/program/shell/dir.sh");

int main()
{
    if (0 != access(gFileName.c_str(), R_OK))
    {
        std::cout << "File:" << gFileName << " is not exist!" << std::endl;
    }
    else
    {
        std::cout << "========================" << std::endl;
        struct stat file_stat;
        lstat(gFileName.c_str(), &file_stat);

        std::cout << "File:" << gFileName << " is exist, and its size:" << file_stat.st_size << std::endl;
    }

	// extract file name in a path
    const char* p = strrchr(gFileName.c_str(), '/');
	char sub_file_name[20];
    if (NULL == p)
    {
        std::cout << "Cannot find character '/'" << std::endl;
    }
    else
    {
        std::cout << *p << std::endl;
		strcpy(sub_file_name, p + 1);
        std::cout << sub_file_name << std::endl;
    }

    return 0;
}
