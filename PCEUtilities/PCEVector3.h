#ifndef PCEVECTOR3_H
#define PCEVECTOR3_H

#include <cassert>
#include <cmath>
#include <cfloat>

class PCEVector3D
{

public:

	PCEVector3D()
	{
		m_pCoordinates[0] = 0;
		m_pCoordinates[1] = 0;
		m_pCoordinates[2] = 0;
	}

	PCEVector3D( const double& a, const double& b, const double& c )
	{
		m_pCoordinates[0] = a;
		m_pCoordinates[1] = b;
		m_pCoordinates[2] = c;
	}

	inline double& x()
	{
		return operator[](0);
	}

	inline const double& x() const
	{
		return operator[](0);
	}

	inline double& y()
	{
		return operator[](1);
	}

	inline const double& y() const
	{
		return operator[](1);
	}

	inline double& z()
	{
		return operator[](2);
	}

	inline const double& z() const
	{
		return operator[](2);
	}

	inline double& operator[]( unsigned int i_uiIndex )
	{
		assert( i_uiIndex >= 0 && i_uiIndex < 3 );
		return m_pCoordinates[i_uiIndex];
	}
	
	inline const double& operator[]( unsigned int i_uiIndex ) const
	{
		assert( i_uiIndex >= 0 && i_uiIndex < 3 );
		return m_pCoordinates[i_uiIndex];
	}

	inline bool operator==( const PCEVector3D& i_other ) const
	{
		return (i_other.x()==x() && i_other.y()==y() && i_other.z()==z());
	}

	inline bool operator!=( const PCEVector3D& i_other ) const
	{
		return !(*this == i_other);
	}

	inline PCEVector3D operator-() const
	{
		return PCEVector3D( -x(), -y(), -z() );
	}

	inline const PCEVector3D& operator=( const PCEVector3D& i_other )
	{
		x() = i_other.x();
		y() = i_other.y();
		z() = i_other.z();
		
		return *this;
	}

	inline const PCEVector3D& operator+=( const PCEVector3D& i_other )
	{
		x() += i_other.x();
		y() += i_other.y();
		z() += i_other.z();

		return *this;
	}

	inline const PCEVector3D& operator-=( const PCEVector3D& i_other )
	{
		x() -= i_other.x();
		y() -= i_other.y();
		z() -= i_other.z();

		return *this;
	}

	inline const PCEVector3D& operator*=( const double& i_rValue )
	{
		x() *= i_rValue;
		y() *= i_rValue;
		z() *= i_rValue;

		return *this;
	}

	inline const PCEVector3D& operator/=( const double& i_rValue )
	{
		double r = 1 / i_rValue;

		x() *= r;
		y() *= r;
		z() *= r;

		return *this;
	}

	inline PCEVector3D operator+( const PCEVector3D& v ) const
	{
		return PCEVector3D( x() + v.x(), y() + v.y(), z() + v.z() );
	}

	inline PCEVector3D operator-( const PCEVector3D& v ) const
	{
		return PCEVector3D( x() - v.x(), y() - v.y(), z() - v.z() );
	}

	inline PCEVector3D operator*( const double& s ) const
	{
		return PCEVector3D( x()*s, y()*s, z()*s );
	}

	inline const PCEVector3D operator/(double s) const
	{
		s = 1/s;

		return PCEVector3D( s*x(), s*y(), s*z() );
	}

	inline PCEVector3D Cross( const PCEVector3D& v ) const
	{

		return PCEVector3D( y()*v.z() - z()*v.y()
						  , z()*v.x() - x()*v.z()
						  , x()*v.y() - y()*v.x() 
						  );
	}

	inline double Dot( const PCEVector3D& v ) const
	{
		return x()*v.x() + y()*v.y() + z()*v.z();
	}

	inline double Module() const
	{
		return sqrt( Dot(*this) );
	}

	inline PCEVector3D Unit() const
	{
		return (*this) / Module();
	}

	void Normalize()
	{
		(*this) /= Module();
	}
/*
	TODO
	inline bool NearlyEqual( const PCEVector3D& v, const double e ) const
	{
		double rModule = Module();
		return (rModule + e) == 0 || (rModule - e) == 0;
	}
*/

private:

	double m_pCoordinates[3];
};

typedef PCEVector3D PCEPoint;

static const PCEPoint INVALID_POINT(DBL_MAX, DBL_MAX, DBL_MAX);

#endif // PCEVECTOR3_H