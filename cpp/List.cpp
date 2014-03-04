#include "List.h"
#include <iostream>
#include <cstddef>

ListNode::ListNode()
        : m_pNext(NULL)
{
}

ListNode::ListNode(int v, ListNode *n)
        : m_iData(v)
        , m_pNext(n)
{
}

List::List()
        : m_pHead(NULL)
{
}

List::List(int v)
        : m_pHead(new ListNode(v))
{
}

List::~List()
{
    Clear();
}

void List::Clear()
{
    if (NULL == m_pHead)
        return;

    ListNode *p = m_pHead->m_pNext;
    while (NULL != p)
    {
        m_pHead->m_pNext = p->m_pNext;
        delete p;
        p = m_pHead->m_pNext;
    }

    delete m_pHead;
    m_pHead = NULL;
}

void List::Insert(int v)
{
    ListNode *pNewNode = new ListNode(v);
    if (Empty())
    {
        m_pHead = pNewNode;
        return;
    }

    ListNode *p = m_pHead;
	if (NULL != p && v < p->m_iData)
	{
		pNewNode->m_pNext = m_pHead;
		m_pHead = pNewNode;
		return;
	}

    while (NULL != p && v > p->m_iData)
    {
        if (NULL == p->m_pNext || NULL != p->m_pNext && v < p->m_pNext->m_iData)
        {
            pNewNode->m_pNext = p->m_pNext;
            p->m_pNext = pNewNode;
            break;
        }
		p = p->m_pNext;
    }
}

bool List::Empty()
{
	return m_pHead == NULL;
}

void List::Print()
{
	ListNode *p = m_pHead;
	while (NULL != p)
	{
		std::cout << p->m_iData << " "; 
		p = p->m_pNext;
	}
	std::cout << std::endl;
}

int main()
{
	List ltest;
	int array[] = {3, 9, 1, 23, 2};
	int len = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < len; ++i)
	{
		ltest.Insert(array[i]);
	}

	ltest.Print();

	return 0;
}
