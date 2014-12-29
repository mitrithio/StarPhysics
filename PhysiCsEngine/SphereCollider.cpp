#include "PCESystemApi.h"
#include <typeinfo>
#include <cmath>
#include "SphereCollider.h"
#include "ErrorDefinitions.h"


Sphere3DCollider::Sphere3DCollider(float i_r, float i_x, float i_y, float i_z)
	: Collider(PCEIds::DESC_BOUNDING_SPHERE) 
	, mRadius(i_r)
{
	mCenter[0] = i_x;
	mCenter[1] = i_y;
	mCenter[2] = i_z;
}

Sphere3DCollider::Sphere3DCollider()
	: Collider(PCEIds::DESC_BOUNDING_SPHERE)
	, mRadius(0.0f)
{
	mCenter[0] = 0.0f;
	mCenter[1] = 0.0f;
	mCenter[2] = 0.0f;
}

const Collider* Sphere3DCollider::CheckCollisionWith(const PCEPoint3D &i_point) const
{

	float fDistanceFromPoint = pow(mCenter[0] - i_point[0],2) + pow(mCenter[1] - i_point[1],2) + pow(mCenter[2] - i_point[2],2);
	int iDistanceFromPoint = *(int*)&fDistanceFromPoint;

	float fPowRadius = pow(mRadius,2);
	int iPowRadius = *(int*)&fPowRadius;

	const Collider * pCollider = nullptr;
	if (iDistanceFromPoint <= iPowRadius)
	{
		bool bColliderFound = false;
		for (unsigned int i = 0; !bColliderFound && i < m_vSubShapes.size(); ++i)
		{
			if (m_vSubShapes[i]->GetType() == PCEIds::TYPE_COLLIDER)
			{
				pCollider = static_cast<const Collider *>(m_vSubShapes[i])->subShapeCollidedWith(i_point);
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

const Collider* Sphere3DCollider::CheckCollisionWith(const Collider& i_collider) const
{
	if (i_collider.GetDescription() == PCEIds::DESC_BOUNDING_SPHERE)
		return CheckCollisionWith(static_cast<const Sphere3DCollider *>(&i_collider));
	else return i_collider.CheckCollisionWith(*this);
}

const Collider* Sphere3DCollider::CheckCollisionWith(const Sphere3DCollider* i_sphere) const
{
	float fSquareDistanceFromOtherCollider = pow(mCenter[0] - i_sphere->mCenter[0],2) + pow(mCenter[1] - i_sphere->mCenter[1],2) + pow(mCenter[2] - i_sphere->mCenter[2],2);
	int iSquareDistanceFromOtherCollider = *(int*)&fSquareDistanceFromOtherCollider;

	float fSquareRadiusDistance = pow( mRadius + i_sphere->mRadius, 2 );
	int iSquareRadiusDistance = *(int*)&fSquareRadiusDistance;

	const Collider * pCollider = nullptr;
	if (iSquareDistanceFromOtherCollider <= iSquareRadiusDistance)
	{
		bool bColliderFound = false;
		for (uint32_t uiIndex = 0; !bColliderFound && uiIndex < m_vSubShapes.size(); ++uiIndex)
		{
			if (m_vSubShapes[uiIndex]->GetType() == PCEIds::TYPE_COLLIDER)
			{
				pCollider = static_cast<const Collider*>(m_vSubShapes[uiIndex])->subShapeCollidedWith(*i_sphere);
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