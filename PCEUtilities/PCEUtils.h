#ifndef PCEUTILS_H
#define PCEUTILS_H

#include <cassert>
#include <memory>
#include "PCEPair.h"

template<class T1, class T2>
template<class U, class V>
PCEPair<T1,T2> make_pair(U&& i_first, V&& i_second)
{
	return PCEPair<T1,T2>(i_first,i_second);
}

template<class T>
class PCEBaseAllocator : public allocator
{
public:
	typedef T			value_type;
	typedef T*			pointer;
	typedef T&			reference;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;

public:
	PCEBaseAllocator()
	{
		_start = nullptr;
		_size = 0;

		_used_memory     = 0;
		_num_allocations = 0;
	}

	PCEBaseAllocator(const PCEBaseAllocator& i_other)
	{

	}
	
	template<class U>
	PCEBaseAllocator(const PCEBaseAllocator<U>& i_other)
	{

	}

	PCEBaseAllocator(size_t size, void* start)
	{
		_start          = start;
		_size           = size;

		_used_memory     = 0;
		_num_allocations = 0;
	}

	virtual ~PCEBaseAllocator()
	{
		assert(_num_allocations == 0 && _used_memory == 0);

		_start = nullptr;
		_size   = 0;
	}

	virtual void* allocate(size_t size, unsigned int alignment = 4) = 0;

	virtual void deallocate(void* p) = 0;

	void* getStart() const
	{
		return _start;
	}

	size_t getSize() const
	{
		return _size;
	}

	size_t getUsedMemory() const
	{
		return _used_memory;
	}

	size_t getNumAllocations() const
	{
		return _num_allocations;
	}

protected:
	void*         _start;
	size_t        _size;

	size_t        _used_memory;
	size_t        _num_allocations;
};

#endif //PCEUTILS_H