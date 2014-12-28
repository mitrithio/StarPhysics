#ifndef PCEVECTOR_H
#define PCEVECTOR_H

#include <assert.h>
#include "PCEUtils.h"

template<class T, class Alloc = PCEAllocator<T> >
class PCEVector
{
public:

	typedef T					value_type;
	typedef Alloc				allocator_type;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;
	typedef value_type*			iterator;
	typedef const value_type*	const_iterator;
	typedef std::size_t			size_type;

	typedef value_type*			input_iterator;
public:

	explicit PCEVector(const allocator_type& i_alloc = allocator_type())
		: size_(0)
		, capacity_(0)
		, data_(nullptr)
		, allocator_(i_alloc)
	{
	}

	explicit PCEVector(size_type i_n)
		: size_(i_n)
		, capacity_(i_n)
		, allocator_(allocator_)
	{
		data_ = allocator_.allocate(capacity_);
		for (unsigned int index = 0; index != size_; ++index)
		{
			allocator_.construct(&data_[index]);
		}
	}

	explicit PCEVector(size_type i_n, const value_type& i_val, const allocator_type& i_alloc = allocator_type())
		: size_(i_n)
		, capacity_(i_n)
		, allocator_(i_alloc)
	{
		data_ = allocator_.allocate(capacity_);
		for (unsigned int index = 0; index != size_; ++index)
		{
			i_alloc.construct(&data_[index],i_val);
		}
	}

	PCEVector(const PCEVector& i_other)
		: size_(i_other.size_)
		, capacity_(i_other.capacity_)
		, allocator_(allocator_)
	{
		data_ = allocator_.allocate(capacity_);
		size_type index = 0;
		for (const_iterator it = i_other.begin(); it != i_other.end(); ++it, ++index)
		{
			allocator_.construct(&data_[index],*it);
		}
	}

	PCEVector(const PCEVector& i_other, const allocator_type& i_alloc)
		: size_(i_other.size_)
		, capacity_(i_other.capacity_)
		, allocator_(i_alloc)
	{
		data_ = allocator_.allocate(capacity_);
		size_type index = 0;
		for (const_iterator it = i_other.begin(); it != i_other.end(); ++it, ++index)
		{
			allocator_.construct(&data_[index],*it);
		}
	}

	PCEVector(input_iterator i_first, input_iterator i_last, const allocator_type& i_alloc = allocator_type())
		: allocator_(i_alloc)
	{
		// construct [i_first,i_last)
		size_ = capacity_ = i_last - i_first;
		data_ = allocator_.allocate(capacity_);
		unsigned int index = 0;
		for ( input_iterator it = i_first; it != i_last ; ++it, ++index )
		{
			allocator_.construct(&data_[index],(*it));
		}
	}

	~PCEVector()
	{
		DestroyAndDeallocateRange(begin(),end());
	}

	void assign(input_iterator i_first, input_iterator i_last)
	{
		// assign [i_first, i_last)
		DestroyRange(begin(), end());

		insert(begin(),i_first,i_last);
	}

	void assign(size_type i_n, const value_type& i_val)
	{
		DestroyRange(begin(),end());

		insert(begin(),i_n,i_val);
	}

	reference at(size_type i_n)
	{
		assert(i_n<size_);
		return operator[](i_n);
	}

	const_reference at(size_type i_n) const
	{
		assert(i_n<size_);
		return operator[](i_n);
	}

	reference back()
	{
		return data_[size_ - 1];
	}

	const_reference back() const
	{
		return data_[size_ - 1];
	}

	iterator begin()
	{
		return data_;
	}

	const_iterator begin() const
	{
		return data_;
	}

	size_type capacity() const
	{
		return capacity_;
	}

	const_iterator cbegin() const
	{
		return data_;
	}

	const_iterator cend() const
	{
		return data_[size_];
	}

	void clear()
	{
		DestroyAndDeallocateRange(begin(),end());
	}

	value_type* data()
	{
		return data_;
	}

	const value_type* data() const
	{
		return data_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	iterator end()
	{
		return &data_[size_];
	}

	const_iterator end() const
	{
		return &data_[size_];
	}

	iterator erase( const_iterator i_pos )
	{
		if ( i_pos != end() )
		{
			return erase(i_pos,i_pos+1);
		}

		return end();
	}

	iterator erase( const_iterator i_first, const_iterator i_last )
	{
		size_type firstPos = i_first - begin();
		size_type lastPos = firstPos + (i_last - i_first);
		Move(&data_[firstPos], &data_[lastPos], end());

		return &data_[firstPos];
	}

	reference front()
	{
		return data_[0];
	}

	const_reference front() const
	{
		return data_[0];
	}

	allocator_type get_allocator() const
	{
		return allocator_;
	}

	iterator insert( const_iterator i_pos, const value_type& i_val )
	{
		return insert(i_pos,1,i_val);
	}

	iterator insert( const_iterator i_pos, size_type i_n, const value_type& i_val )
	{
		size_type index = i_pos - begin();
		iterator pos = &data_[index];
		if ( size_ + i_n > capacity_)
		{
			reserve((size_+i_n)*2);
		}

		if ( index != size_ )
		{
			Move(pos + i_n, pos, end());
		}

		for ( ; index < (pos - begin()) + i_n; ++index )
		{
			allocator_.construct(&data_[index],i_val);
		}

		size_ += i_n;

		return pos;
	}

	template<class input_iterator>
	iterator insert( const_iterator i_pos, input_iterator i_first, input_iterator i_last )
	{
		size_type index = i_pos - begin();
		iterator pos = &data_[index];

		size_type i_n = i_last - i_first;
		if ( size_ + i_n > capacity_)
		{
			reserve((size_+i_n)*2);
		}

		if ( index != size_ )
		{
			Move(pos + i_n, pos, end());
		}

		for ( input_iterator it = i_first ; it != i_last; ++it, ++index )
		{
			allocator_.construct(&data_[index],*it);
		}

		size_ += i_n;

		return pos;
	}

	size_type max_size() const
	{
		return allocator_.max_size();
	}

	PCEVector& operator=( const PCEVector& i_other )
	{
		if (this != &i_other)
		{
			assign(i_other.begin(), i_other.end());
		}

		return *this;
	}

	reference operator[]( size_type i_n )
	{
		return data_[i_n];
	}

	const_reference operator[]( size_type i_n ) const
	{
		return data_[i_n];
	}

	void pop_back()
	{
		erase(begin() + size_ - 1);
	}

	void push_back( const value_type& i_val )
	{
		insert(end(),i_val);
	}

	void reserve( size_type i_n )
	{
		if ( i_n > capacity_ )
		{
			PCEVector v(*this);
			DestroyAndDeallocateRange(begin(),end());
			capacity_ = i_n;
			size_ = v.size();
			allocator_.allocate(capacity_);
			size_type index = 0;
			for (const_iterator it = v.begin(); it != v.end(); ++it, ++index)
			{
				allocator_.construct(&data_[index],*it);
			}
		}
	}

	void resize( size_type i_n, value_type i_val = value_type() )
	{
		if ( i_n < size_ )
		{
			DestroyRange( begin() + i_n, end() );
		}

		insert(end(), i_n - size_, i_val);
	}

	size_type size() const
	{
		return size_;
	}

	void swap( PCEVector& i_other )
	{
		PCEVector v(i_other);
		i_other = *this;
		operator=(v);
	}

protected:

	void DestroyRange( iterator i_first, iterator i_last )
	{
		iterator it = i_first;
		while ( it != i_last )
		{
			allocator_.destroy(it++);
		}

		size_ -= (i_last - i_first);
	}

	void DestroyAndDeallocateRange( iterator i_first, iterator i_last )
	{
		DestroyRange(i_first,i_last);
		allocator_.deallocate(i_first,i_last-i_first);
		capacity_ -= (i_last - i_first);
	}

	void Move( iterator i_dest, iterator i_first, iterator i_last )
	{
		PCEVector v(i_first,i_last);
		size_type index_dest = i_dest - begin();
		if  (i_dest - i_first < 0)
		{
			DestroyRange(i_dest,i_last);
		}
		else
		{
			DestroyRange(i_first,i_last);
		}

		for (iterator itV = v.begin(); itV != v.end(); ++itV, ++index_dest)
		{
			allocator_.construct(&data_[index_dest],*itV);
		}

		size_ += v.size();
	}

private:

	size_type	size_;
	size_type	capacity_;
	value_type* data_;
	
	allocator_type allocator_;
};

template<class T, class Alloc>
bool operator==(const PCEVector<T,Alloc>& lhs, const PCEVector<T,Alloc>& rhs);

template<class T, class Alloc>
bool operator!=(const PCEVector<T,Alloc>& lhs, const PCEVector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(const PCEVector<T,Alloc>& lhs, const PCEVector<T,Alloc>& rhs);

template<class T, class Alloc>
bool operator<=(const PCEVector<T,Alloc>& lhs, const PCEVector<T,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<class T, class Alloc>
bool operator>(const PCEVector<T,Alloc>& lhs, const PCEVector<T,Alloc>& rhs)
{
	return rhs < lhs;
}

template<class T, class Alloc>
bool operator>=(const PCEVector<T,Alloc>& lhs, const PCEVector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template<class T, class Alloc>
void swap(PCEVector<T,Alloc>& i_other, PCEVector<T,Alloc>& y)
{
	PCEVector<T,Alloc> v(i_other);
	i_other = y;
	y = v;
}

#endif 
