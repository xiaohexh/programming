#include <iostream>
#include <string>
#include <utility>

class Test
{
public:
	Test(const std::string& name = "unknown");

	std::string _name;
};

Test::Test(const std::string& name)
{
	_name = name;
}

int main()
{
	std::auto_ptr<int> p(new int(3));
	//std::auto_ptr<Test> p(new Test());
	//std::cout << p->_name << std::endl;

	return 0;
}
