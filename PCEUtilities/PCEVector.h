#ifndef PCEVECTOR_H
#define PCEVECTOR_H

#include <assert.h>

template <class T>
class PCEVector
{
public:

	PCEVector(const unsigned int i_capacity = 0)
		: m_count(0)
		, m_capacity(i_capacity)
	{
		if (i_capacity == 0)
		{
			mp_elements = nullptr;
		}
		else
		{
			mp_elements = new T[m_capacity];
		}
	}

	PCEVector(const T* i_arrayElements, const unsigned int i_arraySize)
	{
		m_capacity = i_arraySize + 10;
		m_count = 0;
		mp_elements = new T[m_capacity];
		push_back(i_arrayElements,i_arraySize);
	}

	PCEVector(T* i_arrayElements, const unsigned int i_arraySize)
	{
		m_capacity = i_arraySize + 10;
		m_count = 0;
		mp_elements = new T[m_capacity];
		push_back(i_arrayElements,i_arraySize);
	}

	PCEVector(const PCEVector<T>& i_otherVector)
	{
		m_capacity = i_otherVector.m_capacity;
		m_count = i_otherVector.m_count;
		mp_elements = new T[m_capacity];
		for(unsigned int index = 0; index < m_count; ++index)
		{
			mp_elements[index] = i_otherVector[index];
		}
	}

	~PCEVector()
	{
		if (mp_elements != nullptr)
		{
			delete[] mp_elements;
		}
	}

	T& operator[](const unsigned int i_index) const		{return mp_elements[i_index];}

	T& at(const unsigned int i_index) const		{assert(i_index < m_count); return mp_elements[i_index];}

	void push_back(const T& io_newElement)
	{
		if (m_count == m_capacity)
		{
			addCapacity(10);
		}
		mp_elements[m_count] = io_newElement;
		++m_count;
	}

	void push_back(T& io_newElement)
	{
		if (m_count == m_capacity)
		{
			addCapacity(10);
		}
		mp_elements[m_count] = io_newElement;
		++m_count;
	}

	void push_back(const PCEVector<T>& i_otherVector)
	{
		if (m_count + i_otherVector.m_count > m_capacity)
		{
			addCapacity(m_count + i_otherVector.m_count - m_capacity + 10);
		}
		for(unsigned int index = 0; index < i_otherVector.m_count; ++index)
		{
			mp_elements[m_count] = i_otherVector.mp_elements[index];
			++m_count;
		}
	}

	void push_back(const T* i_arrayElements, const unsigned int i_numberOfNewElements)
	{
		if (m_count + i_numberOfNewElements > m_capacity)
		{
			addCapacity(m_count + i_numberOfNewElements - m_capacity + 10);
		}
		for(unsigned int index = 0; index < i_numberOfNewElements; ++index)
		{
			mp_elements[m_count] = i_arrayElements[index];
			++m_count;
		}
	}

	void push_back(T* i_arrayElements, const unsigned int i_numberOfNewElements)
	{
		if (m_count + i_numberOfNewElements > m_capacity)
		{
			addCapacity(m_count + i_numberOfNewElements - m_capacity + 10);
		}
		for(unsigned int index = 0; index < i_numberOfNewElements; ++index)
		{
			mp_elements[m_count] = i_arrayElements[index];
			++m_count;
		}
	}

	void shrink_to_fit()
	{
		if (m_count != m_capacity)
		{
			T* tpElements = mp_elements;

			mp_elements = new T[m_count];
			if (mp_elements != nullptr && tpElements != nullptr)
			{
				for(unsigned int index = 0; index < m_count; ++index)
				{
					mp_elements[index] = tpElements[index];
				}
				delete[] tpElements;
			}
			m_capacity = m_count;
		}
	}

	void resize(const unsigned int i_newCapacity)
	{
		if(i_newCapacity > m_capacity)
		{
			addCapacity(i_newCapacity - m_capacity);
		}
	}

	bool empty() const
	{
		return (m_count == 0);
	}

	void erase(const unsigned int i_atIndex)
	{
		if (i_atIndex < m_count && i_atIndex >= 0)
		{
			if (m_count > 1)
			{
				T* tpElements = mp_elements;

				mp_elements = new T[m_capacity];
				if (mp_elements != nullptr && tpElements != nullptr)
				{
					for(unsigned int index = 0; index < m_count; ++index)
					{
						if( index < i_atIndex)
						{
							mp_elements[index] = tpElements[index];
						}
						else if( index > i_atIndex)
						{
							mp_elements[index-1] = tpElements[index];
						}
					}
					delete[] tpElements;
				}
			} 
			else
			{
				mp_elements = nullptr;
			}
			--m_count;
		}
	}

	const unsigned int size() const		{return m_count;}

	const unsigned int capacity() const	{return m_capacity;}

	bool operator==(const PCEVector<T>& rvalue) const
	{
		bool isEqual = (m_count == rvalue.m_count && m_capacity == rvalue.m_capacity);

		for(unsigned int index = 0; isEqual && index < m_count; ++index)
		{
			isEqual = ( mp_elements[index] == rvalue.mp_elements[index] ); 
		}

		return isEqual;
	}

	bool operator!=(const PCEVector<T>& rvalue) const
	{
		return !(*this == rvalue);
	}

	const PCEVector<T>& operator=(const PCEVector<T>& rvalue)
	{
		if (this != &rvalue || *this != rvalue)
		{
			if (mp_elements != nullptr)
			{
				delete[] mp_elements;
			}
			m_capacity = rvalue.m_capacity;
			m_count = rvalue.m_count;
			if (m_capacity != 0)
			{
				mp_elements = new T[m_capacity];
				for(unsigned int index = 0; index < m_count; ++index)
				{
					mp_elements[index] = rvalue[index];
				}
			}
		}
		return *this;
	}

private:
	T *mp_elements;
	unsigned int m_capacity;
	unsigned int m_count;

	void addCapacity(unsigned int i_value)
	{
		if(i_value != 0)
		{
			m_capacity += i_value;
			T* tpElements = mp_elements;

			mp_elements = new T[m_capacity];
			if (mp_elements != nullptr && tpElements != nullptr)
			{
				for(unsigned int index = 0; index < m_count; ++index)
				{
					mp_elements[index] = tpElements[index];
				}
				delete[] tpElements;
			}
		}
	}

	
};

#endif