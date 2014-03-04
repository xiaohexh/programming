#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

const std::string FileName("/tmp/fifo");

int main()
{
    int n = 0;

    int ret = mkfifo(FileName.c_str(), S_IFIFO | 0666);
    if (0 != ret)
    {
        std::cout << "create fifo failed!" << std::endl;
        return 1;
    }

    std::string user_name("Chris");

    std::cout << "create fifo success!" << std::endl;
    int fd = open(FileName.c_str(), O_RDWR | O_APPEND, 0755);
    char buffer[] = "Hello Chris I want to a programmer, because I like it\
					 very much. So I come to UCloud.cn to learn and work here.";
    if ((n = write(fd, buffer, sizeof(buffer))) > 0)
    {
        std::cout << "write success!" << std::endl;
    }
    //close(fd);

    //fd = open(FileName.c_str(), O_RDWR);
    char buff[8];
    memset(buff, 0, sizeof(buff));
    buff[sizeof(buff) - 1] = '\0';
    while (1)
    {
        if ((n = read(fd, buff, sizeof(buff) - 1)) > 0)
            std::cout << buff << std::endl;
        else
            break;
    }
    close(fd);

    return 0;
}
