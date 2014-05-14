#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

int main()
{
	    char uuiditem[100];
	    sprintf(uuiditem, "%s%u", "e2bbc195-6cf7-4475-a175-ee9e972c300e", 8005);
	    std::string tmp(uuiditem);
	    std::cout << tmp << std::endl;
	    if (tmp == "e2bbc195-6cf7-4475-a175-ee9e972c300e8005")
	        std::cout << "right" << std::endl;

	    return 0;
}

