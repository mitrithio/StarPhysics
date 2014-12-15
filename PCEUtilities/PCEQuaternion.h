#ifndef PCEQUATERNION_H
#define PCEQUATERNION_H

class PCEQuaternion
{
public:

	PCEQuaternion( float a, float b, float c, float d );

	PCEQuaternion( const PCEQuaternion& i_other );

	~PCEQuaternion();

	PCEQuaternion& operator+=(const PCEQuaternion& i_other);

	PCEQuaternion operator+(const PCEQuaternion& i_other) const;

	PCEQuaternion& operator-=(const PCEQuaternion& i_other);

	PCEQuaternion operator-(const PCEQuaternion& i_other) const;

	PCEQuaternion& operator*=(const PCEQuaternion& i_other);

	PCEQuaternion operator*(const PCEQuaternion& i_other) const;

	PCEQuaternion& operator*=(float i_fScalar);

	PCEQuaternion operator*(float i_fScalar) const;

	PCEQuaternion& operator/=(float i_fScalar);

	PCEQuaternion operator/(float i_fScalar) const;

	float& operator[](unsigned int i_uiIndex) const;

	float Module();
	
	PCEQuaternion Normal();

private:

	float* m_mQuaternion;
};

#endif // PCEQUATERNION_H