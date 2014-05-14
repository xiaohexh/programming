#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "event.h"

int main()
{
	struct evbuffer* buff = NULL;
	char c, c2[3] = {0};

	buff = evbuffer_new();
	assert(buff != NULL);

	evbuffer_add(buff, "1", 1);
	evbuffer_add(buff, "2", 1);
	evbuffer_add(buff, "3", 1);
	evbuffer_add_printf(buff, "Hello, %s, I'm %d", "Chris", 30);
	assert(buff->off == 20);
	
	evbuffer_free(buff);

	return 0;
}
