#ifndef PCEMAP_H
#define PCEMAP_H

#include <assert.h>
#include "PCEVector.h"


template <class KeyType, class ValueType>
class PCEMap
{
public:

	PCEMap(){}

	PCEMap( const PCEMap<KeyType,ValueType>& i_other )
		: m_keyValueVector( i_other.m_keyValueVector )
	{}

	~PCEMap(){}

	const bool empty() const
	{
		return m_keyValueVector.empty();
	}

	const int size() const
	{
		return m_keyValueVector.size();
	}

	const int max_size() const
	{
		return m_keyValueVector.capacity();
	}

	ValueType& operator[](const KeyType& i_key)
	{
		int indexValue = containsKey(i_key);
		if (indexValue == -1)
		{
			KeyValuePair newPair;
			newPair.first = i_key;
			m_keyValueVector.push_back(newPair);
			indexValue = m_keyValueVector.size() - 1;
		}

		return m_keyValueVector[indexValue].second;
	}

	const ValueType& at(const KeyType& i_key) const
	{
		int indexValue = containsKey(i_key);
		assert(indexValue != -1);
		return m_keyValueVector[indexValue]->second;
	}

	const int erase(const KeyType& i_key)
	{
		int indexValue = containsKey(i_key);
		int found = 0;
		while (indexValue != -1)
		{
			++found;
			m_keyValueVector.erase(indexValue);
			indexValue = containsKey(i_key);
		}

		return found;
	}

	const int erase(const KeyType *i_arrayKey, const int i_arrayLenght)
	{
		int found = 0;
		for (int arrayIndex = 0; arrayIndex < i_arrayLenght; ++arrayIndex)
		{
			int indexValue = containsKey(i_arrayKey[arrayIndex]);
			while (indexValue != -1)
			{
				++found;
				m_keyValueVector.erase(indexValue);
				indexValue = containsKey(i_arrayKey[arrayIndex]);
			}
		}

		return found;
	}

	void clear()
	{
		m_keyValueVector.clear();
	}

	const int containsKey(const KeyType& i_key)
	{
		int valueFounded = -1;

		for (uint32_t index = 0; valueFounded == -1 && index < m_keyValueVector.size(); ++index)
		{
			if (m_keyValueVector[index].first == i_key)
			{
				valueFounded = index;
			}
		}

		return valueFounded;
	}

	PCEMap<KeyType,ValueType>& operator=( const PCEMap<KeyType,ValueType>& i_other )
	{
		if ( this != &i_other )
		{
			m_keyValueVector = i_other.m_keyValueVector;
		}

		return *this;
	}

	bool operator==( const PCEMap<KeyType,ValueType>& i_other ) const
	{
		return m_keyValueVector == i_other.m_keyValueVector;
	}

	bool operator!=( const PCEMap<KeyType,ValueType>& i_other ) const
	{
		return !(*this == i_other);
	}

private:

	struct KeyValuePair
	{
		KeyType first;
		ValueType second;

		bool operator==( const KeyValuePair& i_other ) const
		{
			return first == i_other.first && second == i_other.second;
		}

		bool operator!=( const KeyValuePair& i_other ) const
		{
			return !( *this == i_other ); 
		}
	};

	PCEVector<KeyValuePair> m_keyValueVector;

public:

	class PCEIterator
	{
	public:

		PCEIterator( PCEVector<KeyValuePair>* i_pVector )
			: m_uiIndex(0)
			, m_pVector( i_pVector )
		{
		}

		PCEIterator( unsigned int i_uiIndex, PCEVector<KeyValuePair>* i_pVector )
			: m_uiIndex(i_uiIndex)
			, m_pVector( i_pVector )
		{
		}

		PCEIterator( const PCEIterator& i_PCEIt )
			: m_uiIndex( i_PCEIt.m_uiIndex )
			, m_pVector( i_PCEIt.m_pVector )
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

		virtual bool operator!=( const PCEIterator& i_other ) const
		{
			return !( *this == i_other );
		}

		virtual KeyValuePair& operator*()
		{
			return m_pVector->at( m_uiIndex );
		}

		virtual const KeyValuePair& operator*() const
		{
			return m_pVector->at( m_uiIndex );
		}

	protected:

		unsigned int m_uiIndex;
		PCEVector<KeyValuePair>* m_pVector;
	};

	PCEIterator begin()
	{
		return PCEIterator( &m_keyValueVector );
	}

	PCEIterator end()
	{
		return begin() + size();
	}
};

#endif