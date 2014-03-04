#include <iostream>
#include <string>

void replace_distinct(std::string & str, 
		const std::string & old_value,
		const std::string & new_value)
{
	std::string::size_type old_str_length = old_value.size();
	for (std::string::size_type pos = 0;
		   	pos != std::string::npos; 
			pos += old_str_length)
	{
		if (std::string::npos != (pos = str.find(old_value, pos)))
		{
			str.replace(pos, old_str_length, new_value);
		}
		else
			break;
	}
}

int main()
{
	std::string name("Andy Williams Andy Andy Jenny");
	std::cout << "Before replace: " << name << std::endl;

	std::string old_value("Andy");
	std::string new_value("Chris");
	replace_distinct(name, old_value, new_value);

	std::cout << "After replace: " << name << std::endl;

	return 0;
}
