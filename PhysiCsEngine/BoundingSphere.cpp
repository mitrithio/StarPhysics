#include "PCESystemApi.h"
#include <typeinfo>
#include <math.h>
#include "BoundingSphere.h"
#include "ErrorDefinitions.h"


BoundingSphere::BoundingSphere(float i_r, float i_x, float i_y, float i_z)
	: Collider(ESD_BOUNDINGSPHERE) 
	, mRadius(i_r)
	, mCenter(i_x, i_y, i_z)
{
}

BoundingSphere::BoundingSphere()
	: Collider(ESD_BOUNDINGSPHERE)
	, mCenter(0.0f,0.0f)
	, mRadius(0.0f)
{}

const Collider* BoundingSphere::shapeCollidedWith(const PCEPoint &i_point) const
{

	float d2CenterPoint = (mCenter.mX - i_point.mX)*(mCenter.mX - i_point.mX) + (mCenter.mY - i_point.mY)*(mCenter.mY - i_point.mY) + (mCenter.mZ - i_point.mZ)*(mCenter.mZ - i_point.mZ);
	if (d2CenterPoint <= mRadius*mRadius)
	{
		for (unsigned int i = 0; i < m_subShapes.size(); ++i)
		{
			const Collider * collisionBound = static_cast<const Collider *>(m_subShapes[i])->shapeCollidedWith(i_point);
			if (collisionBound != nullptr)
			{
				return collisionBound;
			}
		}
		return this;
	}
	return nullptr;
}

const bool BoundingSphere::shapeCollidedWith(const Collider * i_shape, const Collider * o_shapeCollided) const
{
	if (dynamic_cast<const BoundingSphere *>(i_shape))
		return shapeCollidedWith(static_cast<const BoundingSphere *>(i_shape), o_shapeCollided);
	return false;
}

// BoundingSphere& BoundingSphere::operator=(const BoundingSphere& rvalue)
// {
// 	if (!(*this == rvalue))
// 	{
// 		this->mDesc = rvalue.mDesc;
// 		this->mType = rvalue.mType;
// 		this->mCenter = rvalue.mCenter;
// 		this->mRadius = rvalue.mRadius;
// 		this->m_subShapes = rvalue.m_subShapes;
// 	}
// 	return *this;
// }
// 
// bool BoundingSphere::operator==(const BoundingSphere& rvalue) const
// {
// 	return mDesc == rvalue.mDesc		&&
// 		   mType == rvalue.mType		&&
// 		   mCenter == rvalue.mCenter	&&
// 		   mRadius == rvalue.mRadius	&&
// 		   m_subShapes == rvalue.m_subShapes;
// }
// 
// bool BoundingSphere::operator!=(const BoundingSphere& rvalue) const
// {
// 	return !(*this == rvalue);
// }
// 
// bool BoundingSphere::operator==(const Shape& rvalue) const
// {
// 	assert(dynamic_cast<const BoundingSphere *>(&rvalue));
// 	return *this == *static_cast<const BoundingSphere *>(&rvalue);
// }
// 
// bool BoundingSphere::operator!=(const Shape& rvalue) const
// {
// 	return !(*this != rvalue);
// }
// 
// Shape& BoundingSphere::operator=(const Shape& rvalue)
// {
// 	assert(dynamic_cast<const BoundingSphere *>(&rvalue));
// 	return operator=(*static_cast<const BoundingSphere *>(&rvalue));
// }
// 
// BoundingSphere::BoundingSphere(const BoundingSphere& i_boundingSphere)
// 	: Collider(i_boundingSphere.mDesc)
// 	, mCenter(i_boundingSphere.mCenter)
// 	, mRadius(i_boundingSphere.mRadius)
// {
// 	m_subShapes = i_boundingSphere.m_subShapes;
// }

const bool BoundingSphere::shapeCollidedWith(const BoundingSphere * i_sphere, const Collider * o_shapeCollided) const
{
	float dCenterCenter = sqrtf((mCenter.mX - i_sphere->mCenter.mX)*(mCenter.mX - i_sphere->mCenter.mX) + (mCenter.mY - i_sphere->mCenter.mY)*(mCenter.mY - i_sphere->mCenter.mY) + (mCenter.mZ - i_sphere->mCenter.mZ)*(mCenter.mZ - i_sphere->mCenter.mZ));

	int diffCenterCenter = *(int*)&dCenterCenter;

	float sRadiusRadius = mRadius + i_sphere->mRadius;
	int sumRadiusRadius = *(int*)&sRadiusRadius;

	const Collider * colliderFound = nullptr;
	bool founded = false;
	if (diffCenterCenter <= sumRadiusRadius)
	{
		for (int index = 0; !founded && index < m_subShapes.size(); ++index)
		{
			founded = static_cast<const Collider*>(m_subShapes[index])->shapeCollidedWith(i_sphere, colliderFound);
		}
		if (colliderFound == nullptr)
		{
			colliderFound = this;
		}
	}
	o_shapeCollided = colliderFound;
	return founded;
}