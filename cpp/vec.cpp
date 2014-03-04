#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vecNum;
	for (int i = 1; i < 9; ++i)
		vecNum.push_back(i);

	std::vector<int>::iterator iter;
	for (iter = vecNum.begin(); iter != vecNum.end();)
	{
		std::cout << *iter << ", ";
		iter = vecNum.erase(iter);
	}

	return 0;
}
