#ifndef PCEVECTOR_H
#define PCEVECTOR_H

#include <assert.h>

template <class T>
class PCEVector
{
public:

	PCEVector(const size_t i_capacity = 0)
		: mCount(0)
		, mCapacity(i_capacity)
	{
		if (i_capacity == 0)
		{
			mpElements = nullptr;
		}
		else
		{
			mpElements = new T[mCapacity];
		}
	}

	PCEVector(const T& i_arrayElements, const size_t i_arraySize)
	{
		mCapacity = i_arraySize;
		mCount = i_arraySize;
		mpElements = new T[mCapacity];

	}

	PCEVector(const PCEVector<T>& i_otherVector)
	{
		mCapacity = i_otherVector.mCapacity;
		mCount = i_otherVector.mCount;
		mpElements = new T[mCapacity];
		for (size_t i = 0; i < mCount; ++i)
		{
			mpElements[i] = i_otherVector[i];
		}
	}

	const T& operator[](const size_t index) const		{return mpElements[index];}

	const T& at(const size_t index) const		{assert(index < mCount); return mpElements[index];}

	void push_back(const T& io_newElement)
	{
		if (mCount == mCapacity)
		{
			addCapacity(10);
		}
		mpElements[mCount] = io_newElement;
		++mCount;
	}

	void shrink_to_fit()
	{
		if (mCount != mCapacity)
		{
			T* tpElements = mpElements;

			mpElements = new T[mCount];
			if (mpElements != nullptr && tpElements != nullptr)
			{
				for (size_t i = 0; i < mCount; ++i)
				{
					mpElements[i] = tpElements[i];
				}
				delete[] tpElements;
			}
			mCapacity = mCount;
		}
	}

	void reserve(const size_t i_newCapacity)
	{
		if(i_newCapacity > mCapacity)
		{
			addCapacity(i_newCapacity - mCapacity);
		}
	}

	bool empty() const
	{
		return (mCount == 0);
	}

	void erase(const size_t i_atIndex)
	{
		if (at(i_atIndex))
		{
			T* tpElements = mpElements;

			mpElements = new T[mCapacity];
			if (mpElements != nullptr && tpElements != nullptr)
			{
				for (size_t i = 0; i < mCount; ++i)
				{
					if( i < i_atIndex)
					{
						mpElements[i] = tpElements[i];
					}
					else if( i > i_atIndex)
					{
						mpElements[i-1] = tpElements[i];
					}
				}
				delete[] tpElements;
			}
			mCapacity = mCount;
		}
	}

	~PCEVector()
	{
		if (mpElements != nullptr)
		{
			delete[] mpElements;
		}
	}

	const size_t size() const		{return mCount;}
	const size_t capacity() const	{return mCapacity;}

	bool operator==(const PCEVector<T>& rvalue) const
	{
		bool isEqual = true;
		if (mCount != rvalue.mCount || mCapacity != rvalue.mCapacity)
		{
			isEqual = false;
		}
		for (size_t i = 0; isEqual && i < mCount; ++i)
		{
			isEqual = ( mpElements[i] == rvalue.mpElements[i] ); 
		}
		return isEqual;
	}

	bool operator!=(const PCEVector<T>& rvalue) const
	{
		return !(*this == rvalue);
	}

	const PCEVector<T>& operator=(const PCEVector<T>& i_otherVector)
	{
		if (this != &i_otherVector)
		{
			if (mpElements != nullptr)
			{
				delete[] mpElements;
			}
			mCapacity = i_otherVector.mCapacity;
			mCount = i_otherVector.mCount;
			mpElements = new T[mCapacity];
			for (size_t i = 0; i < mCount; ++i)
			{
				mpElements[i] = i_otherVector[i];
			}
		}
		return *this;
	}

private:
	T *mpElements;
	size_t mCapacity;
	size_t mCount;

	void addCapacity(size_t i_value)
	{
		if(i_value != 0)
		{
			mCapacity += i_value;
			T* tpElements = mpElements;

			mpElements = new T[mCapacity];
			if (mpElements != nullptr && tpElements != nullptr)
			{
				for (size_t i = 0; i < mCount; ++i)
				{
					mpElements[i] = tpElements[i];
				}
				delete[] tpElements;
			}
		}
	}
};

#endif