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

	PCEVector3D(const float& a, const float& b, const float& c)
	{
		m_pCoordinates[0] = a;
		m_pCoordinates[1] = b;
		m_pCoordinates[2] = c;
	}

	inline float& x()
	{
		return operator[](0);
	}

	inline const float& x() const
	{
		return operator[](0);
	}

	inline float& y()
	{
		return operator[](1);
	}

	inline const float& y() const
	{
		return operator[](1);
	}

	inline float& z()
	{
		return operator[](2);
	}

	inline const float& z() const
	{
		return operator[](2);
	}

	inline float& operator[]( unsigned int i_uiIndex)
	{
		assert( i_uiIndex >= 0 && i_uiIndex < 3);
		return m_pCoordinates[i_uiIndex];
	}
	
	inline const float& operator[]( unsigned int i_uiIndex) const
	{
		assert( i_uiIndex >= 0 && i_uiIndex < 3);
		return m_pCoordinates[i_uiIndex];
	}

	inline bool operator==(const PCEVector3D& i_other) const
	{
		return (i_other.x()==x() && i_other.y()==y() && i_other.z()==z());
	}

	inline bool operator!=(const PCEVector3D& i_other) const
	{
		return !(*this == i_other);
	}

	inline PCEVector3D operator-() const
	{
		return PCEVector3D( -x(), -y(), -z());
	}

	inline const PCEVector3D& operator=(const PCEVector3D& i_other)
	{
		x() = i_other.x();
		y() = i_other.y();
		z() = i_other.z();
		
		return *this;
	}

	inline const PCEVector3D& operator+=(const PCEVector3D& i_other)
	{
		x() += i_other.x();
		y() += i_other.y();
		z() += i_other.z();

		return *this;
	}

	inline const PCEVector3D& operator-=(const PCEVector3D& i_other)
	{
		x() -= i_other.x();
		y() -= i_other.y();
		z() -= i_other.z();

		return *this;
	}

	inline const PCEVector3D& operator*=(const float& i_value)
	{
		x() *= i_value;
		y() *= i_value;
		z() *= i_value;

		return *this;
	}

	inline const PCEVector3D& operator/=(const float& i_value)
	{
		float r = 1 / i_value;

		*this *= r;

		return *this;
	}

	inline PCEVector3D operator+(const PCEVector3D& i_other) const
	{
		PCEVector3D tmp = *this;
		tmp += i_other;
		return tmp;
	}

	inline PCEVector3D operator-(const PCEVector3D& i_other) const
	{
		PCEVector3D tmp = *this;
		tmp -= i_other;
		return tmp;
	}

	inline PCEVector3D operator*(const float& i_value) const
	{
		PCEVector3D tmp = *this;
		tmp *= i_value;
		return tmp;
	}

	inline PCEVector3D operator/(const float& i_value) const
	{
		PCEVector3D tmp = *this;
		tmp /= i_value;
		return tmp;
	}

	inline PCEVector3D Cross(const PCEVector3D& i_other) const
	{

		return PCEVector3D( y()*i_other.z() - z()*i_other.y()
						  , z()*i_other.x() - x()*i_other.z()
						  , x()*i_other.y() - y()*i_other.x() 
						 );
	}

	inline float Dot(const PCEVector3D& i_other) const
	{
		return x()*i_other.x() + y()*i_other.y() + z()*i_other.z();
	}

	inline float Module() const
	{
		return sqrt( Dot(*this));
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
	inline bool NearlyEqual(const PCEVector3D& i_other, const float e) const
	{
		float rModule = Module();
		return (rModule + e) == 0 || (rModule - e) == 0;
	}
*/

private:

	float m_pCoordinates[3];
};

class PCEVector2D
{

public:

	PCEVector2D()
	{
		m_pCoordinates[0] = 0;
		m_pCoordinates[1] = 0;
	}

	PCEVector2D(const float& a, const float& b)
	{
		m_pCoordinates[0] = a;
		m_pCoordinates[1] = b;
	}

	inline float& x()
	{
		return operator[](0);
	}

	inline const float& x() const
	{
		return operator[](0);
	}

	inline float& y()
	{
		return operator[](1);
	}

	inline const float& y() const
	{
		return operator[](1);
	}

	inline float& operator[]( unsigned int i_uiIndex)
	{
		return m_pCoordinates[i_uiIndex];
	}
	
	inline const float& operator[]( unsigned int i_uiIndex) const
	{
		return m_pCoordinates[i_uiIndex];
	}

	inline bool operator==(const PCEVector2D& i_other) const
	{
		return (i_other.x()==x() && i_other.y()==y());
	}

	inline bool operator!=(const PCEVector2D& i_other) const
	{
		return !(*this == i_other);
	}

	inline PCEVector2D operator-() const
	{
		return PCEVector2D(-x(), -y());
	}

	inline const PCEVector2D& operator=(const PCEVector2D& i_other)
	{
		if (this != &i_other)
		{
			x() = i_other.x();
			y() = i_other.y();
		}
		
		return *this;
	}

	inline const PCEVector2D& operator+=(const PCEVector2D& i_other)
	{
		x() += i_other.x();
		y() += i_other.y();

		return *this;
	}

	inline const PCEVector2D& operator-=(const PCEVector2D& i_other)
	{
		x() -= i_other.x();
		y() -= i_other.y();

		return *this;
	}

	inline const PCEVector2D& operator*=(const float& i_rValue)
	{
		x() *= i_rValue;
		y() *= i_rValue;

		return *this;
	}

	inline const PCEVector2D& operator/=(const float& i_rValue)
	{
		float r = 1 / i_rValue;

		x() *= r;
		y() *= r;

		return *this;
	}

	inline PCEVector2D operator+(const PCEVector2D& i_other) const
	{
		PCEVector2D tmp = *this;
		tmp += i_other;
		return tmp;
	}

	inline PCEVector2D operator-(const PCEVector2D& i_other) const
	{
		PCEVector2D tmp = *this;
		tmp -= i_other;
		return tmp;
	}

	inline PCEVector2D operator*(const float& i_value) const
	{
		PCEVector2D tmp = *this;
		tmp *= i_value;
		return tmp;
	}

	inline PCEVector2D operator/(const float& i_value) const
	{
		PCEVector2D tmp = *this;
		tmp /= i_value;
		return tmp;
	}

	inline float Cross(const PCEVector2D& i_other) const
	{
		return x()*i_other.y() - y()*i_other.x();

	}

	inline float Dot(const PCEVector2D& i_other) const
	{
		return x()*i_other.x() + y()*i_other.y();
	}

	inline float Module() const
	{
		return sqrt( Dot(*this));
	}

	inline PCEVector2D Unit() const
	{
		return (*this) / Module();
	}

	void Normalize()
	{
		(*this) /= Module();
	}
/*
	TODO
	inline bool NearlyEqual(const PCEVector3D& i_other, const float e) const
	{
		float rModule = Module();
		return (rModule + e) == 0 || (rModule - e) == 0;
	}
*/

private:

	float m_pCoordinates[2];
};

typedef PCEVector3D PCEPoint3D;
typedef PCEVector2D PCEPoint2D;

static const PCEPoint3D INVALID_POINT(FLT_MAX, FLT_MAX, FLT_MAX);
static const PCEPoint2D INVALID_POINT(FLT_MAX, FLT_MAX);

#endif // PCEVECTOR3_H