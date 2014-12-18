#ifndef PCEMATRIX_H
#define	PCEMATRIX_H

#include <cmath>

template<unsigned int ROW,unsigned int COL>
class PCEMatrix
{
public:

	PCEMatrix();

	PCEMatrix( const double i_args[], unsigned int i_uiCount = ROW*COL );

	PCEMatrix( const PCEMatrix<ROW,COL>& i_other );
	
	~PCEMatrix();

	PCEMatrix<ROW,COL>& operator=( const PCEMatrix<ROW,COL>& i_other );

	bool operator==(const PCEMatrix<ROW,COL>& i_other) const;
	
	bool operator!=(const PCEMatrix<ROW,COL>& i_other) const;

	PCEMatrix<ROW,COL>& operator+=( const PCEMatrix<ROW,COL>& i_other );

	PCEMatrix<ROW,COL> operator+( const PCEMatrix<ROW,COL>& i_other );

	template<unsigned int COL2>
	PCEMatrix<ROW,COL2> operator*( const PCEMatrix<COL,COL2>& i_other );

	PCEMatrix<ROW,COL>& operator*=( double i_fScalar );

	PCEMatrix<ROW,COL> operator*( double i_fScalar );

	double* operator[]( unsigned int i_uiRow );

	const double* operator[]( unsigned int i_uiRow ) const;

private:

	double*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};



/* *** template specializtion *** */

template<unsigned int N>
class PCEMatrix<N,N>
{
public:

	PCEMatrix();

	PCEMatrix( const double i_args[], unsigned int i_uiCount = N*N );

	PCEMatrix( const PCEMatrix<N,N>& i_other );

	~PCEMatrix();

	PCEMatrix<N,N>& operator=( const PCEMatrix<N,N>& i_other );

	bool operator==(const PCEMatrix<N,N>& i_other);

	bool operator!=(const PCEMatrix<N,N>& i_other);

	template<unsigned int COL>
	PCEMatrix<N,COL> operator*( const PCEMatrix<N,COL>& i_other );

	PCEMatrix<N,N>& operator*=( double i_fScalar );

	PCEMatrix<N,N> operator*( double i_fScalar );

	double* operator[]( unsigned int i_uiRow );

	const double* operator[]( unsigned int i_uiRow ) const;

private:

	double*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};



/* *** template specializtion *** */

template<unsigned int N>
class PCEMatrix<1,N>;
template<unsigned int N>
class PCEMatrix<N,1>
{
public:

	PCEMatrix();

	PCEMatrix( const double i_args[], unsigned int i_uiCount = N );

	PCEMatrix( const PCEMatrix<N,1>& i_other );

	PCEMatrix( const PCEMatrix<1,N>& i_other );

	~PCEMatrix();

	PCEMatrix<N,1>& operator=( const PCEMatrix<N,1>& i_other );

	bool operator==(const PCEMatrix<N,1>& i_other) const;
	
	bool operator!=(const PCEMatrix<N,1>& i_other) const;

	PCEMatrix<N,1>& operator+=( const PCEMatrix<N,1>& i_other );

	PCEMatrix<N,1> operator+( const PCEMatrix<N,1>& i_other ) const;

	PCEMatrix<N,1>& operator-=( const PCEMatrix<N,1>& i_other );

	PCEMatrix<N,1> operator-( const PCEMatrix<N,1>& i_other ) const;

	template<unsigned int COL2>
	PCEMatrix<N,COL2> operator*( const PCEMatrix<1,COL2>& i_other ) const;

	PCEMatrix<N,N> operator*(const PCEMatrix<1,N>& i_other ) const;

	PCEMatrix<N,1>& operator*=( double i_fScalar );

	PCEMatrix<N,1> operator*( double i_fScalar ) const;

	PCEMatrix<N,1>& operator/=( double i_fScalar );

	PCEMatrix<N,1> operator/( double i_fScalar ) const;

	double& operator[]( unsigned int i_uiRow );

	const double& operator[]( unsigned int i_uiRow ) const;

	double Module() const;

	PCEMatrix<N,1> Normal() const;

	operator PCEMatrix<1,N>();

private:

	double*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};



/* *** template specializtion *** */

template<unsigned int N>
class PCEMatrix<1,N>
{
public:

	PCEMatrix();

	PCEMatrix( const double i_args[], unsigned int i_uiCount = N );

	PCEMatrix( const PCEMatrix<1,N>& i_other );

	PCEMatrix( const PCEMatrix<N,1>& i_other );

	~PCEMatrix();

	PCEMatrix<1,N>& operator=( const PCEMatrix<1,N>& i_other );

	bool operator==(const PCEMatrix<1,N>& i_other) const;

	bool operator!=(const PCEMatrix<1,N>& i_other) const;

	PCEMatrix<1,N>& operator+=( const PCEMatrix<1,N>& i_other );

	PCEMatrix<1,N> operator+( const PCEMatrix<1,N>& i_other ) const;

	PCEMatrix<1,N>& operator-=( const PCEMatrix<1,N>& i_other );

	PCEMatrix<1,N> operator-( const PCEMatrix<1,N>& i_other ) const;

	template<unsigned int COL2>
	PCEMatrix<1,COL2> operator*( const PCEMatrix<N,COL2>& i_other ) const;
	
	double operator*( const PCEMatrix<N,1>& i_other ) const;

	PCEMatrix<1,N>& operator*=( double i_fScalar );

	PCEMatrix<1,N> operator*( double i_fScalar ) const;

	PCEMatrix<1,N>& operator/=( double i_fScalar );

	PCEMatrix<1,N> operator/( double i_fScalar ) const;

	double& operator[]( unsigned int i_uiRow );

	const double& operator[]( unsigned int i_uiRow ) const;

	double Module() const;

	PCEMatrix<1,N> Normal() const;

	operator PCEMatrix<N,1>();

private:

	double*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};

template<unsigned int ROW,unsigned int COL>
PCEMatrix<ROW, COL>::PCEMatrix() 
	: m_uiRows( ROW )
	, m_uiColumns( COL )
{
	m_mMatrix = new double[ ROW * COL ]();
}

template<unsigned int ROW, unsigned int COL>
PCEMatrix<ROW,COL>::PCEMatrix( const double i_args[], unsigned int i_uiCount /*= ROW*COL*/ )
	: m_uiRows( ROW )
	, m_uiColumns( COL )
{
	m_mMatrix = new double[ROW*COL]();
	unsigned int uiIndex = 0;
	if ( i_uiCount <= ROW*COL )
	{
		for ( ; uiIndex < i_uiCount; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_args[uiIndex];
		}
	}

	for ( ; uiIndex < ROW*COL; ++uiIndex )
	{
		m_mMatrix[uiIndex] = 0.0f;
	}
}

template<unsigned int ROW,unsigned int COL>
PCEMatrix<ROW, COL>::PCEMatrix( const PCEMatrix<ROW,COL>& i_other )
	: m_uiRows( i_other.m_uiRows )
	, m_uiColumns( i_other.m_uiColumns )
{
	m_mMatrix = new double[ ROW * COL ]();
	for ( unsigned int uiIndex = 0; uiIndex < ROW*COL; ++uiIndex )
	{
		m_mMatrix[uiIndex] = i_other.m_mMatrix[uiIndex];
	}
}

template<unsigned int ROW,unsigned int COL>
PCEMatrix<ROW, COL>::~PCEMatrix()
{
	delete [] m_mMatrix;
}

template<unsigned int ROW,unsigned int COL>
PCEMatrix<ROW,COL>& PCEMatrix<ROW, COL>::operator=( const PCEMatrix<ROW,COL>& i_other )
{
	if ( this != &i_other )
	{
		for ( unsigned int uiIndex = 0; uiIndex < ROW*COL; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_other.m_mMatrix[uiIndex];
		}
	}

	return *this;
}

template<unsigned int ROW,unsigned int COL>
bool PCEMatrix<ROW, COL>::operator==( const PCEMatrix<ROW,COL>& i_other ) const
{
	bool bEqual = true;
	if ( this != &i_other )
	{
		for ( unsigned int uiIndex = 0; bEqual && uiIndex < ROW*COL; ++uiIndex )
		{
			bEqual = m_mMatrix[uiIndex] == i_other.m_mMatrix[uiIndex];
		}
	}
	return bEqual;
}

template<unsigned int ROW,unsigned int COL>
bool PCEMatrix<ROW, COL>::operator!=( const PCEMatrix<ROW,COL>& i_other ) const
{
	return !((*this) == i_other);
}

template<unsigned int ROW,unsigned int COL>
PCEMatrix<ROW,COL>& PCEMatrix<ROW, COL>::operator+=( const PCEMatrix<ROW,COL>& i_other )
{
	for ( unsigned int uiIndex = 0; uiIndex < ROW*COL; ++uiIndex )
	{
		m_mMatrix[uiIndex] += i_other.m_mMatrix[uiIndex];
	}

	return *this;
}

template<unsigned int ROW,unsigned int COL>
PCEMatrix<ROW,COL> PCEMatrix<ROW, COL>::operator+( const PCEMatrix<ROW,COL>& i_other )
{
	PCEMatrix<ROW,COL> oRes = *this;
	oRes += i_other;
	return oRes;
}

template<unsigned int ROW, unsigned int COL>
template<unsigned int COL2>
PCEMatrix<ROW,COL2> PCEMatrix<ROW,COL>::operator*( const PCEMatrix<COL,COL2>& i_other )
{
	PCEMatrix<ROW,COL2> oMatrix();
	for ( unsigned int uiRow = 0; uiRow < ROW; ++uiRow )
	{
		for ( unsigned int uiCol = 0; uiCol < COL2; ++uiCol )
		{
			for ( unsigned int uiIndex = 0; uiIndex < COL; ++uiIndex )
			{
				oMatrix[uiRow][uiCol] += (*this)[uiRow][uiIndex] * i_other[uiIndex][uiCol];
			}
		}
	}

	return oMatrix;
}

template<unsigned int ROW, unsigned int COL>
PCEMatrix<ROW,COL>& PCEMatrix<ROW,COL>::operator*=( double i_fScalar )
{
	for ( unsigned int uiRow = 0; uiRow < ROW; ++uiRow )
	{
		for ( unsigned int uiCol = 0; uiCol < COL; ++uiCol )
		{
			(*this)[uiRow][uiCol] *= i_fScalar;
		}
	}

	return *this;
}

template<unsigned int ROW, unsigned int COL>
PCEMatrix<ROW,COL> PCEMatrix<ROW,COL>::operator*( double i_fScalar )
{
	PCEMatrix<ROW,COL> res = *this;
	res *= i_fScalar;
	return res;
}

template<unsigned int ROW, unsigned int COL>
double* PCEMatrix<ROW,COL>::operator[]( unsigned int i_uiRow )
{
	return &m_mMatrix[ i_uiRow * COL ];
}

template<unsigned int ROW, unsigned int COL>
const double* PCEMatrix<ROW,COL>::operator[]( unsigned int i_uiRow ) const
{
	return &m_mMatrix[ i_uiRow * COL ];
}



template<unsigned int N>
PCEMatrix<N,N>::PCEMatrix()
	: m_uiColumns(N)
	, m_uiRows(N)
{
	m_mMatrix = new double[N*N]();
}

template<unsigned int N>
PCEMatrix<N,N>::PCEMatrix( const double i_args[], unsigned int i_uiCount /*= N*N*/ )
	: m_uiRows( N )
	, m_uiColumns( N )
{
	m_mMatrix = new double[N*N]();
	unsigned int uiIndex = 0;
	if ( i_uiCount <= N*N )
	{
		for ( ; uiIndex < i_uiCount; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_args[uiIndex];
		}
	}

	for ( ; uiIndex < N*N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = 0.0f;
	}
}

template<unsigned int N>
PCEMatrix<N,N>::PCEMatrix( const PCEMatrix<N,N>& i_other )
	: m_uiColumns(N)
	, m_uiRows(N)
{
	m_mMatrix = new double[N*N]();
	for ( unsigned int uiIndex = 0; uiIndex < N*N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = i_other.m_mMatrix[uiIndex];
	}
}

template<unsigned int N>
PCEMatrix<N,N>::~PCEMatrix()
{
	delete [] m_mMatrix;
}

template<unsigned int N>
PCEMatrix<N,N>& PCEMatrix<N,N>::operator=( const PCEMatrix<N,N>& i_other )
{
	if ( this != &i_other )
	{
		for ( unsigned int uiIndex = 0; uiIndex < N*N; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_other.m_mMatrix[uiIndex];
		}
	}

	return *this;
}

template<unsigned int N>
bool PCEMatrix<N,N>::operator==(const PCEMatrix<N,N>& i_other)
{
	bool bEqual = true;
	if ( this != &i_other )
	{
		for ( unsigned int uiIndex = 0; bEqual && uiIndex < N*N; ++uiIndex )
		{
			bEqual = m_mMatrix[uiIndex] == i_other.m_mMatrix[uiIndex];
		}
	}
	return bEqual;
}

template<unsigned int N>
bool PCEMatrix<N,N>::operator!=(const PCEMatrix<N,N>& i_other)
{
	return !((*this) == i_other);
}

template<unsigned int N>
template<unsigned int COL>
PCEMatrix<N,COL> PCEMatrix<N,N>::operator*( const PCEMatrix<N,COL>& i_other )
{
	PCEMatrix<N,COL> oMatrix();
	for ( unsigned int uiRow = 0; uiRow < N; ++uiRow )
	{
		for ( unsigned int uiCol = 0; uiCol < COL; ++uiCol )
		{
			for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
			{
				oMatrix[uiRow][uiCol] += (*this)[uiRow][uiIndex] * i_other[uiIndex][uiCol];
			}
		}
	}

	return oMatrix;
}

template<unsigned int N>
PCEMatrix<N,N>& PCEMatrix<N,N>::operator*=( double i_fScalar )
{
	for ( unsigned int uiRow = 0; uiRow < N; ++uiRow )
	{
		for ( unsigned int uiCol = 0; uiCol < N; ++uiCol )
		{
			(*this)[uiRow][uiCol] *= i_fScalar;
		}
	}

	return *this;
}

template<unsigned int N>
PCEMatrix<N,N> PCEMatrix<N,N>::operator*( double i_fScalar )
{
	PCEMatrix<N,N> res = *this;
	res *= i_fScalar;
	return res;
}

template<unsigned int N>
double* PCEMatrix<N,N>::operator[]( unsigned int i_uiRow )
{
	return &m_mMatrix[ i_uiRow * N ];
}

template<unsigned int N>
const double* PCEMatrix<N,N>::operator[]( unsigned int i_uiRow ) const
{
	return &m_mMatrix[ i_uiRow * N ];
}




template<unsigned int N>
PCEMatrix<N,1>::PCEMatrix()
	: m_uiRows(N)
	, m_uiColumns(1)
{
	m_mMatrix = new double[N];
}

template<unsigned int N>
PCEMatrix<N,1>::PCEMatrix( const double i_args[], unsigned int i_uiCount /*= N*/ )
	: m_uiRows( N )
	, m_uiColumns( 1 )
{
	m_mMatrix = new double[N]();
	unsigned int uiIndex = 0;
	if ( i_uiCount <= N )
	{
		for ( ; uiIndex < i_uiCount; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_args[uiIndex];
		}
	}

	for ( ; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = 0.0f;
	}
}

template<unsigned int N>
PCEMatrix<N,1>::PCEMatrix( const PCEMatrix<N,1>& i_other )
	: m_uiRows(N)
	, m_uiColumns(1)
{
	m_mMatrix = new double[N];
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = i_other[uiIndex];
	}
}

template<unsigned int N>
PCEMatrix<N,1>::PCEMatrix( const PCEMatrix<1,N>& i_other )
	: m_uiRows(N)
	, m_uiColumns(1)
{
	m_mMatrix = new double[N];
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = i_other[uiIndex];
	}
}

template<unsigned int N>
PCEMatrix<N,1>::~PCEMatrix()
{
	delete [] m_mMatrix;
}

template<unsigned int N>
PCEMatrix<N,1>& PCEMatrix<N,1>::operator=( const PCEMatrix<N,1>& i_other )
{
	if ( this != &i_other )
	{
		for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_other[uiIndex];
		}
	}
	return *this;
}

template<unsigned int N>
bool PCEMatrix<N,1>::operator==( const PCEMatrix<N,1>& i_other ) const
{
	bool bEqual = true;
	for ( unsigned int uiIndex = 0; bEqual && uiIndex < N; ++uiIndex )
	{
		bEqual = m_mMatrix[uiIndex] == i_other[uiIndex];
	}

	return bEqual;
}

template<unsigned int N>
bool PCEMatrix<N,1>::operator!=( const PCEMatrix<N,1>& i_other ) const
{
	return !(*this == i_other);
}

template<unsigned int N>
PCEMatrix<N,1>& PCEMatrix<N,1>::operator+=( const PCEMatrix<N,1>& i_other )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] += i_other[uiIndex];
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<N,1> PCEMatrix<N,1>::operator+( const PCEMatrix<N,1>& i_other ) const
{
	PCEMatrix<N,1> oVector = *this;
	oVector += i_other;
	return oVector;
}

template<unsigned int N>
PCEMatrix<N,1>& PCEMatrix<N,1>::operator-=( const PCEMatrix<N,1>& i_other )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] -= i_other[uiIndex];
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<N,1> PCEMatrix<N,1>::operator-( const PCEMatrix<N,1>& i_other ) const
{
	PCEMatrix<N,1> oVector = *this;
	oVector -= i_other;
	return oVector;
}

template<unsigned int N>
template<unsigned int COL2>
PCEMatrix<N,COL2> PCEMatrix<N,1>::operator*( const PCEMatrix<1,COL2>& i_other ) const
{
	PCEMatrix<N,COL2> oMatrix();
	for ( unsigned int uiCol = 0; uiCol < COL2; ++uiCol )
	{
		for ( unsigned int uiRow = 0; uiRow < N; ++uiRow )
		{
			oMatrix[uiRow][uiCol] += (*this)[uiRow] * i_other[0][uiCol];
		}
	}

	return oMatrix;
}

template<unsigned int N>
PCEMatrix<N,1>& PCEMatrix<N,1>::operator*=( double i_fScalar )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] *= i_fScalar;
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<N,1> PCEMatrix<N,1>::operator*( double i_fScalar ) const
{
	PCEMatrix<N,1> oVector = *this;
	oVector *= i_fScalar;
	return oVector;
}

template<unsigned int N>
PCEMatrix<N,N> PCEMatrix<N,1>::operator*( const PCEMatrix<1,N>& i_other ) const
{
	PCEMatrix<N,N> oRes;
	for ( unsigned int uiRow = 0; uiRow < N; ++uiRow )
	{
		for ( unsigned int uiCol = 0; uiCol < N; ++uiCol )
		{
			oRes[uiRow][uiCol] = (*this)[uiRow] * i_other[uiCol];
		}
	}
	return oRes;
}

template<unsigned int N>
PCEMatrix<N,1>& PCEMatrix<N,1>::operator/=( double i_fScalar )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] /= i_fScalar;
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<N,1> PCEMatrix<N,1>::operator/( double i_fScalar ) const
{
	PCEMatrix<N,1> oVector = *this;
	oVector /= i_fScalar;
	return oVector;
}

template<unsigned int N>
double& PCEMatrix<N,1>::operator[]( unsigned int i_uiIndex )
{
	return m_mMatrix[i_uiIndex];
}

template<unsigned int N>
const double& PCEMatrix<N,1>::operator[]( unsigned int i_uiIndex ) const
{
	return m_mMatrix[i_uiIndex];
}

template<unsigned int N>
double PCEMatrix<N,1>::Module() const
{
	double fModuleModule = 0;
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		fModuleModule += m_mMatrix[uiIndex] * m_mMatrix[uiIndex];
	}

	return sqrt(fModuleModule);
}

template<unsigned int N>
PCEMatrix<N,1> PCEMatrix<N,1>::Normal() const
{
	double fModule = Module();
	PCEMatrix<N,1> oVector = *this;
	if(fModule > 0.000001f)
	{
		for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
		{
			oVector[uiIndex] /= fModule;
		}
	}

	return oVector;
}

template<unsigned int N>
PCEMatrix<N,1>::operator PCEMatrix<1,N>()
{
	return PCEMatrix<1,N>(*this);
}



template<unsigned int N>
PCEMatrix<1,N>::PCEMatrix()
	: m_uiRows(1)
	, m_uiColumns(N)
{
	m_mMatrix = new double[N];
}

template<unsigned int N>
PCEMatrix<1,N>::PCEMatrix( const double i_args[], unsigned int i_uiCount /*= N*/ )
	: m_uiRows( 1 )
	, m_uiColumns( N )
{
	m_mMatrix = new double[N]();
	unsigned int uiIndex = 0;
	if ( i_uiCount <= N )
	{
		for ( ; uiIndex < i_uiCount; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_args[uiIndex];
		}
	}

	for ( ; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = 0.0f;
	}
}

template<unsigned int N>
PCEMatrix<1,N>::PCEMatrix( const PCEMatrix<1,N>& i_other )
	: m_uiRows(1)
	, m_uiColumns(N)
{
	m_mMatrix = new double[N];
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = i_other[uiIndex];
	}
}

template<unsigned int N>
PCEMatrix<1,N>::PCEMatrix( const PCEMatrix<N,1>& i_other )
	: m_uiRows(1)
	, m_uiColumns(N)
{
	m_mMatrix = new double[N];
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] = i_other[uiIndex];
	}
}

template<unsigned int N>
PCEMatrix<1,N>::~PCEMatrix()
{
	delete [] m_mMatrix;
}

template<unsigned int N>
PCEMatrix<1,N>& PCEMatrix<1,N>::operator=( const PCEMatrix<1,N>& i_other )
{
	if ( this != &i_other )
	{
		for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
		{
			m_mMatrix[uiIndex] = i_other[uiIndex];
		}
	}
	return *this;
}

template<unsigned int N>
bool PCEMatrix<1,N>::operator==( const PCEMatrix<1,N>& i_other ) const
{

	bool bEqual = true;
	for ( unsigned int uiIndex = 0; bEqual && uiIndex < N; ++uiIndex )
	{
		bEqual = m_mMatrix[uiIndex] == i_other[uiIndex];
	}
	return bEqual;
}

template<unsigned int N>
bool PCEMatrix<1,N>::operator!=( const PCEMatrix<1,N>& i_other ) const
{
	return !(*this == i_other);
}

template<unsigned int N>
PCEMatrix<1,N>& PCEMatrix<1,N>::operator+=( const PCEMatrix<1,N>& i_other )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] += i_other[uiIndex];
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<1,N> PCEMatrix<1,N>::operator+( const PCEMatrix<1,N>& i_other ) const
{
	PCEMatrix<1,N> oVector = *this;
	oVector += i_other;
	return oVector;
}

template<unsigned int N>
PCEMatrix<1,N>& PCEMatrix<1,N>::operator-=( const PCEMatrix<1,N>& i_other )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] -= i_other[uiIndex];
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<1,N> PCEMatrix<1,N>::operator-( const PCEMatrix<1,N>& i_other ) const
{
	PCEMatrix<1,N> oVector = *this;
	oVector -= i_other;
	return oVector;
}

template<unsigned int N>
template<unsigned int COL2>
PCEMatrix<1,COL2> PCEMatrix<1,N>::operator*( const PCEMatrix<N,COL2>& i_other ) const
{
	PCEMatrix<1,COL2> oMatrix();
	for ( unsigned int uiCol = 0; uiCol < COL2; ++uiCol )
	{
		for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
		{
			oMatrix[0][uiCol] += (*this)[uiIndex] * i_other[uiIndex][uiCol];
		}
	}

	return oMatrix;
}

template<unsigned int N>
PCEMatrix<1,N>& PCEMatrix<1,N>::operator*=( double i_fScalar )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] *= i_fScalar;
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<1,N> PCEMatrix<1,N>::operator*( double i_fScalar ) const
{
	PCEMatrix<1,N> oVector = *this;
	oVector *= i_fScalar;
	return oVector;
}

template<unsigned int N>
double PCEMatrix<1,N>::operator*( const PCEMatrix<N,1>& i_other ) const
{
	double fRes = 0;
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		fRes += m_mMatrix[uiIndex] * i_other[uiIndex];
	}

	return fRes;
}

template<unsigned int N>
PCEMatrix<1,N>& PCEMatrix<1,N>::operator/=( double i_fScalar )
{
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		m_mMatrix[uiIndex] /= i_fScalar;
	}
	return *this;
}

template<unsigned int N>
PCEMatrix<1,N> PCEMatrix<1,N>::operator/( double i_fScalar ) const
{
	PCEMatrix<1,N> oVector = *this;
	oVector /= i_fScalar;
	return oVector;
}

template<unsigned int N>
double& PCEMatrix<1,N>::operator[]( unsigned int i_uiIndex )
{
	return m_mMatrix[i_uiIndex];
}

template<unsigned int N>
const double& PCEMatrix<1,N>::operator[]( unsigned int i_uiIndex ) const
{
	return m_mMatrix[i_uiIndex];
}

template<unsigned int N>
double PCEMatrix<1,N>::Module() const
{
	double fModuleModule = 0;
	for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
	{
		fModuleModule += m_mMatrix[uiIndex] * m_mMatrix[uiIndex];
	}

	return sqrt(fModuleModule);
}

template<unsigned int N>
PCEMatrix<1,N> PCEMatrix<1,N>::Normal() const
{
	double fModule = Module();
	PCEMatrix<1,N> oVector = *this;
	if(fModule > 0.000001f)
	{
		for ( unsigned int uiIndex = 0; uiIndex < N; ++uiIndex )
		{
			oVector[uiIndex] /= fModule;
		}
	}

	return oVector;
}

template<unsigned int N>
PCEMatrix<1,N>::operator PCEMatrix<N,1>()
{
	return PCEMatrix<N,1>( *this );
}

#endif // PCEMATRIX_H