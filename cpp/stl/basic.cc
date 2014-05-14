#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int number = 0;
	std::vector<int> vec;
	std::cout << "input number(ctrl+d to quit):" << std::endl;
	while (std::cin >> number)
		vec.push_back(number);

	sort(vec.begin(), vec.end());

	for(std::vector<int>::iterator iter = vec.begin();
			iter != vec.end();
			++ iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	return 0;
}
