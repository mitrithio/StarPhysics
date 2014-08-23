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

	T& operator[](const unsigned int i_index) const		{return m_pElements[i_index];}

	T& at(const unsigned int i_index) const		{assert(i_index < m_uiCount); return m_pElements[i_index];}

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
		if(i_newCapacity > m_uiCapacity)
		{
			addCapacity(i_newCapacity - m_uiCapacity);
		}
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

	const unsigned int size() const		{return m_uiCount;}

	const unsigned int capacity() const	{return m_uiCapacity;}

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
		if (this != &rvalue || *this != rvalue)
		{
			if (m_pElements != nullptr)
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

};

/*!
	\brief A simple Point class which contains x, y and z coordinates.
*/
class PCEVector3{

public:
	float mX;	/*!< the local X coordinate */
	float mY;	/*!< the local Y coordinate */
	float mZ;	/*!< the local Z coordinate */

	/*!
		\brief Redefinition of == operator.
	*/
	inline bool operator== (const PCEVector3& rvalue) const
	{
		return mX == rvalue.mX && mY == rvalue.mY && mZ == rvalue.mZ;
	}
	
	/*!
		\brief Redefinition of != operator.
	*/
	inline bool operator!= (const PCEVector3& rvalue) const
	{
		return !(*this == rvalue);
	}
		
	/*!
		\brief Redefinition of = operator.
	*/
	PCEVector3& operator= (const PCEVector3& rvalue)
	{
		if (this != &rvalue)
		{
			mX = rvalue.mX; 
			mY = rvalue.mY; 
			mZ = rvalue.mZ;
		}
		return *this;
	}

	PCEVector3()
		: mX(0)
		, mY(0)
		, mZ(0)
	{}

	PCEVector3(float i_x, float i_y, float i_z)
		: mX(i_x)
		, mY(i_y)
		, mZ(i_z)
	{}

	PCEVector3(const PCEVector3& i_other)
		: mX(i_other.mX)
		, mY(i_other.mY)
		, mZ(i_other.mZ)
	{}
};


/*!
	\brief A simple Point class which contains x and y coordinates.
*/

class PCEVector2 {

public:
	float mX;	/*!< the local X coordinate */
	float mY;	/*!< the local Y coordinate */

	/*!
		\brief Redefinition of == operator.
	*/
	inline bool operator== (const PCEVector2& rvalue) const
	{
		return mX == rvalue.mX && mY == rvalue.mY;
	}

	PCEVector2& operator+=(const PCEVector2& i_other)
	{
		mX += i_other.mX;
		mY += i_other.mY;

		return *this;
	}

	const PCEVector2 operator+(const PCEVector2& i_other) const
	{
		PCEVector2 tmp(*this);
		tmp += i_other;
		return tmp;
	}
	
	/*!
		\brief Redefinition of != operator.
	*/
	inline bool operator!= (const PCEVector2& rvalue) const
	{
		return !(*this == rvalue);
	}
		
	/*!
		\brief Redefinition of = operator.
	*/
	PCEVector2& operator= (const PCEVector2& rvalue)
	{
		if (this != &rvalue)
		{
			mX = rvalue.mX; 
			mY = rvalue.mY;
		}
		return *this;
	}

	PCEVector2()
		: mX(0)
		, mY(0)
	{}
		
	PCEVector2(float i_x, float i_y, float i_z = 0)
		: mX(i_x)
		, mY(i_y)
	{}

	PCEVector2(const PCEVector2& i_other)
		: mX(i_other.mX)
		, mY(i_other.mY)
	{}
};

#endif