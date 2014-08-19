#include <stdio.h>

//------------------------------
// Read 'n' bytes from a descriptor.
//------------------------------
ssize_t readn(int fd, void* vptr, size_t n)
{
	size_t	nleft;
	size_t	nread;
	char*	ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if (nread = read(fd, ptr, nleft) < 0)
		{
			if (errno == EINTR)
				nread = 0;  // and call read() again
			else
				return -1;
		}
		else if (nread == 0)
			break;

		nleft -= nread;
		ptr += nread;
	}

	return (n - nleft);
}

ssize_t writen(int fd, void* vptr, size_t n)
{
	size_t nleft;
	size_t nwrite;
	char* ptr;

	ptr = vptr;
	while (nleft > 0)
	{
		if (nwrite = write(fd, ptr, nleft) <= 0)
		{
			if (nwrite < 0 && errno == EINTR)
				nwrite = 0;
			else
				return -1;
		}

		nleft -= nwrite;
		ptr += nwrite;
	}

	return n;
}
