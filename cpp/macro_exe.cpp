#include <iostream>

#define DEFAULT_MEMBER(cls_name) \
	cls_name();                  \
	virtual ~cls_name();         \
	void Print();                \

#define SAFE_DELETE(ptr)           \
	if (ptr)                     \
	{                            \
		delete ptr;              \
		ptr = NULL;              \
	}                            \

typedef enum
{
	LL_NET,
	LL_DEBUG,
	LL_INFO,
	LL_WARN,
	LL_ERROR
}LOG_LEVEL;

typedef struct
{
	LOG_LEVEL logLevel;
	const char* pName;
}LevelName;

static LevelName LEVEL_NAME[] =
{
	{LL_NET, "net"},
	{LL_DEBUG, "debug"},
	{LL_WARN, "warnning"},
};

class Book
{
public:

	DEFAULT_MEMBER(Book)
};

Book::Book()
{
}

Book::~Book()
{
}

void Book::Print()
{
	std::cout << "Hello" << std::endl;
	std::cout << LEVEL_NAME[2].pName << std::endl;
}

int main()
{
	Book book;
	book.Print();

	char* p = new char('a');
	std::cout << *p << std::endl;
	SAFE_DELETE(p);

	return 0;
}
