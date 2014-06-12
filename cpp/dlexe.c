#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#define MAX_STRING 80

void invoke_method(char* lib, char* method, float argument)
{
	void* dl_handle = NULL;
	float (*func)(float);
	char* error = NULL;

	// open the shared object
	dl_handle = dlopen(lib, RTLD_LAZY);
	if (!dl_handle)
	{
		printf("dlopen failed\n");
		return;
	}

	// resolve the symbol from the object
	func = dlsym(dl_handle, method);
	error = dlerror();
	if (error != NULL)
	{
		printf("dlsym failed\n");
		return;
	}

	// call the solved method
	printf(" %f\n", (*func)(argument));

	// close the object
	dlclose(dl_handle);

	return;
}

int main(int argc, char** argv)
{
	char line[MAX_STRING + 1];
	char lib[MAX_STRING + 1];
	char method[MAX_STRING + 1];
	float argument;

	while (1)
	{
		printf("> ");
		fgets(line, MAX_STRING, stdin);
		if (!strncmp(line, "bye", 3))
		{
			printf("bye-bye!\n");
			break;
		}

		sscanf(line, "%s %s %f", lib, method, &argument);
		invoke_method(lib, method, argument);
	}

	return 0;
}
