#ifndef PCEMAP_H
#define PCEMAP_H

#include <assert.h>
#include "PCEVector.h"


template <class KeyType, class ValueType>
class PCEMap
{
public:

	PCEMap(){}

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
			newPair.m_key = i_key;
			m_keyValueVector.push_back(newPair);
			indexValue = m_keyValueVector.size() - 1;
		}

		return m_keyValueVector[indexValue].m_value;
	}

	const ValueType& at(const KeyType& i_key) const
	{
		int indexValue = containsKey(i_key);
		assert(indexValue != -1);
		return m_keyValueVector[indexValue]->m_value;
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

		for (int index = 0; valueFounded == -1 && index < m_keyValueVector.size(); ++index)
		{
			if (m_keyValueVector[index].m_key == i_key)
			{
				valueFounded = index;
			}
		}

		return valueFounded;
	}

private:

	struct KeyValuePair
	{
		KeyType m_key;
		ValueType m_value;
	};

	PCEVector<KeyValuePair> m_keyValueVector;
};


template <class KeyType, class ValueType>
class PCEMap<KeyType, ValueType *>
{
public:

	PCEMap(){}

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

	ValueType* operator[](const KeyType& i_key)
	{
		int indexValue = containsKey(i_key);
		if (indexValue == -1)
		{
			KeyValuePair newPair;
			newPair.m_key = i_key;
			newPair.m_value = nullptr;
			m_keyValueVector.push_back(newPair);
			indexValue = m_keyValueVector.size() - 1;
		}

		return m_keyValueVector[indexValue].m_value;
	}

	const ValueType* at(const KeyType& i_key) const
	{
		int indexValue = containsKey(i_key);
		assert(indexValue != -1);
		return m_keyValueVector[indexValue].m_value;
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

		for (int index = 0; valueFounded == -1 && index < m_keyValueVector.size(); ++index)
		{
			if (m_keyValueVector[index].m_key == i_key)
			{
				valueFounded = index;
			}
		}

		return valueFounded;
	}

private:

	struct KeyValuePair
	{
		KeyType m_key;
		ValueType* m_value;
	};

	PCEVector<KeyValuePair> m_keyValueVector;
};

#endif