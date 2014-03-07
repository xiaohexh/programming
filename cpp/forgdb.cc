#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

std::string gName("Chris");

class Print
{
public:
	// overload 
	// break Print::print()
	int print();

	// break Print::print(const std::string&)
	int print(const std::string& name);
};

int Print::print()
{
	std::cout << gName << std::endl;
	return 0;
}

int Print::print(const std::string& name)
{
	std::cout << name << std::endl;
	return 0;
}

int main(int argc, char** argv)
{
	if (argc < 2)  // set args
	{
		std::cout << "Usage:" << basename(argv[0]) << " username" << std::endl;
		return 1;
	}

	Print obj;
	int pid = fork();
	if (pid == 0)
	{
		// child process
		std::cout << "In Child, child's pid:" << getpid() << std::endl;
		std::cout << "In Child, parent's pid:" << getppid() << std::endl;
		std::cout << "child process" << std::endl;
		obj.print();
		exit(0);
	}
	else if (pid < 0)
	{
		std::cout << "error! err msg:" << strerror(errno) << std::endl;
	}

	std::cout << "parent's pid:" << getpid() << std::endl;
	std::string name(argv[1]);
	obj.print(name);

	waitpid(pid, NULL, NULL);

	return 0;
}
