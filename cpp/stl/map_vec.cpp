#include <iostream>
#include <string>
#include <vector>
#include <map>

int main()
{
	std::map<int, std::vector<std::string> > book;
	std::vector<std::string>& vecb = book[2];
	std::string name_1 = "Joy";
	std::string name_2 = "Andy";
	vecb.push_back(name_1);
	vecb.push_back(name_2);

	std::vector<std::string> vect = book[2];
	typedef std::vector<std::string>::iterator SIter;

	for (SIter iter = vect.begin(); iter != vect.end(); ++ iter)
		std::cout << *iter << std::endl;

	return 0;
}
