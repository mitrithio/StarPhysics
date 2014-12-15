#ifndef PCEMATRIX_H
#define	PCEMATRIX_H

#include <math.h>

template<unsigned int ROW,unsigned int COL>
class PCEMatrix
{
public:

	PCEMatrix();

	PCEMatrix( const float i_args[], unsigned int i_uiCount = ROW*COL );

	PCEMatrix( const PCEMatrix<ROW,COL>& i_other );
	
	~PCEMatrix();

	PCEMatrix<ROW,COL>& operator=( const PCEMatrix<ROW,COL>& i_other );

	bool operator==(const PCEMatrix<ROW,COL>& i_other) const;
	
	bool operator!=(const PCEMatrix<ROW,COL>& i_other) const;

	PCEMatrix<ROW,COL>& operator+=( const PCEMatrix<ROW,COL>& i_other );

	PCEMatrix<ROW,COL> operator+( const PCEMatrix<ROW,COL>& i_other );

	template<unsigned int COL2>
	PCEMatrix<ROW,COL2> operator*( const PCEMatrix<COL,COL2>& i_other );

	PCEMatrix<ROW,COL>& operator*=( float i_fScalar );

	PCEMatrix<ROW,COL> operator*( float i_fScalar );

	float* operator[]( unsigned int i_uiRow ) const;

private:

	float*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};

template<unsigned int N>
class PCEMatrix<N,N>
{
public:

	PCEMatrix();

	PCEMatrix( const float i_args[], unsigned int i_uiCount = N*N );

	PCEMatrix( const PCEMatrix<N,N>& i_other );

	~PCEMatrix();

	PCEMatrix<N,N>& operator=( const PCEMatrix<N,N>& i_other );

	bool operator==(const PCEMatrix<N,N>& i_other);

	bool operator!=(const PCEMatrix<N,N>& i_other);

	template<unsigned int COL>
	PCEMatrix<N,COL> operator*( const PCEMatrix<N,COL>& i_other );

	PCEMatrix<N,N>& operator*=( float i_fScalar );

	PCEMatrix<N,N> operator*( float i_fScalar );

	float* operator[]( unsigned int i_uiRow ) const;

private:

	float*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};

template<unsigned int N>
class PCEMatrix<1,N>;
template<unsigned int N>
class PCEMatrix<N,1>
{
public:

	PCEMatrix();

	PCEMatrix( const float i_args[], unsigned int i_uiCount = N );

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

	PCEMatrix<N,1>& operator*=( float i_fScalar );

	PCEMatrix<N,1> operator*( float i_fScalar ) const;

	PCEMatrix<N,1>& operator/=( float i_fScalar );

	PCEMatrix<N,1> operator/( float i_fScalar ) const;

	float& operator[]( unsigned int i_uiRow ) const;

	float Module() const;

	PCEMatrix<N,1> Normal() const;

	operator PCEMatrix<1,N>();

private:

	float*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};

template<unsigned int N>
class PCEMatrix<1,N>
{
public:

	PCEMatrix();

	PCEMatrix( const float i_args[], unsigned int i_uiCount = N );

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
	
	float operator*( const PCEMatrix<N,1>& i_other ) const;

	PCEMatrix<1,N>& operator*=( float i_fScalar );

	PCEMatrix<1,N> operator*( float i_fScalar ) const;

	PCEMatrix<1,N>& operator/=( float i_fScalar );

	PCEMatrix<1,N> operator/( float i_fScalar ) const;

	float& operator[]( unsigned int i_uiRow ) const;

	float Module() const;

	PCEMatrix<1,N> Normal() const;

	operator PCEMatrix<N,1>();

private:

	float*		 m_mMatrix;
	unsigned int m_uiRows;
	unsigned int m_uiColumns;
};

#endif // PCEMATRIX_H