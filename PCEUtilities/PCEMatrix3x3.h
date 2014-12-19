#pragma once

#include "PCEVector3.h"
#include <cassert>

class PCEMatrix3x3
{

public:

	PCEMatrix3x3()
	{
		m_vRowVectors[0].x() = 1;
		m_vRowVectors[1].y() = 1;
		m_vRowVectors[2].z() = 1;
	}

	PCEMatrix3x3( const PCEVector3D& i_oRow0, const PCEVector3D& i_oRow1, const PCEVector3D& i_oRow2 )
	{
		m_vRowVectors[0] = i_oRow0;
		m_vRowVectors[1] = i_oRow1;
		m_vRowVectors[2] = i_oRow2;
	}

	PCEVector3D& operator[]( unsigned int i_uiRowIndex )
	{
		assert( i_uiRowIndex >= 0 && i_uiRowIndex < 3 );
		return m_vRowVectors[i_uiRowIndex];
	}

	const PCEVector3D& operator[]( unsigned int i_uiRowIndex ) const
	{
		assert( i_uiRowIndex >= 0 && i_uiRowIndex < 3 );
		return m_vRowVectors[i_uiRowIndex];
	}

	const bool operator==( const PCEMatrix3x3& i_other ) const
	{
		return m_vRowVectors[0]==i_other.m_vRowVectors[0] && m_vRowVectors[1]==i_other.m_vRowVectors[1] && m_vRowVectors[2]==i_other.m_vRowVectors[2];
	}

	const bool operator!=( const PCEMatrix3x3& i_other ) const
	{
		return !(i_other == *this);
	}

	const PCEMatrix3x3& operator=( const PCEMatrix3x3& i_other )
	{
		m_vRowVectors[0] = i_other.m_vRowVectors[0];
		m_vRowVectors[1] = i_other.m_vRowVectors[1];
		m_vRowVectors[2] = i_other.m_vRowVectors[2];

		return *this;
	}

	const PCEMatrix3x3& operator+=( const PCEMatrix3x3& m )
	{
		m_vRowVectors[0] += m.m_vRowVectors[0];
		m_vRowVectors[1] += m.m_vRowVectors[1];
		m_vRowVectors[2] += m.m_vRowVectors[2];

		return *this;
	}

	const PCEMatrix3x3& operator+=( const PCEMatrix3x3& m )
	{
		m_vRowVectors[0] -= m.m_vRowVectors[0];
		m_vRowVectors[1] -= m.m_vRowVectors[1];
		m_vRowVectors[2] -= m.m_vRowVectors[2];

		return *this;
	}

	const PCEMatrix3x3& operator*=( double& s )
	{
		m_vRowVectors[0] *= s;
		m_vRowVectors[1] *= s;
		m_vRowVectors[2] *= s;

		return *this;
	}

	const PCEMatrix3x3& operator*=( const PCEMatrix3x3& m )
	{

		//NOTE: don’t change the columns

		//in the middle of the operation

		PCEMatrix3x3 temp = (*this);

		m_vRowVectors[0] = temp * m.m_vRowVectors[0];
		m_vRowVectors[1] = temp * m.m_vRowVectors[1];
		m_vRowVectors[2] = temp * m.m_vRowVectors[2];

		return *this;

	}

	inline PCEMatrix3x3 operator+( const PCEMatrix3x3& m ) const
	{
		return PCEMatrix3x3( m_vRowVectors[0] + m.m_vRowVectors[0], m_vRowVectors[1] + m.m_vRowVectors[1], m_vRowVectors[2] + m.m_vRowVectors[2] );
	}

	inline PCEMatrix3x3 operator-( const PCEMatrix3x3& m ) const
	{
		return PCEMatrix3x3( m_vRowVectors[0] - m.m_vRowVectors[0], m_vRowVectors[1] - m.m_vRowVectors[1], m_vRowVectors[2] - m.m_vRowVectors[2] );
	}

	inline PCEMatrix3x3 operator*( const double& s ) const
	{
		return PCEMatrix3x3( m_vRowVectors[0]*s, m_vRowVectors[1]*s, m_vRowVectors[2]*s );
	}

	friend inline PCEMatrix3x3 operator*( const double& s, const PCEMatrix3x3& m )
	{
		return m * s;
	}

	inline PCEVector3D operator*( const PCEVector3D& v ) const
	{
		return PCEVector3D( m_vRowVectors[0]*v.x() + m_vRowVectors[1]*v.y() + m_vRowVectors[2]*v.z() );
	}

	friend inline PCEVector3D operator*( const PCEVector3D& v, const PCEMatrix3x3& m )
	{
		return PCEVector3D( m.m_vRowVectors[0].Dot(v), m.m_vRowVectors[1].Dot(v), m.m_vRowVectors[2].Dot(v) );
	}

	inline PCEMatrix3x3 operator*( const PCEMatrix3x3& m ) const
	{
		return PCEMatrix3x3( (*this)*m.m_vRowVectors[0], (*this)*m.m_vRowVectors[1], (*this)*m.m_vRowVectors[2] );
	}

	inline PCEMatrix3x3 transpose() const
	{
		return PCEMatrix3x3( PCEVector3D( m_vRowVectors[0].x(), m_vRowVectors[1].x(), m_vRowVectors[2].x() )	//column 0
						   , PCEVector3D( m_vRowVectors[0].y(), m_vRowVectors[1].y(), m_vRowVectors[2].y() )	//column 1
						   , PCEVector3D( m_vRowVectors[0].z(), m_vRowVectors[1].z(), m_vRowVectors[2].z() )	//column 2
						   );
	}

	inline double determinant() const
	{
		return m_vRowVectors[0].Dot( m_vRowVectors[1].Cross(m_vRowVectors[2]) );
	}

	inline const PCEMatrix3x3 inverse() const
	{
		double rDet = determinant();
		
		assert(rDet != 0.0);
		if ( rDet != 0.0 )
		{
			double rCoef = 1 / determinant();
			return PCEMatrix3x3( adjoint() * rCoef );
		}
		
		return PCEMatrix3x3();
	}

	inline PCEMatrix3x3 adjoint() const
	{
		return PCEMatrix3x3( PCEVector3D(cofactor(1, 1, 2, 2), cofactor(0, 2, 2, 1), cofactor(0, 1, 1, 2))
						   , PCEVector3D(cofactor(1, 2, 2, 0), cofactor(0, 0, 2, 2), cofactor(0, 2, 1, 0))
						   , PCEVector3D(cofactor(1, 0, 2, 1), cofactor(0, 1, 2, 0), cofactor(0, 0, 1, 1)) 
						   );
	}

	inline double cofactor( unsigned int i_uiRow1, unsigned int i_uiCol1, unsigned int i_uiRow2, unsigned int i_uiCol2 ) const
	{
		return m_vRowVectors[i_uiRow1][i_uiCol1] * m_vRowVectors[i_uiRow2][i_uiCol2] - m_vRowVectors[i_uiRow1][i_uiCol2] * m_vRowVectors[i_uiRow2][i_uiCol1];
	}

private:

	PCEVector3D m_vRowVectors[3];
};

