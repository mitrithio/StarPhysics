#include "PCESystemApi.h"
#include <typeinfo>
#include <math.h>
#include "SphereCollider.h"
#include "ErrorDefinitions.h"


SphereCollider::SphereCollider(float i_r, float i_x, float i_y, float i_z)
	: Collider(ESD_BOUNDINGSPHERE) 
	, mRadius(i_r)
	, mCenter(i_x, i_y, i_z)
{
}

SphereCollider::SphereCollider()
	: Collider(ESD_BOUNDINGSPHERE)
	, mCenter(0.0f,0.0f,0.0f)
	, mRadius(0.0f)
{}

const Collider* SphereCollider::subShapeCollidedWith(const PCEVector3 &i_point) const
{

	float fDistanceFromPoint = (mCenter.mX - i_point.mX)*(mCenter.mX - i_point.mX) + (mCenter.mY - i_point.mY)*(mCenter.mY - i_point.mY) + (mCenter.mZ - i_point.mZ)*(mCenter.mZ - i_point.mZ);
	int iDistanceFromPoint = *(int*)&fDistanceFromPoint;

	float fPowRadius = mRadius*mRadius;
	int iPowRadius = *(int*)&fPowRadius;

	const Collider * pCollider = nullptr;
	if (iDistanceFromPoint <= iPowRadius)
	{
		bool bColliderFound = false;
		for (unsigned int i = 0; !bColliderFound && i < m_subShapes.size(); ++i)
		{
			if (m_subShapes[i]->getDescriptionType() == ESDT_COLLIDER)
			{
				pCollider = static_cast<const Collider *>(m_subShapes[i])->subShapeCollidedWith(i_point);
				bColliderFound = (pCollider != nullptr);
			}
		}
		if (bColliderFound == false)
		{
			pCollider = this;
		}
	}
	return pCollider;
}

const Collider* SphereCollider::subShapeCollidedWith(const Collider& i_collider) const
{
	if (i_collider.getDescription() == ESD_BOUNDINGSPHERE)
		return subShapeCollidedWith(static_cast<const SphereCollider *>(&i_collider));
	else return i_collider.subShapeCollidedWith(*this);
}

const Collider* SphereCollider::subShapeCollidedWith(const SphereCollider* i_sphere) const
{
	float fSquareDistanceFromOtherCollider = (mCenter.mX - i_sphere->mCenter.mX)*(mCenter.mX - i_sphere->mCenter.mX) + (mCenter.mY - i_sphere->mCenter.mY)*(mCenter.mY - i_sphere->mCenter.mY) + (mCenter.mZ - i_sphere->mCenter.mZ)*(mCenter.mZ - i_sphere->mCenter.mZ);
	int iSquareDistanceFromOtherCollider = *(int*)&fSquareDistanceFromOtherCollider;

	float fSquareRadiusDistance = ( mRadius + i_sphere->mRadius ) * ( mRadius + i_sphere->mRadius );
	int iSquareRadiusDistance = *(int*)&fSquareRadiusDistance;

	const Collider * pCollider = nullptr;
	if (iSquareDistanceFromOtherCollider <= iSquareRadiusDistance)
	{
		bool bColliderFound = false;
		for (uint32_t uiIndex = 0; !bColliderFound && uiIndex < m_subShapes.size(); ++uiIndex)
		{
			if (m_subShapes[uiIndex]->getDescriptionType() == ESDT_COLLIDER)
			{
				pCollider = static_cast<const Collider*>(m_subShapes[uiIndex])->subShapeCollidedWith(*i_sphere);
				bColliderFound = (pCollider != nullptr);
			}
		}
		if (bColliderFound == false)
		{
			pCollider = this;
		}
	}
	return pCollider;
}