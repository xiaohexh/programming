#include <iostream>

int main()
{
	static unsigned flow_no = 1024;
	while (1)
	{
		int tmp = flow_no ++;
		std::cout << "flow number is:" << flow_no << std::endl;
		if (flow_no == 1024)	
			break;
	}

	std::cout << "=========== flow number is:" << flow_no << std::endl;

	return 0;
}
