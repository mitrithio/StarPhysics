#include "Shape.h"

class SphereCollider;

class PlaneCollider : public Collider
{
public:

	PlaneCollider();
	PlaneCollider( double i_a, double i_b, double i_c, double i_d );
	PlaneCollider( PCEHVector3 i_oOrthogonalVector, PCEHVector3 i_oPoint );
	PlaneCollider( PCEHVector3 i_oFirstVector, PCEHVector3 i_oSecondVector, PCEHVector3 i_oPoint );

	virtual const Collider* subShapeCollidedWith( const PCEHVector3& i_oPoint ) const;

	virtual const Collider* subShapeCollidedWith( const Collider& i_oCollider ) const;

private:

	virtual const Collider* subShapeCollidedWith( const SphereCollider* i_pSphereCollider ) const;

private:

	double m_a;
	double m_b;
	double m_c;
	double m_d;
};