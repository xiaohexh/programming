#include <iostream>
#include <string>
#include <map>

struct Person
{
	std::string name;
	int			age;
};

typedef std::multimap<std::string, int>::iterator	mm_iter;
typedef std::map<int, Person>::iterator			per_iter;

std::map<int, Person> person;

void FillPerson()
{
	Person p[] = 
	{
		{"Andy", 28},
		{"Jenny", 27},
		{"Chris", 38},
		{"Lorry", 40},
	};

	int len = sizeof(p) / sizeof(p[0]);
	for (int i = 0; i < len; ++i)
	{
		person.insert(std::make_pair(i, p[i]));
	}

	Person f = {"Andy", 30};

	person.insert(std::make_pair(1, f));
}

Person* GetPerson(std::string n)
{
	for (per_iter iter = person.begin(); iter != person.end(); ++ iter)
	{
		if (iter->second.name == n)
			return &iter->second;
	}

	return NULL;
}

void map_uplow_bound()
{
	std::multimap<std::string, int> author;
	author.insert(std::make_pair("Jack", 1));
	author.insert(std::make_pair("Jack", 2));
	author.insert(std::make_pair("Andy", 1));
	author.insert(std::make_pair("Frank", 3));
	author.insert(std::make_pair("Chris", 1));
	author.insert(std::make_pair("Jack", 5));
	author.insert(std::make_pair("Jet", 5));
	author.insert(std::make_pair("Brian", 4));

	mm_iter iter = author.begin();
	for (; iter != author.end(); ++iter)
	{
		std::cout << iter->first << " " << iter->second << std::endl;
	}

	std::cout << "==============================" << std::endl;
	std::string search_item("Jack");
	mm_iter search_begin = author.lower_bound(search_item);
	mm_iter search_end = author.upper_bound(search_item);
	while (search_begin != search_end)
	{
		std::cout << search_begin->first << " " << search_begin->second << std::endl;  
		++ search_begin;
	}

	std::cout << "==============================" << std::endl;
	int count = 0;
	std::pair<mm_iter, mm_iter> pos = author.equal_range(search_item);
	while (pos.first != pos.second)
	{
		std::cout << pos.first->first << " " << pos.first->second << std::endl;
		++ pos.first;
		++ count; 
	}

	std::cout << "*** Count:" << count  << std::endl;
}

std::map<std::string, int> ps;


int main()
{
    map_uplow_bound();

	FillPerson();
	Person* per = GetPerson("Andy");
	if (NULL != per)
		std::cout << "Name:" << per->name << " " << "Age:" << per->age << std::endl;

	std::cout << "=====================" << std::endl;
	ps.insert(std::make_pair("Code", 1));
	ps.insert(std::make_pair("Source", 2));
	ps.insert(std::make_pair("Code", 3));
	typedef std::map<std::string, int>::iterator PI;
	PI it = ps.begin();
	std::cout << "Size:" << ps.size() << std::endl;
	for (; it != ps.end(); ++it)
	{
		std::cout << it->first << ":" << it->second << std::endl;
	}

	return 0;
}
