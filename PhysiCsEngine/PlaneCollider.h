#include "Shape.h"

class SphereCollider;

class PlaneCollider : public Collider
{
public:

	PlaneCollider();
	PlaneCollider( double i_a, double i_b, double i_c, double i_d );
	PlaneCollider( PCEVector3D i_oOrthogonalVector, PCEVector3D i_oPoint );
	PlaneCollider( PCEVector3D i_oFirstVector, PCEVector3D i_oSecondVector, PCEVector3D i_oPoint );

	virtual const Collider* CheckCollisionWith( const PCEVector3D& i_oPoint ) const;

	virtual const Collider* CheckCollisionWith( const Collider& i_oCollider ) const;

private:

	virtual const Collider* CheckCollisionWith( const SphereCollider* i_pSphereCollider ) const;

private:

	double m_a;
	double m_b;
	double m_c;
	double m_d;
};