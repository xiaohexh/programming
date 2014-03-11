#include <iostream>
#include "file_sys.h"

int main()
{
	FileSys filesys;
	char* multi_name = "John,Chris,Andy";
	char* sep = ",";
	int count = filesys.StrtoK(multi_name, sep);
	
	return 0;
}
