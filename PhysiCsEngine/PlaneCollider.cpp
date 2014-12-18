#include "PlaneCollider.h"

#include "SphereCollider.h"

PlaneCollider::PlaneCollider( double i_a, double i_b, double i_c, double i_d )
	: Collider(PCEIds::DESC_PLANE)
	, m_a(i_a)
	, m_b(i_b)
	, m_c(i_c)
	, m_d(i_d)
{
}

PlaneCollider::PlaneCollider( PCEHVector3 i_oOrthogonalVector, PCEHVector3 i_oPoint )
	: Collider(PCEIds::DESC_PLANE)
	, m_a( i_oOrthogonalVector[0] )
	, m_b( i_oOrthogonalVector[1] )
	, m_c( i_oOrthogonalVector[2] )
	, m_d( - ( m_a * i_oPoint[0] + m_b * i_oPoint[1] + m_c * i_oPoint[2] ) )
{
}

PlaneCollider::PlaneCollider( PCEHVector3 i_oFirstVector, PCEHVector3 i_oSecondVector, PCEHVector3 i_oPoint )
	: Collider(PCEIds::DESC_PLANE)
{
	m_a = i_oFirstVector[1] * i_oSecondVector[2] - i_oFirstVector[2] * i_oSecondVector[1];
	m_b = i_oFirstVector[2] * i_oSecondVector[0] - i_oFirstVector[0] * i_oSecondVector[2];
	m_c = i_oFirstVector[0] * i_oSecondVector[1] - i_oFirstVector[1] * i_oSecondVector[0];
	m_d = - ( m_a * i_oPoint[0] + m_b * i_oPoint[1] + m_c * i_oPoint[2] );
}

const Collider* PlaneCollider::subShapeCollidedWith( const PCEHVector3& i_oPoint ) const
{
	if ( m_a * i_oPoint[0] + m_b * i_oPoint[1] + m_c * i_oPoint[2] == m_d )
	{
		return this;
	}

	return nullptr;
}

const Collider* PlaneCollider::subShapeCollidedWith( const Collider& i_oCollider ) const
{
	if (i_oCollider.getDescription() == PCEIds::DESC_BOUNDING_SPHERE )
		return subShapeCollidedWith(static_cast<const SphereCollider *>(&i_oCollider));
	else return i_oCollider.subShapeCollidedWith(*this);
}

const Collider* PlaneCollider::subShapeCollidedWith( const SphereCollider* i_pSphereCollider ) const
{
	double fSquareRadius = ( i_pSphereCollider->getRadius() * i_pSphereCollider->getRadius() );
	int iSquareRadius = *(int*)&fSquareRadius;

	const PCEHVector3& oSphereCenter = i_pSphereCollider->getCenter();
	double fSquareDistance = ( m_a*oSphereCenter[0] + m_b*oSphereCenter[1] + m_c*oSphereCenter[2] - m_d );
	fSquareDistance *= fSquareDistance;
	fSquareDistance /= ( m_a + m_b + m_c );
	int iSquareDistance = *(int*)&fSquareDistance;

	if ( iSquareDistance <= iSquareRadius )
	{
		return this;
	}

	return nullptr;
}
