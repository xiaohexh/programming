#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

// file pointer
typedef void (*Print)(const std::string& mesg, int no);

const char* GenerateTime()
{
	static char szTimeString[128];
	memset(szTimeString, 0, sizeof(szTimeString));
	szTimeString[sizeof(szTimeString) - 1] = '\0';

	struct timeval sTimeval;
	struct tm sTM;

	gettimeofday(&sTimeval, NULL);
	std::cout << sTimeval.tv_sec << "." << sTimeval.tv_usec << std::endl;
	localtime_r(&sTimeval.tv_sec, &sTM);

	strftime(szTimeString, 128, "Now it's %I:%M", &sTM);
	std::cout << szTimeString << std::endl;
	sprintf(szTimeString, "%s.%03d", szTimeString, (int)(sTimeval.tv_usec/1000));
	std::cout << szTimeString << std::endl;
	std::cout << sTimeval.tv_usec << std::endl;
}

int main()
{
	GenerateTime();

	for (int i = 0; i < 20; ++ i)
		std::cout << "=";
	std::cout << std::endl;

	time_t now = time(NULL);
	char now_time[128];
	strftime(now_time, sizeof(now_time), "%Y/%m/%d %H:%M", localtime(&now));
	std::cout << now_time << std::endl;
	return 0;
}
