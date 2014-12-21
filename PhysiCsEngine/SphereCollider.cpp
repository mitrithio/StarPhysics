#include "PCESystemApi.h"
#include <typeinfo>
#include <cmath>
#include "SphereCollider.h"
#include "ErrorDefinitions.h"


SphereCollider::SphereCollider(double i_r, double i_x, double i_y, double i_z)
	: Collider(PCEIds::DESC_BOUNDING_SPHERE) 
	, mRadius(i_r)
{
	mCenter[0] = i_x;
	mCenter[1] = i_y;
	mCenter[2] = i_z;
}

SphereCollider::SphereCollider()
	: Collider(PCEIds::DESC_BOUNDING_SPHERE)
	, mRadius(0.0f)
{
	mCenter[0] = 0.0f;
	mCenter[1] = 0.0f;
	mCenter[2] = 0.0f;
}

const Collider* SphereCollider::CheckCollisionWith(const PCEPoint &i_point) const
{

	double fDistanceFromPoint = pow(mCenter[0] - i_point[0],2) + pow(mCenter[1] - i_point[1],2) + pow(mCenter[2] - i_point[2],2);
	int iDistanceFromPoint = *(int*)&fDistanceFromPoint;

	double fPowRadius = pow(mRadius,2);
	int iPowRadius = *(int*)&fPowRadius;

	const Collider * pCollider = nullptr;
	if (iDistanceFromPoint <= iPowRadius)
	{
		bool bColliderFound = false;
		for (unsigned int i = 0; !bColliderFound && i < m_subShapes.size(); ++i)
		{
			if (m_subShapes[i]->getDescriptionType() == PCEIds::TYPE_COLLIDER)
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

const Collider* SphereCollider::CheckCollisionWith(const Collider& i_collider) const
{
	if (i_collider.getDescription() == PCEIds::DESC_BOUNDING_SPHERE)
		return CheckCollisionWith(static_cast<const SphereCollider *>(&i_collider));
	else return i_collider.CheckCollisionWith(*this);
}

const Collider* SphereCollider::CheckCollisionWith(const SphereCollider* i_sphere) const
{
	double fSquareDistanceFromOtherCollider = pow(mCenter[0] - i_sphere->mCenter[0],2) + pow(mCenter[1] - i_sphere->mCenter[1],2) + pow(mCenter[2] - i_sphere->mCenter[2],2);
	int iSquareDistanceFromOtherCollider = *(int*)&fSquareDistanceFromOtherCollider;

	double fSquareRadiusDistance = pow( mRadius + i_sphere->mRadius, 2 );
	int iSquareRadiusDistance = *(int*)&fSquareRadiusDistance;

	const Collider * pCollider = nullptr;
	if (iSquareDistanceFromOtherCollider <= iSquareRadiusDistance)
	{
		bool bColliderFound = false;
		for (uint32_t uiIndex = 0; !bColliderFound && uiIndex < m_subShapes.size(); ++uiIndex)
		{
			if (m_subShapes[uiIndex]->getDescriptionType() == PCEIds::TYPE_COLLIDER)
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