#ifndef SINGLETON_H__
#define SINGLETON_H__

#include <string>
#include <pthread.h>

class Lock
{
public:
	Lock()
	{
		pthread_mutex_lock(&m_mutex);
	}

	~Lock()
	{
		pthread_mutex_unlock(&m_mutex);
	}

private:
	static pthread_mutex_t m_mutex;
};

class Person
{
public:

	static Person* instance();

	void SetName(const std::string& name);

	std::string Name() const;

private:
	Person(){}
	Person(const Person&); // remove
	Person& operator = (const Person&); //remove

	std::string m_sName;
	static Person* m_pInstance;
};

#endif // SINGLETON_H__
