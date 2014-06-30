#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main()
{
	FILE* file;
	char line[BUF_SIZE];
	memset(line, '\0', BUF_SIZE);
	const char* file_name = "/proc/meminfo";
	unsigned total, free, buffer, cache, ap_free;

	if (NULL == (file = fopen(file_name, "r")))
	{
		std::cout << "open /proc/meminfo failed" << std::endl;
		return -1;
	}

	while (NULL != fgets(line, sizeof(line), file))
	{
		if (0 == strncmp(line, "MemTotal:", 9))
		{
			//sscanf(line, "%*s%l64u", &total);
			sscanf(line, "%*s%llu", &total);
		}
		if (0 == strncmp(line, "MemFree:", 8))
		{
			sscanf(line, "%*s%llu", &free);
		}
		if (0 == strncmp(line, "Buffers:", 8))
		{
			sscanf(line, "%*s%llu", &buffer);
		}
		if (0 == strncmp(line, "Cached:", 7))
		{
			sscanf(line, "%*s%llu", &cache);
		}
	}

	fclose(file);
	ap_free = free + buffer + cache;
	double mem_free_rate = (double)ap_free / (double)total;

	std::cout << mem_free_rate << std::endl;

	return 0;
}
