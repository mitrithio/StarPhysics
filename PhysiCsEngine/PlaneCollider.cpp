#include "PlaneCollider.h"

#include "SphereCollider.h"

PlaneCollider::PlaneCollider( float i_a, float i_b, float i_c, float i_d )
	: Collider(ESD_PLANE)
	, m_a(i_a)
	, m_b(i_b)
	, m_c(i_c)
	, m_d(i_d)
{
}

PlaneCollider::PlaneCollider( PCEVector3 i_oOrthogonalVector, PCEVector3 i_oPoint )
	: Collider(ESD_PLANE)
	, m_a( i_oOrthogonalVector.mX )
	, m_b( i_oOrthogonalVector.mY )
	, m_c( i_oOrthogonalVector.mZ )
	, m_d( - ( m_a * i_oPoint.mX + m_b * i_oPoint.mY + m_c * i_oPoint.mZ ) )
{
}

PlaneCollider::PlaneCollider( PCEVector3 i_oFirstVector, PCEVector3 i_oSecondVector, PCEVector3 i_oPoint )
	: Collider(ESD_PLANE)
{
	m_a = i_oFirstVector.mY * i_oSecondVector.mZ - i_oFirstVector.mZ * i_oSecondVector.mY;
	m_b = i_oFirstVector.mZ * i_oSecondVector.mX - i_oFirstVector.mX * i_oSecondVector.mZ;
	m_c = i_oFirstVector.mX * i_oSecondVector.mY - i_oFirstVector.mY * i_oSecondVector.mX;
	m_d = - ( m_a * i_oPoint.mX + m_b * i_oPoint.mY + m_c * i_oPoint.mZ );
}

const Collider* PlaneCollider::subShapeCollidedWith( const PCEVector3& i_oPoint ) const
{
	if ( m_a * i_oPoint.mX + m_b * i_oPoint.mY + m_c * i_oPoint.mZ == m_d )
	{
		return this;
	}

	return nullptr;
}

const Collider* PlaneCollider::subShapeCollidedWith( const Collider& i_oCollider ) const
{
	if (i_oCollider.getDescription() == ESD_BOUNDINGSPHERE)
		return subShapeCollidedWith(static_cast<const SphereCollider *>(&i_oCollider));
	else return i_oCollider.subShapeCollidedWith(*this);
}

const Collider* PlaneCollider::subShapeCollidedWith( const SphereCollider* i_pSphereCollider ) const
{
	float fSquareRadius = ( i_pSphereCollider->getRadius() * i_pSphereCollider->getRadius() );
	int iSquareRadius = *(int*)&fSquareRadius;

	const PCEVector3& oSphereCenter = i_pSphereCollider->getCenter();
	float fSquareDistance = ( m_a*oSphereCenter.mX + m_b*oSphereCenter.mY + m_c*oSphereCenter.mZ - m_d );
	fSquareDistance *= fSquareDistance;
	fSquareDistance /= ( m_a + m_b + m_c );
	int iSquareDistance = *(int*)&fSquareDistance;

	if ( iSquareDistance <= iSquareRadius )
	{
		return this;
	}

	return nullptr;
}
