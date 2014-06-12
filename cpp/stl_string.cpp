#include <iostream>
#include <string>

int main()
{
	std::string message("Hello");
	std::cout << message << " " << message.size() << std::endl;
	std::cout << message.data() << " " << message.length() << std::endl;

	return 0;
}
