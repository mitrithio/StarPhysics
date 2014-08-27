#ifndef PCELIST_H
#define PCELIST_H

/************************************************************************/
/*
	This is a List implemented on a PCEVector. To use this class properly,
	the T type must have a working copy constructor.
*/
/************************************************************************/
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
		m_pHead->m_pData = &i_oFirstNode;
		m_pHead->m_pNext = nullptr;
		m_pHead->m_pPrev = nullptr;
		m_pHead->m_uiVectorIndex = 0;
		m_pBack = m_pHead;
		m_oVectorList.push_back(i_oFirstNode);
	}
	
	~PCEList()
	{
		DeleteList();
	}

	void push_back(const T& i_oLastNode)
	{
		if( m_pHead != nullptr)
		{
			Node * tmp = new Node();
			m_pBack->m_pNext = tmp;
			tmp->m_pPrev = m_pBack;
			tmp->m_pData = &i_oLastNode;
			tmp->m_pNext = nullptr;
			tmp->m_uiVectorIndex = m_oVectorList.size();
			m_pBack = tmp;
		}
		else
		{
			m_pHead = new Node();
			m_pHead->m_pData = &i_oLastNode;
			m_pHead->m_pNext = nullptr;
			m_pHead->m_pPrev = nullptr;
			m_pHead->m_uiVectorIndex = 0;
			m_pBack = m_pHead;
		}
		m_oVectorList.push_back(i_oLastNode);
	}

	void push_front(const T& i_oNewFirstNode)
	{
		if( m_pHead != nullptr )
		{
			Node * tmp = new Node();
			tmp->m_pData = &i_oNewFirstNode;
			tmp->m_pNext = m_pHead;
			tmp->m_pPrev = nullptr;
			tmp->m_uiVectorIndex = m_oVectorList.size();
			m_pHead = tmp;
		}
		else
		{
			m_pHead = new Node();
			m_pHead->m_pData = &i_oNewFirstNode;
			m_pHead->m_pNext = nullptr;
			m_pHead->m_pPrev = nullptr;
			m_pHead->m_uiVectorIndex = 0;
			m_pBack = m_pHead; 
		}
		m_oVectorList.push_back(i_oLastNode);
	}

	bool DeleteNode( const T& i_oData )
	{
		unsigned int uiIndex = 0;
		for (Node* pNodeIterator = m_pHead; pNodeIterator != nullptr; pNodeIterator = pNodeIterator->m_pNext)
		{
			if (pNodeIterator->m_pData == &i_oData)
			{
				Node* tmpNode = pNodeIterator;
				if (pNodeIterator == m_pHead)
				{
					m_pHead = tmpNode->m_pNext;
					m_pHead->m_pPrev = nullptr;
				}
				else
				{				
					Node* jumpingNode = pNodeIterator->m_pPrev;
					if (pNodeIterator == m_pBack)
					{
						jumpingNode->m_pNext = nullptr;
						m_pBack = jumpingNode;
					}
					else
					{
						jumpingNode->m_pNext = tmpNode->m_pNext;
						jumpingNode = tmpNode->m_pNext;
						jumpingNode->m_pPrev = tmpNode->m_pPrev;
						UpdateIndexFromTo( jumpingNode->m_uiVectorIndex, m_oVectorList.size() - 1 );
					}
				}
				m_oVectorList.erase(uiIndex);
				delete tmpNode;
				return true;
			}
			++uiIndex;
		}

		return false;
	}

	bool DeleteNode( unsigned int i_uiIndex )
	{
		return DeleteNode(m_oVectorList.at(i_uiIndex).pData);
	}

	unsigned int size() const
	{
		return m_oVectorList.size();
	}

	void shrink_to_fit()
	{
		m_oVectorList.shrink_to_fit();
	}

	void clear()
	{
		Node* tmpHead = m_pHead;
		m_pHead = nullptr;
		Node* tmpBack = m_pBack;
		m_pBack = nullptr;
		DeleteFromTo( tmpHead, tmpBack );
	}
	

private:
	struct Node
	{
		unsigned int m_uiVectorIndex;
		const T * m_pData;
		Node * m_pNext;
		Node * m_pPrev;
	};

	Node * m_pHead;
	Node * m_pBack;
	PCEVector<T*> m_oVectorList;

	PCEList( const PCEList<T>& i_oList )
		: m_pBack( nullptr )
		, m_pHead( nullptr )
	{
		m_oVectorList.resize( i_oList.size() );
 		if ( m_oVectorList.capacity() > 0 )
 		{
			Node* oCopyListIterator = i_oList.m_pHead;
		
			Node* oNewNodeIterator = new Node();
			oNewNodeIterator->m_uiVectorIndex = 0;
			oNewNodeIterator->m_pData = new T( oCopyListIterator->m_pData );
			m_pHead = oNewNodeIterator;
			m_oVectorList.push_back(oNewNodeIterator);
			for ( unsigned int uiIndex = 1; uiIndex < i_oList.size(); ++uiIndex )
 			{
				oCopyListIterator = oCopyListIterator->m_pNext;

				oNewNodeIterator->m_pNext = new Node();
				oNewNodeIterator->m_pNext->m_pPrev = oNewNodeIterator;
				oNewNodeIterator = oNewNodeIterator->m_pNext;
				oNewNodeIterator->m_uiVectorIndex = uiIndex;
				oNewNodeIterator->m_pData = new T( oCopyListIterator->m_pData );
				m_oVectorList.push_back( oNewNodeIterator );
 			}
			m_pBack = oNewNodeIterator;
		}
	}

	PCEList& operator=(const PCEList<T>& i_other)
	{
		if( this != &i_other )
		{
			m_oVectorList.clear();
			m_oVectorList.resize( i_oList.size() );
			if ( m_oVectorList.capacity() > 0 )
			{
				Node* oCopyListIterator = i_oList.m_pHead;

				Node* oNewNodeIterator = new Node();
				oNewNodeIterator->m_uiVectorIndex = 0;
				oNewNodeIterator->m_pData = new T( oCopyListIterator->m_pData );
				m_pHead = oNewNodeIterator;
				m_oVectorList.push_back(oNewNodeIterator);
				for ( unsigned int uiIndex = 1; uiIndex < i_oList.size(); ++uiIndex )
				{
					oCopyListIterator = oCopyListIterator->m_pNext;

					oNewNodeIterator->m_pNext = new Node();
					oNewNodeIterator->m_pNext->m_pPrev = oNewNodeIterator;
					oNewNodeIterator = oNewNodeIterator->m_pNext;
					oNewNodeIterator->m_uiVectorIndex = uiIndex;
					oNewNodeIterator->m_pData = new T( oCopyListIterator->m_pData );
					m_oVectorList.push_back( oNewNodeIterator );
				}
				m_pBack = oNewNodeIterator;
			}
		}
		return *this;
	}

	void DeleteList()
	{
		if (m_pHead != nullptr)
		{
 			DeleteFromTo(m_pHead, m_pBack);
		}
	}

	bool DeleteFromTo( Node* i_pFrom, Node* i_pTo )
	{
		if (i_pTo == nullptr || i_pFrom == nullptr)
		{
			return false;
		}

		unsigned int uiInitialSize = m_oVectorList.size();
		unsigned int uiIndexErased = 0;
		if ( i_pFrom == i_pTo )
		{
			Node* tmpNode = i_pFrom;
			i_pFrom = nullptr;
			i_pTo = nullptr;
			delete tmp;
			++uiIndexErased;
		}
		Node* pNodeIterator = i_pFrom;
		while ( pNodeIterator != i_pTo )
		{
			Node* tmpNode = pNodeIterator;
			pNodeIterator = pNodeIterator->m_pNext;
			m_oVectorList.erase(  )
			delete tmpNode;
			++uiIndexErased;
		}
		
		delete i_pTo;
		return true;
	}

	void UpdateIndexFromTo( unsigned int i_uiVectorIndex, unsigned int i_uiIndexTo )
	{
		for (unsigned int uiIndex = i_uiVectorIndex+1; uiIndex <= i_uiIndexTo; ++uiIndex)
		{
			--(m_oVectorList.at(uiIndex).uiVectorIndex);
		}
	}


};

#endif