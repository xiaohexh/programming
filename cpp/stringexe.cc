#include <iostream>
#include <string>
#include <algorithm>

class Message
{
public:
	Message(const std::string& head, const std::string& body);

	const std::string& getMsg() const;

private:
	std::string _msg;
};

Message::Message(const std::string& head, const std::string& body)
{
	_msg.append(head);
	_msg.append(body);
}

const std::string& Message::getMsg() const
{
	return _msg;
}

int main()
{
	std::string head("abcdefghijklmnopqrstuvwxyz");
	std::string body("abcdefghijklmnopqrstuvwxyz");
	transform(head.begin(), head.end(), head.begin(), ::toupper);
	Message obj(head, body);
	std::cout << obj.getMsg() << std::endl;

	head.erase(0, -2);
	std::cout << head << std::endl;

	return 0;
}
