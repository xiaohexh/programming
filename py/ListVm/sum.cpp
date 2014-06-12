#include <iostream>
#include <stdlib.h>
#include <cstring>

#define ARRAY_NUMBER 20
#define STR_LEN		 20

#ifdef __cplusplus
extern "C"
{
#endif

struct StructTest
{
	int number;
	char* pChar;
	char str[STR_LEN];
	int iArray[ARRAY_NUMBER];
};

char* GetStructInfo(struct StructTest* pStruct)
{
	for (int i = 0; i < ARRAY_NUMBER; ++i)
		pStruct->iArray[i] = i;
	pStruct->pChar = "Hello Python";
	strcpy(pStruct->str, "Hello world!");
	pStruct->number = 100;

	return "Just OK";
}

//class __attribute__((visibility("default"))) Foo
class Foo
{
public:
	//void Print(const std::string& name)
	void Print(int name)
	{
		std::cout << "your name is:" << name << std::endl;
	}
};

//void Print(const std::string& name)
void Print(int name)
{
	std::cout << "input name:" << name << std::endl;
	Foo obj;
	obj.Print(name);
}

int foo(int a, int b)
{
	std::cout << "your input " << a <<  " and " << b << std::endl;
	return a + b;
}


#ifdef __cplusplus
}
#endif
