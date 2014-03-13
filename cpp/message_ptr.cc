#include <iostream>
#include <string>

template <typename T>
class MessagePtr
{
public:
	typedef T element_type;

	MessagePtr(element_type* ptr)
	{
		p = ptr;
	}

	~MessagePtr()
	{
		if (p)
		{
			delete p;
			p = NULL;
		}
	}

	element_type& operator*() const
	{
		return *p;
	}

	element_type* operator->() const
	{
		return p;
	}

private:
	element_type *p;
};

class Person
{
public:
	Person()
		: m_iAge(0){}

	Person(std::string n, int a)
		: m_sName(n)
		, m_iAge(a){}

	void SetName(const std::string& name)
	{
		m_sName = name;
	}

	void SetAge(const int age)
	{
		m_iAge = age;
	}

	std::string Name() const
	{
		return m_sName;
	}

	int Age() const
	{
		return m_iAge;
	}

private:
	std::string m_sName;
	int			m_iAge;
};


int main()
{
	MessagePtr<Person> p(new Person); 	
	p->SetName("Andy");
	(*p).SetAge(70);
	std::cout << p->Name() << std::endl;
	std::cout << (*p).Age() << std::endl;

	return 0;
}
