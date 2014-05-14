#include <iostream>
#include <string>

typedef struct
{
	std::string name;
	int			age;
	double		score;
}student;

student ming =
{
	name: "xiao ming",
	age: 23,
	score: 2.3,
};

struct MyReturn
{
	enum ErrorCode
	{
		SUCCESS = 0,
		WARN,
		FAIL,
		INVALID_PARAM,
		UNKNOWN
	};
};

MyReturn::ErrorCode Handle()
{
	return MyReturn::INVALID_PARAM;
}

int main()
{
	std::cout << ming.name << std::endl;
	std::cout << ming.age << std::endl;

	std::cout << MyReturn::SUCCESS << std::endl;
	std::cout << MyReturn::FAIL << std::endl;
	std::cout << Handle() << std::endl;

	return 0;
}
