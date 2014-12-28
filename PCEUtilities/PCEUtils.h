#ifndef PCEUTILS_H
#define PCEUTILS_H

#include <cassert>
#include <memory>
#include "PCEPair.h"

template<class T1, class T2, class U, class V>
PCEPair<T1,T2> make_pair(U&& i_first, V&& i_second)
{
	return PCEPair<T1,T2>(i_first,i_second);
}

template<class T>
struct PCECompareLess
{
	bool operator() (const T& x, const T& y) const {return x<y;}
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef bool result_type;
};

template<class T>
class PCEAllocator
{
public:
	typedef T				value_type;
	typedef T*				pointer;
	typedef T&				reference;
	typedef const T*		const_pointer;
	typedef const T&		const_reference;
	typedef std::size_t		size_type;
	typedef std::ptrdiff_t	difference_type;

public:

	template <class Ty> 
	struct rebind {
		typedef PCEAllocator<Ty> other;
	};
		
public:

	PCEAllocator()
	{
	}

	PCEAllocator(const PCEAllocator& )
	{
	}
	
	template<class U>
	PCEAllocator(const PCEAllocator<U>& )
	{
	}

	PCEAllocator(size_t size, void* start)
	{
		_start          = start;
		_size           = size;

		_used_memory     = 0;
		_num_allocations = 0;
	}

	virtual ~PCEAllocator()
	{
	}

	pointer address(reference i_x) const
	{
		return &i_x;
	}
	
	const_pointer address(const_reference i_x) const
	{
		return &i_x;
	}

	pointer allocate(size_t i_size, PCEAllocator<void>::const_pointer = 0)
	{
		assert(i_size < max_size());
		return reinterpret_cast<pointer>( ::operator new(i_size * sizeof (value_type)) );
	}

	void deallocate(pointer p, size_type )
	{
		::operator delete(p);
	}

	size_type max_size() const
	{
		return ( size_type(-1) / sizeof (value_type) );
	}

	void construct(pointer i_p)
	{
		::new ((void*)i_p) value_type();
	}

	void construct(pointer i_p, const_reference i_val)
	{
		::new ((void*)i_p) value_type(i_val);
	}

	template<class U>
	void destroy(U* i_p)
	{
		i_p->~value_type();
	}
};

template<>
class PCEAllocator<void>
{
public:
	typedef void			value_type;
	typedef void*			pointer;
	typedef const void*		const_pointer;
};

#endif //PCEUTILS_H