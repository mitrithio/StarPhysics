#ifndef PCEMAP_H
#define PCEMAP_H

#include <cassert>
#include "PCEUtils.h"
#include "PCEPair.h"
#include "PCEVector.h"

template <class Key, typename T, class Cmp = PCECompareLess<Key>, class Alloc = PCEAllocator< PCEPair< const Key, T > > >
class PCEMap
{
public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef Cmp										key_compare;
	typedef Alloc									allocator_type;
	typedef PCEPair<const key_type, mapped_type>	value_type;
	typedef PCEVector<value_type>					my_base;
	typedef typename my_base::reference				reference;
	typedef typename my_base::const_reference		const_reference;
	typedef typename my_base::iterator				iterator;
	typedef typename my_base::const_iterator		const_iterator;
	typedef std::size_t								size_type;
	typedef std::ptrdiff_t							difference_type;

	typedef iterator								input_iterator;
	
public:

	class value_compare
	{
		friend class PCEMap;
	protected:
		Cmp comp;
		value_compare(Cmp i_cmp) : comp(i_cmp) {}  // constructed with map's comparison object
	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};

public:

	explicit PCEMap(const key_compare& i_cmp = key_compare(), const allocator_type& i_alloc = allocator_type())
		: values_(i_alloc)
		, cmp_(i_cmp)
		, allocator_(i_alloc)
	{}

	explicit PCEMap(const allocator_type& i_alloc)
		: values_(i_alloc)
		, cmp_(PCECompareLess<Key>())
		, allocator_(i_alloc)
	{}

	PCEMap(input_iterator i_first, input_iterator i_last, const key_compare& i_cmp = key_compare(), const allocator_type& i_alloc = allocator_type())
		: values_(i_first,i_last,i_alloc)
		, cmp_(i_cmp)
		, allocator_(i_alloc)
	{
	}

	PCEMap(const PCEMap& i_other)
		: values_(i_other.values_,i_other.allocator_)
		, cmp_(i_other.cmp_)
		, allocator_(i_other.allocator_)
	{}

	~PCEMap()
	{
	}

	mapped_type& at(const key_type& k)
	{
		iterator itWhere = lower_bound(k);
		assert ( itWhere != end() && !key_comp()(k,itWhere.first) ); // out of bound
		return itWhere.second;
	}

	const mapped_type& at(const key_type& k) const
	{
		const_iterator itWhere = lower_bound(k);
		assert ( itWhere != end() && !key_comp()(k,itWhere.first) ); // out of bound
		return itWhere.second;
	}

	iterator begin()
	{
		return values_.begin();
	}

	const_iterator begin() const
	{
		return values_.begin();
	}

	const_iterator cbegin() const
	{
		return values_.cbegin();
	}

	const_iterator cend() const
	{
		return values_.cend();
	}

	void clear()
	{
		erase(begin(),end());
	}

	size_type count(const key_type& k)
	{
		const_iterator itWhere = lower_bound(k);
		if (itWhere != end() && key_comp()(i_oKey,itWhere.first))
		{
			return 1;
		}

		return 0;
	}

	bool empty() const
	{
		return values_.empty();
	}

	iterator end()
	{
		return values_.end();
	}

	const_iterator end() const
	{
		return values_.end();
	}

	PCEPair<iterator,iterator> equal_range(const key_type& k)
	{
		return PCEPair<iterator,iterator>(lower_bound(k),upper_bound(k));
	}

	PCEPair<const_iterator,const_iterator> equal_range(const key_type& k) const
	{
		return PCEPair<const_iterator,const_iterator>(lower_bound(k),upper_bound(k));
	}

	iterator erase(const_iterator position)
	{
		return values_.erase(position);
	}

	size_type erase(const key_type& k)
	{
		iterator pos = find(k);
		if ( pos != end() )
		{
			erase(pos);
			return 1;
		}

		return 0;
	}

	iterator erase(const_iterator first, const_iterator second)
	{
		iterator it = first;
		for ( ; it != second+1 ; it = erase(it) )
		return it;
	}

	iterator find( const key_type& i_k )
	{
		bool bFound = false;
		iterator it = begin();
		for ( ; !bFound && it != end(); ++it )
		{
			bFound = ( (*it).first == i_k );
		}

		if ( bFound )
		{
			return it - 1;
		}

		return it;
	}

	const_iterator find(const key_type& i_k) const
	{
		bool bFound = false;
		const_iterator it = begin();
		for ( ; !bFound && it != end(); ++it )
		{
			bFound = ( (*it).first == i_k );
		}

		if ( bFound )
		{
			return it - 1;
		}

		return it;
	}

	allocator_type get_allocator() const
	{
		return allocator_;
	}

	PCEPair<iterator, bool> insert(const value_type& i_val)
	{
		bool bRet = false;
		for ( iterator itValue = begin(); !bRet && itValue != end(); ++itValue )
		{
			bRet = !cmp_(itValue.first,i_val.first);
		}

		if (bRet) // if true, itValue points to the position after i_val possible position, to end() otherwise.
		{	
			--itValue;
			if ( !cmp_(i_val.first,itValue.first) )
			{ // i_val.first is in the map already
				bRet = false;

				return PCEPair<iterator, bool>(itValue, bRet);
			}
		}
		
		return PCEPair<iterator, bool>( insert(itValue,i_val), bRet ); 
	}

	template<class U, class V> 
	PCEPair<iterator, bool> insert(PCEPair<U,V>&& i_val)
	{
		bool bRet = false;
		iterator itValue = begin();
		for ( ; !bRet && itValue != end(); ++itValue )
		{
			bRet = !cmp_(itValue->first,i_val.first);
		}

		if (bRet) // if true, itValue points to the position after i_val possible position, to end() otherwise.
		{	
			--itValue;
			if ( !cmp_(i_val.first,itValue->first) )
			{ 
				// i_val.first is in the map already
				bRet = false;

				return PCEPair<iterator, bool>(itValue, bRet);
			}
		}

		return PCEPair<iterator, bool>( insert(itValue,i_val), bRet );
	}

	iterator insert(const_iterator i_pos, const value_type& i_val)
	{
		iterator it = find(i_val.first);
		if (it != end())
		{ // i_val.first already in the map
			;
		}
		else if (i_pos != end())
		{ 
			if ( cmp_( (i_pos - 1)->first,i_val.first ) && !cmp_( i_pos->first,i_val.first ) )
			{
				// right position, insert in position i_pos
				size_type indexPos = i_pos - begin();
				it = begin() + indexPos;
				values_.insert(it,1,i_val);
			}
			else
			{
				// wrong position, no insertion;
				it = end();
			}
		}
		else 
		{
			// i_pos == end(), so is to check is the right position
			if ( cmp_( (i_pos - 1)->first,i_val.first ) )
			{
				// insert as last element
				it = end();
				values_.push_back(i_val);
			}
			else
			{
				// wrong position, no insertion;
				it = end();
			}
		}

		return it;
	}

	template<class U, class V> 
	iterator insert(const_iterator i_pos, PCEPair<U,V>&& i_val)
	{
		iterator it = find(i_val.first);
		if (it != end())
		{ // i_val.first already in the map
			;
		}
		else if (i_pos != end())
		{ 
			if ( cmp_( (i_pos - 1)->first,i_val.first ) && !cmp_( i_pos->first,i_val.first ) )
			{
				// right position, insert in position i_pos
				size_type indexPos = i_pos - begin();
				it = begin() + indexPos;
				values_.insert(it,1,i_val);
			}
			else
			{
				// wrong position, no insertion;
				it = end();
			}
		}
		else 
		{
			// i_pos == end(), so is to check is the right position
			if ( cmp_( (i_pos - 1)->first,i_val.first ) )
			{
				// insert as last element
				it = end();
				values_.push_back(i_val);
			}
			else
			{
				// wrong position, no insertion;
				it = end();
			}
		}

		return it;
	}

	void insert(input_iterator i_first, input_iterator i_last)
	{
		for ( ; i_first != i_last; ++i_first )
		{
			insert(*i_first);
		}
	}

	key_compare key_comp() const
	{
		return cmp_;
	}

	iterator lower_bound(const key_type& k)
	{
		iterator it = begin();
		for ( ;
			it != end() ;
			++it )
		{
			if ( !cmp_(it.first, k) )
			{
				return it;
			}
		}

		return it;
	}

	const_iterator lower_bound(const key_type& k) const
	{
		const_iterator it = begin();
		for ( ;
			it != end() ;
			++it )
		{
			if ( !cmp_(it.first, k) )
			{
				return it;
			}
		}

		return it;
	}

	size_type max_size() const
	{
		return values_.max_size();
	}

	PCEMap& operator=(const PCEMap& i_other)
	{
		if ( this != i_other )
		{
			cmp_ = i_other.cmp_;
			allocator_ = i_other.allocator_;
			values_ = i_other.values_;
		}

		return *this;
	}

	mapped_type& operator[](const key_type& i_k)
	{
		return (*((this->insert(make_pair<const key_type,mapped_type>(i_k,mapped_type()))).first)).second;
	}

	mapped_type& operator[](key_type&& i_k)
	{
		return (*((this->insert(make_pair<const key_type,mapped_type>(i_k,mapped_type()))).first)).second;
	}

	size_type size() const
	{
		return values_.size();
	}

	void swap(PCEMap& i_other)
	{
		PCEMap m(*this);
		i_other = *this;
		*this = m;
	}

	iterator upper_bound(const key_type& k)
	{
		iterator it = begin();
		for (  ;
			it != end();
			++it )
		{
			if ( key_comp()(k,it->first) )
			{
				return it;
			}
		}

		return it;
	}

	const_iterator upper_bound(const key_type& k) const
	{
		const_iterator it = begin();
		for (  ;
			it != end();
			++it )
		{
			if ( key_comp()(k,it->first) )
			{
				return it;
			}
		}

		return it;
	}

	value_compare value_comp() const
	{
		return value_compare(cmp_);
	}

private:

	my_base			values_;

	key_compare		cmp_;
	allocator_type	allocator_;
};

#endif