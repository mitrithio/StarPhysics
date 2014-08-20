#ifndef PCELIST_H
#define PCELIST_H

template <class T>
class PCEList
{
public:
	PCEList()
	{
		m_pHead = nullptr;
		m_pBack = nullptr;
	}

	PCEList(const T& i_oFirstNode)
	{
		m_pHead = new Node();
		m_pHead->pNode = &i_oFirstNode;
		m_pHead->pNext = nullptr;
		m_pHead->pPrev = nullptr;
		m_pBack = m_pHead;
	}
	
	~PCEList()
	{
		EraseList();
	}

	void PushBack(const T& i_oLastNode)
	{
		if( m_pHead != nullptr)
		{
			Node * tmp = new Node();
			m_pBack->pNext = tmp;
			tmp->pPrev = m_pBack;
			tmp->pNode = i_oLastNode;
			tmp->pNext = nullptr;
			m_pBack = tmp;
		}
		else
		{
			m_pHead = new Node();
			m_pHead->pNode = &i_oFirstNode;
			m_pHead->pNext = nullptr;
			m_pHead->pPrev = nullptr;
			m_pBack = m_pHead;
		}
	}

	void PushFront(const T& i_oNewFirstNode)
	{
		if( m_pHead != nullptr )
		{
			Node * tmp = new Node();
			tmp->pNode = &i_oNewFirstNode;
			tmp->pNext = m_pHead;
			tmp->pPrev = nullptr;
			m_pBack = tmp;
			m_pHead = tmp;
		}
	}
	

private:
	struct Node
	{
		T * pNode;
		T * pNext;
		T * pPrev;
	};

	Node * m_pHead;
	Node * m_pBack;
	PCEVector<Node> oVectorList;

	PCEList(const PCEList<T>& i_list)
	{
		m_pHead = i_list.m_pHead;
		m_pBack = i_list.m_pBack;
	}

	PCEList& operator=(const PCEList<T>& i_other)
	{
		if( this != &i_other )
		{
			m_pHead = i_other.m_pHead;
			m_pBack = i_other.m_pBack;
		}
		return *this;
	}

	void EraseList()
	{
		for (Node * oNodeIterator = m_pBack->pPrev; oNodeIterator != m_pHead; oNodeIterator = oNodeIterator->pPrev)
		{
			delete oNodeIterator->pNext;
		}
		delete m_pHead;
	}
};

#endif