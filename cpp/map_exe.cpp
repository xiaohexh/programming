#include <iostream>
#include <map>
#include <string>

class TextBlock
{
	typedef std::map<std::string, std::string> storage_t;
public:
	TextBlock(std::string key, std::string value);

	const std::string& operator[](const std::string& key) const;
	std::string& operator[](const std::string& key);

private:
	storage_t m_storage;
};

TextBlock::TextBlock(std::string key, std::string value)
{
	m_storage[key] = value;
}

const std::string& TextBlock::operator[](const std::string& key) const
{
	std::cout << "const overload operator []" << std::endl;
	return m_storage[key];
}

std::string& TextBlock::operator[](const std::string& key)
{
	std::cout << "non-const overload operator []" << std::endl;
	return m_storage[key];
}

int main()
{
	TextBlock obj("Andy", "Shanghai");
	std::cout << obj["Andy"] << std::endl;

	const TextBlock constObj("Chris", "Beijing");
	std::cout << constObj["Chris"] << std::endl;

	return 0;
}
