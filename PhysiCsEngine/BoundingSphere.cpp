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

void BoundingSphere::addSubSphere(float i_r, float i_x, float i_y, float i_z /* = 0 */)
{
	BoundingSphere tSphere(i_r,i_x,i_y,i_z);
	Shape::addSubShapeArray(&tSphere, 1);
}

const Collider* BoundingSphere::shapeCollidedWith(const PCEPoint &i_point) const
{

	float d2CenterPoint = (mCenter.mX - i_point.mX)*(mCenter.mX - i_point.mX) + (mCenter.mY - i_point.mY)*(mCenter.mY - i_point.mY) + (mCenter.mZ - i_point.mZ)*(mCenter.mZ - i_point.mZ);
	if (d2CenterPoint <= mRadius*mRadius)
	{
		for (unsigned int i = 0; i < getSubShapesCount(); ++i)
		{
			const Collider * collisionBound = static_cast<const Collider *>(mSubShapes[i])->shapeCollidedWith(i_point);
			if (collisionBound != nullptr)
			{
				return collisionBound;
			}
		}
		return this;
	}
	return nullptr;
}

const Collider* BoundingSphere::shapeCollidedWith(const Collider &i_shape) const
{
	if (typeid(i_shape) == typeid(BoundingSphere))
		return shapeCollidedWith(*static_cast<const BoundingSphere *>(&i_shape));
	return nullptr;
}

BoundingSphere::~BoundingSphere()
{
}



/************************************************************************/

//						PRIVATE METHODS									//
//						   operators									//
/************************************************************************/

BoundingSphere& BoundingSphere::operator=(const BoundingSphere& rvalue)
{
	if (this != &rvalue)
	{
		this->mCenter = rvalue.mCenter;
		this->mRadius = rvalue.mRadius;
		this->mSubShapes = rvalue.mSubShapes;
	}
	return *this;
}

bool BoundingSphere::operator==(const BoundingSphere& rvalue) const
{
	if (this == &rvalue)
	{
		return true;
	}

	if (&rvalue == nullptr && this != nullptr)
	{
		return false;
	}

	return (this->mCenter == rvalue.mCenter &&
			this->mRadius == rvalue.mRadius &&
			this->mSubShapes == rvalue.mSubShapes);
}

bool BoundingSphere::operator!=(const BoundingSphere& rvalue) const
{
	return !(this->operator==(rvalue));
}

bool BoundingSphere::operator==(const Shape& rvalue) const
{
	if (typeid(*this) != typeid(rvalue))
	{
		return false;
	}

	if (this == &rvalue)
	{
		return true;
	}
	
	if (&rvalue == nullptr)
	{
		return false;
	}


	const BoundingSphere * rvalueSphere = static_cast<const BoundingSphere*>(&rvalue);
	return *this == *rvalueSphere;
}

bool BoundingSphere::operator!=(const Shape& rvalue) const
{
	return !(*this != rvalue);
}

const Shape& BoundingSphere::operator=(const Shape& rvalue)
{
	assert(typeid(rvalue) == typeid(BoundingSphere));
	if (this != &rvalue)
	{
		operator=(*static_cast<const BoundingSphere*>(&rvalue));
	}
	return *this;
}


/************************************************************************/

//						PRIVATE METHODS									//
//						 other methods									//
/************************************************************************/

BoundingSphere::BoundingSphere(const BoundingSphere& i_boundingSphere)
	: Collider(i_boundingSphere.mDesc, i_boundingSphere.getSubShapesCapacity())
	, mCenter(i_boundingSphere.mCenter)
	, mRadius(i_boundingSphere.mRadius)
{
	mSubShapes = i_boundingSphere.mSubShapes;
}

const Collider* BoundingSphere::shapeCollidedWith(const BoundingSphere &i_sphere) const
{
	float d2CenterCenter = (mCenter.mX - i_sphere.mCenter.mX)*(mCenter.mX - i_sphere.mCenter.mX) + (mCenter.mY - i_sphere.mCenter.mY)*(mCenter.mY - i_sphere.mCenter.mY) + (mCenter.mZ - i_sphere.mCenter.mZ)*(mCenter.mZ - i_sphere.mCenter.mZ);
	d2CenterCenter = sqrtf(d2CenterCenter);
	if (d2CenterCenter <= mRadius + i_sphere.mRadius)
	{
		for (size_t i = 0; i < mSubShapes.size(); ++i)
		{
			const Collider *collisionBound = static_cast<const Collider*>(mSubShapes[i])->shapeCollidedWith(i_sphere);
			if (collisionBound != nullptr)
			{
				return collisionBound;
			}
		}
		return this;
	}
	return nullptr;
}