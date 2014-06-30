#include <iostream>
#include <string>
#include <queue>
#include <deque>
#include <stack>

int main()
{
	std::string note("note");
	std::string book("book");
	std::queue<std::string> strQ;
	strQ.push(note);
	strQ.push(book);
	if (!strQ.empty())
	{
		std::cout << "size of queue:" << strQ.size() << std::endl;
		std::string msg = strQ.front();
		strQ.pop();
		std::cout << msg << std::endl;
	}

	std::stack<std::string> strS;
	strS.push(note);
	strS.push(book);
	if (!strS.empty())
	{
		std::cout << "size of stack:" << strS.size() << std::endl;
		std::string msg = strS.top();
		strS.pop();
		std::cout << msg << std::endl;
	}

	std::deque<std::string> strDQ;
	strDQ.push_back(note);
	strDQ.push_front(book);
	if (!strDQ.empty())
	{
		std::cout << strDQ.front() << std::endl;
		std::cout << strDQ.back() << std::endl;

		for (std::deque<std::string>::iterator iter = strDQ.begin();
				iter != strDQ.end();
				++ iter)
			std::cout << *iter << " ";
		std::cout << std::endl;
	}

	return 0;
}
