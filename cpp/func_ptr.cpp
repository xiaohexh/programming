#include <iostream>
#include <string>

class Person
{
public:
	Person();

	void SetName(const std::string& n);
	void SetAge(int a);

	std::string Name() const;
	int Age() const;

private:
	std::string m_sName;
	int			m_iAge;
};

Person::Person()
	: m_sName()
	, m_iAge(0)
{
}

void Person::SetName(const std::string& n)
{
	m_sName = n;
}

void Person::SetAge(int a)
{
	m_iAge = a;
}

std::string Person::Name() const
{
	return m_sName;
}

int Person::Age() const
{
	return m_iAge;
}

void Prompt(int* num, std::string& msg)
{
	std::string help[] =
	{
		"--version		version of software;",
		"--usage		usage of this software"
	};

	int len = sizeof(help) / sizeof(help[0]);
	std::cout << "Prompt:: len = " << len << std::endl;
	for (int i = 0; i < len; ++i)
		std::cout << help[i] << std::endl;
}

int main()
{
	// C-style function pointer
	typedef void (*FUNC_PTR)(int* num, std::string& msg);
	FUNC_PTR pprompt = NULL; 
	pprompt = &Prompt;
	int a = 3;
	std::string msg("Hello");
	pprompt(&a, msg);

	Person person;
	person.SetName(msg);
	person.SetAge(a);
	std::cout << "Name:" << person.Name() << std::endl;
	std::cout << "Age:"  << person.Age()  << std::endl;
	// C++-style function pointer
	void (Person::*mem_name)(const std::string& n) = NULL;
	mem_name = &Person::SetName;
	(person.*mem_name)(msg);
	std::cout << "Name:" << person.Name() << std::endl;

	return 0;
}
