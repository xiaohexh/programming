#include "singleton.h"

#include <iostream>
#include <stdio.h>

pthread_mutex_t Lock::m_mutex = PTHREAD_MUTEX_INITIALIZER;
Person* Person::m_pInstance = NULL;

Person* Person::instance()
{
    if (NULL == m_pInstance)
	{
		Lock lock();
		if (NULL == m_pInstance)
		{
		std::cout << "Create new instance" << std::endl;
        m_pInstance = new Person();
		}
	}
    return m_pInstance;
}

void Person::SetName(const std::string& name)
{
    m_sName = name;
}

std::string Person::Name() const
{
    return m_sName;
}

int main()
{
    Person* p = Person::instance();
	printf("address:%p\n", &p);
    p->SetName("Andy");
    std::cout << p->Name() << std::endl;
    Person* op = Person::instance();
	std::cout << &op << std::endl;

    return 0;
}
