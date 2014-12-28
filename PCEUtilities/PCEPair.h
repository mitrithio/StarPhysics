#ifndef PCEPAIR_H
#define PCEPAIR_H

template<class T1, class T2>
struct PCEPair
{
	T1 first;
	T2 second;

	PCEPair()
		: first()
		, second()
	{}

	template<class U, class V> 
	PCEPair(const PCEPair<U,V>& i_other)
		: first(i_other.first)
		: second(i_other.second)
	{}

	PCEPair(const T1& i_oFirst, const T2& i_oSecond)
		: first(i_oFirst)
		, second(i_oSecond)
	{}

	template<class U, class V> 
	PCEPair(U&& i_oFirst, V&& i_oSecond)
		: first(i_oFirst)
		, second(i_oSecond)
	{}

	PCEPair& operator=(const PCEPair& i_other)
	{
		if (this != &i_other)
		{
			first = i_other.first;
			second = i_other.second;
		}

		return *this;
	}

	template<class U, class V> 
	PCEPair& operator=(const PCEPair<U,V>& i_other)
	{
		if (this != &i_other)
		{
			first = i_other.first;
			second = i_other.second;
		}

		return *this;
	}
};

template <class T1, class T2>
bool operator==(const PCEPair<T1,T2>& i_left, const PCEPair<T1,T2>& i_right)
{ 
	return i_left.first==i_right.first && i_left.second==i_right.second; 
}

template <class T1, class T2>
bool operator!=(const PCEPair<T1,T2>& i_left, const PCEPair<T1,T2>& i_right)
{ 
	return !(i_left==i_right); 
}

template <class T1, class T2>
bool operator<(const PCEPair<T1,T2>& i_left, const PCEPair<T1,T2>& i_right)
{ 
	return i_left.first<i_right.first || (!(i_right.first<i_left.first) && i_left.second<i_right.second); 
}

template <class T1, class T2>
bool operator<=(const PCEPair<T1,T2>& i_left, const PCEPair<T1,T2>& i_right)
{ 
	return !(i_right<i_left);
}

template <class T1, class T2>
bool operator>(const PCEPair<T1,T2>& i_left, const PCEPair<T1,T2>& i_right)
{ 
	return i_right<i_left;
}

template <class T1, class T2>
bool operator>=(const PCEPair<T1,T2>& i_left, const PCEPair<T1,T2>& i_right)
{ 
	return !(i_left<i_right);
}

#endif	//PCEPAIR_H