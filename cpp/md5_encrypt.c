#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>

int main()
{
	unsigned char	*data = "Hello";
	unsigned char	md[16];
	int				i = 0;
	char			tmp[3] = {'\0'};
	char			buf[33] = {'\0'};
	MD5(data, strlen(data), md);
	
	for (i = 0; i < 16; ++i)
	{
		printf("%x", md[i]);
		//sprintf(tmp, "%2.2x", md[i]);
		//strcat(buf, tmp);
	}	
	printf("%s\n", buf);

	return 0;
}
