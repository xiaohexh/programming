#ifndef SINGLE_LIST_H_
#define SINGLE_LIST_H_

#include <cstddef>

class List;

class ListNode
{
	friend class List;
public:
	ListNode();
	ListNode(int d, ListNode * n = NULL);

private:

	int			m_iData;
	ListNode	*m_pNext;
};

class List
{
public:
	List();
	List(int v);
	~List();

	void	Clear();
	void	Insert(int v);
	ListNode* Find(int v);
	bool	Delete(int v);
	bool	Empty();
	void	Print();

private:
	ListNode *m_pHead;
};

#endif // SINGLE_LIST_H_
