#ifndef PCEMAP_H
#define PCEMAP_H

#include <assert.h>
#include "PCEPair.h"


template <class Key, class T>
class PCEMap
{
public:

	typedef Key								key_type;
	typedef T								mapped_type;
	typedef PCEPair<key_type,mapped_type>	value_type;
	typedef value_type&						reference;
	typedef const reference					const_reference;
	typedef value_type*						iterator;
	typedef const iterator					const_iterator;

	explicit PCEMap()
		: size_(0)
		, capacity_(0)
		, values_(nullptr)
	{}

	PCEMap(const PCEMap& i_other)
		: size_(i_other.size_)
		, capacity_(i_other.capacity_)
	{
		values_ = new value_type[capacity_];
		unsigned int uiCount = 0;
		for (const_iterator it = i_other.begin(); it != i_other.end(); ++it, ++uiCount)
		{
			&values_[uiCount] = new(&values_[uiCount]) value_type(*it);
		}
	}

	~PCEMap()
	{
		if (!empty())
		{
			delete [] values_;
		}
	}

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

	mapped_type& operator[](const key_type& i_key)
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

	mapped_type& at(const key_type& i_key)
	{
		if (find(i_key) != end())
		{
			return (*find(i_key)).second;
		}
	}

	const mapped_type& at(const key_type& i_key) const
	{
		int indexValue = containsKey(i_key);
		assert(indexValue != -1);
		return m_keyValueVector[indexValue]->second;
	}

	const int erase(const key_type& i_key)
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

	const int erase(const key_type *i_arrayKey, const int i_arrayLenght)
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

	const int containsKey(const key_type& i_key)
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

	PCEMap<key_type,mapped_type>& operator=( const PCEMap<key_type,mapped_type>& i_other )
	{
		if ( this != &i_other )
		{
			m_keyValueVector = i_other.m_keyValueVector;
		}

		return *this;
	}

	bool operator==( const PCEMap<key_type,mapped_type>& i_other ) const
	{
		return m_keyValueVector == i_other.m_keyValueVector;
	}

	bool operator!=( const PCEMap<key_type,mapped_type>& i_other ) const
	{
		return !(*this == i_other);
	}

private:

	size_t			size_;
	size_t			capacity_;
	value_type *	values_;

public:

	iterator begin()
	{
		return iterator( &m_keyValueVector );
	}

	iterator end()
	{
		return begin() + size();
	}

	iterator find( const key_type& i_oKey )
	{
		bool bFound = false;
		iterator it = begin();
		for ( ; !bFound && it != end(); ++it )
		{
			bFound = ( (*it)->first == i_oKey )
		}

		if ( bFound )
		{
			return it - 1;
		}

		return it;
	}
};

#endif