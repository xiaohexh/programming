#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{

	int fd = open("dprintf", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return 1;
	dprintf(fd, "%s\n", "Hello");
	close(fd);
	return 0;
}
