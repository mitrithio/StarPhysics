#ifndef PCEVECTOR_H
#define PCEVECTOR_H

#include <assert.h>

template <class T>
class PCEVector
{
public:

	PCEVector(const unsigned int i_capacity = 0)
		: m_uiCount(0)
		, m_uiCapacity(i_capacity)
	{
		if (i_capacity == 0)
		{
			m_pElements = nullptr;
		}
		else
		{
			m_pElements = new T[m_uiCapacity];
		}
	}

	PCEVector(const T* i_arrayElements, const unsigned int i_arraySize)
	{
		m_uiCapacity = i_arraySize + 10;
		m_uiCount = 0;
		m_pElements = new T[m_uiCapacity];
		push_back(i_arrayElements,i_arraySize);
	}

	PCEVector(T* i_arrayElements, const unsigned int i_arraySize)
	{
		m_uiCapacity = i_arraySize + 10;
		m_uiCount = 0;
		m_pElements = new T[m_uiCapacity];
		push_back(i_arrayElements,i_arraySize);
	}

	PCEVector(const PCEVector<T>& i_otherVector)
	{
		m_uiCapacity = i_otherVector.m_uiCapacity;
		m_uiCount = i_otherVector.m_uiCount;
		m_pElements = new T[m_uiCapacity];
		for(unsigned int index = 0; index < m_uiCount; ++index)
		{
			m_pElements[index] = i_otherVector[index];
		}
	}

	~PCEVector()
	{
		if (m_pElements != nullptr)
		{
			delete[] m_pElements;
		}
	}

	T& operator[](const unsigned int i_index) const		
	{
		return m_pElements[i_index];
	}

	T& at(const unsigned int i_index) const
	{
		assert(i_index < m_uiCount); 
		return m_pElements[i_index];
	}

	void push_back(const T& io_newElement)
	{
		if (m_uiCount == m_uiCapacity)
		{
			addCapacity(10);
		}
		m_pElements[m_uiCount] = io_newElement;
		++m_uiCount;
	}

	void push_back(T& io_newElement)
	{
		if (m_uiCount == m_uiCapacity)
		{
			addCapacity(10);
		}
		m_pElements[m_uiCount] = io_newElement;
		++m_uiCount;
	}

	void push_back(const PCEVector<T>& i_otherVector)
	{
		if (m_uiCount + i_otherVector.m_uiCount > m_uiCapacity)
		{
			addCapacity(m_uiCount + i_otherVector.m_uiCount - m_uiCapacity + 10);
		}
		for(unsigned int index = 0; index < i_otherVector.m_uiCount; ++index)
		{
			m_pElements[m_uiCount] = i_otherVector.m_pElements[index];
			++m_uiCount;
		}
	}

	void push_back(const T* i_arrayElements, const unsigned int i_numberOfNewElements)
	{
		if (m_uiCount + i_numberOfNewElements > m_uiCapacity)
		{
			addCapacity(m_uiCount + i_numberOfNewElements - m_uiCapacity + 10);
		}
		for(unsigned int index = 0; index < i_numberOfNewElements; ++index)
		{
			m_pElements[m_uiCount] = i_arrayElements[index];
			++m_uiCount;
		}
	}

	void push_back(T* i_arrayElements, const unsigned int i_numberOfNewElements)
	{
		if (m_uiCount + i_numberOfNewElements > m_uiCapacity)
		{
			addCapacity(m_uiCount + i_numberOfNewElements - m_uiCapacity + 10);
		}
		for(unsigned int index = 0; index < i_numberOfNewElements; ++index)
		{
			m_pElements[m_uiCount] = i_arrayElements[index];
			++m_uiCount;
		}
	}

	void shrink_to_fit()
	{
		if (m_uiCount != m_uiCapacity)
		{
			T* tpElements = m_pElements;

			m_pElements = new T[m_uiCount];
			if (m_pElements != nullptr && tpElements != nullptr)
			{
				for(unsigned int index = 0; index < m_uiCount; ++index)
				{
					m_pElements[index] = tpElements[index];
				}
				delete[] tpElements;
			}
			m_uiCapacity = m_uiCount;
		}
	}

	void resize(const unsigned int i_newCapacity)
	{
		clear();
		addCapacity( i_newCapacity );
	}

	bool empty() const
	{
		return (m_uiCount == 0);
	}

	void erase(const unsigned int i_atIndex)
	{
		assert(i_atIndex < m_uiCount && i_atIndex >= 0);
		if (m_uiCount > 1)
		{
			T* tpElements = m_pElements;

			m_pElements = new T[m_uiCapacity];
			if (m_pElements != nullptr && tpElements != nullptr)
			{
				for(unsigned int index = 0; index < m_uiCount; ++index)
				{
					if( index < i_atIndex)
					{
						m_pElements[index] = tpElements[index];
					}
					else if( index > i_atIndex)
					{
						m_pElements[index-1] = tpElements[index];
					}
				}
				delete[] tpElements;
			}
		} 
		else
		{
			m_pElements = nullptr;
		}
		--m_uiCount;
	}

	const unsigned int size() const
	{
		return m_uiCount;
	}

	const unsigned int capacity() const
	{
		return m_uiCapacity;
	}

	bool operator==(const PCEVector<T>& rvalue) const
	{
		bool isEqual = (m_uiCount == rvalue.m_uiCount && m_uiCapacity == rvalue.m_uiCapacity);

		for(unsigned int index = 0; isEqual && index < m_uiCount; ++index)
		{
			isEqual = ( m_pElements[index] == rvalue.m_pElements[index] ); 
		}

		return isEqual;
	}

	bool operator!=(const PCEVector<T>& rvalue) const
	{
		return !(*this == rvalue);
	}

	const PCEVector<T>& operator=(const PCEVector<T>& rvalue)
	{
		if ( this != &rvalue )
		{
			if ( m_pElements != nullptr )
			{
				delete[] m_pElements;
			}
			m_uiCapacity = rvalue.m_uiCapacity;
			m_uiCount = rvalue.m_uiCount;
			if (m_uiCapacity != 0)
			{
				m_pElements = new T[m_uiCapacity];
				for(unsigned int index = 0; index < m_uiCount; ++index)
				{
					m_pElements[index] = rvalue[index];
				}
			}
		}
		return *this;
	}

	void clear()
	{
		T* tmpElements = m_pElements;
		m_pElements = nullptr;
		delete [] tmpElements;
		m_uiCount = 0;
		m_uiCapacity = 0;
	}

private:
	T* m_pElements;
	unsigned int m_uiCapacity;
	unsigned int m_uiCount;

	void addCapacity(unsigned int i_value)
	{
		if(i_value != 0)
		{
			m_uiCapacity += i_value;
			T* tpElements = m_pElements;

			m_pElements = new T[m_uiCapacity];
			if (m_pElements != nullptr && tpElements != nullptr)
			{
				for(unsigned int index = 0; index < m_uiCount; ++index)
				{
					m_pElements[index] = tpElements[index];
				}
				delete[] tpElements;
			}
		}
	}

public:

	class PCEIterator
	{
	public:

		PCEIterator()
			: m_uiIndex(0)
		{
		}

		PCEIterator( unsigned int i_uiIndex )
			: m_uiIndex(i_uiIndex)
		{
		}

		PCEIterator( const PCEIterator& i_PCEIt )
			: m_uiIndex( i_PCEIt.m_uiIndex )
		{
		}

		virtual ~PCEIterator(){}

		virtual PCEIterator& operator++()
		{
			++m_uiIndex;
			return *this;
		}

		virtual PCEIterator operator++( int )
		{
			PCEIterator tempIt( *this );
			++tempIt;
			return tempIt;
		}

		virtual PCEIterator& operator--()
		{
			--m_uiIndex;
			return *this;
		}

		virtual PCEIterator operator--( int )
		{
			PCEIterator tempIt( *this );
			--tempIt;
			return tempIt;
		}

		virtual PCEIterator& operator+=( const PCEIterator& i_other )
		{
			m_uiIndex += i_other.m_uiIndex;
			return *this;
		}

		virtual PCEIterator operator+( const PCEIterator& i_other )
		{
			m_uiIndex += i_other.m_uiIndex;
			return *this;
		}

		virtual PCEIterator operator+( unsigned int i_uiAddedIndex )
		{
			m_uiIndex += i_uiAddedIndex;
			return *this;
		}

		virtual bool operator==( const PCEIterator& i_other ) const
		{
			return ( m_uiIndex == i_other.m_uiIndex );
		}

		virtual bool operator!=( const PCEIterator& i_other )
		{
			return !( *this == i_other );
		}

		virtual T& operator*()
		{
			return m_pVector->at( m_uiIndex );
		}

		virtual const T& operator*() const
		{
			return m_pVector->at( m_uiIndex );
		}

	protected:

		unsigned int m_uiIndex;
		PCEVector<T>* m_pVector;
	};

	PCEIterator begin()
	{
		return PCEIterator();
	}

	PCEIterator end()
	{
		return PCEIterator( size() );
	}

	const PCEIterator& find( const T& i_value )
	{
		for ( PCEIterator it = begin(); it != end(); ++it )
		{
			if ( (*it) == i_value )
			{
				return it;
			}
		}

		return end();
	}

};

#endif