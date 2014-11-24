#include "Shape.h"

class SphereCollider;

class PlaneCollider : public Collider
{
public:

	PlaneCollider();
	PlaneCollider( float i_a, float i_b, float i_c, float i_d );
	PlaneCollider( PCEVector3 i_oOrthogonalVector, PCEVector3 i_oPoint );
	PlaneCollider( PCEVector3 i_oFirstVector, PCEVector3 i_oSecondVector, PCEVector3 i_oPoint );

	virtual const Collider* subShapeCollidedWith( const PCEVector3& i_oPoint ) const;

	virtual const Collider* subShapeCollidedWith( const Collider& i_oCollider ) const;

private:

	virtual const Collider* subShapeCollidedWith( const SphereCollider* i_pSphereCollider ) const;

private:

	float m_a;
	float m_b;
	float m_c;
	float m_d;
};