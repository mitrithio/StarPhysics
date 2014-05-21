#include "PCESystemApi.h"
#include <math.h>
#include "BoundingSphere.h"
#include "ErrorDefinitions.h"


BoundingSphere::BoundingSphere(float i_r, float i_x, float i_y, float i_z)
	: Shape(ESD_BOUNDINGSPHERE, ESDT_COLLIDER) 
	, mRadius(i_r)
	, mCenter(i_x, i_y, i_z)
	, mpSubSpheres(nullptr)
	, mCountSubSpheres(0)
	, mSubSpheresCapacity(0)
{
}

BoundingSphere::BoundingSphere()
	: Shape(ESD_BOUNDINGSPHERE, ESDT_COLLIDER)
	, mCenter(0.0f,0.0f)
	, mRadius(0.0f)
	, mpSubSpheres(nullptr)
	, mSubSpheresCapacity(0)
	, mCountSubSpheres(0)
{}


BOUNDING_SPHERE_ERROR BoundingSphere::setSubSpheresInitialCapacity(size_t i_capacityOfSubSpheres)
{
	if (mSubSpheresCapacity != 0)
		return PCE_BS_CAPACITY;

	mSubSpheresCapacity = i_capacityOfSubSpheres;
	mpSubSpheres = new BoundingSphere[mSubSpheresCapacity];
	return PCE_OK;
}

BOUNDING_SPHERE_ERROR BoundingSphere::addSubSphere(const BoundingSphere &i_subSphere)
{
	return addSubSphereArray(&i_subSphere, 1);
}

BOUNDING_SPHERE_ERROR BoundingSphere::addSubSphere(float i_r, float i_x, float i_y, float i_z /* = 0 */)
{
	BoundingSphere tSphere(i_r,i_x,i_y,i_z);
	return addSubSphereArray(&tSphere, 1);
}

BOUNDING_SPHERE_ERROR BoundingSphere::addSubSphereArray(const BoundingSphere* i_subSphere, size_t i_numberOfSubSpheres)
{
	if (i_subSphere == nullptr)
		return PCE_BS_ADDSUBSPHERE;
	if (mCountSubSpheres + i_numberOfSubSpheres > mSubSpheresCapacity)
	{
		addCapacity(mCountSubSpheres + i_numberOfSubSpheres - mSubSpheresCapacity);
	}

	size_t i = mCountSubSpheres;
	size_t j = 0;
	for (; i < mCountSubSpheres + i_numberOfSubSpheres || j < i_numberOfSubSpheres; ++i, ++j)
	{ 
		mpSubSpheres[i] = i_subSphere[j];
	}
	if (i - mCountSubSpheres != j)
		return PCE_BS_ADDSUBSPHERE;
	mCountSubSpheres = mCountSubSpheres + i_numberOfSubSpheres;
	return PCE_OK;
}

BOUNDING_SPHERE_ERROR BoundingSphere::addCapacity(size_t i_value)
{
	if(i_value != 0)
	{
		mSubSpheresCapacity += i_value;
		BoundingSphere* tpSubSpheres = mpSubSpheres;

		mpSubSpheres = new BoundingSphere[mSubSpheresCapacity];
		for (unsigned int i = 0; i < mCountSubSpheres; ++i)
		{
			mpSubSpheres[i] = tpSubSpheres[i];
		}
		delete[] tpSubSpheres;
	}
	return PCE_OK;
}

const Shape* BoundingSphere::shapeCollidedWith(const Point &i_point) const
{
	float d2CenterPoint = (mCenter.mX - i_point.mX)*(mCenter.mX - i_point.mX) + (mCenter.mY - i_point.mY)*(mCenter.mY - i_point.mY) + (mCenter.mZ - i_point.mZ)*(mCenter.mZ - i_point.mZ);
	if (d2CenterPoint <= mRadius*mRadius)
	{
		const BoundingSphere *collisionBound = nullptr;
		for (unsigned int i = 0; i < mCountSubSpheres; ++i)
		{
			collisionBound = (BoundingSphere*)mpSubSpheres[i].shapeCollidedWith(i_point);
			if (collisionBound != nullptr)
			{
				return collisionBound;
			}
		}
		return this;
	}
	return nullptr;
}

const Shape* BoundingSphere::shapeCollidedWith(const Shape &i_shape) const
{
	return shapeCollidedWith((BoundingSphere &) i_shape);
}


BoundingSphere::~BoundingSphere()
{
	delete[] mpSubSpheres;
}



/************************************************************************/

//						PRIVATE METHODS									//
//						   operators									//
/************************************************************************/

BoundingSphere& BoundingSphere::operator=(const BoundingSphere& rvalue)
{
	if (*this != rvalue)
	{
		this->mCenter = rvalue.mCenter;
		this->mRadius = rvalue.mRadius;
		if (rvalue.mSubSpheresCapacity == 0)
		{
			this->mpSubSpheres = nullptr;
			this->mSubSpheresCapacity = 0;
			this->mCountSubSpheres = 0;
		}
		else
		{
			this->mSubSpheresCapacity = rvalue.mSubSpheresCapacity;
			this->mCountSubSpheres = rvalue.mCountSubSpheres;
			*(this->mpSubSpheres) = *(rvalue.mpSubSpheres);
		}
	}
	return *this;
}

bool BoundingSphere::operator==(const BoundingSphere& rvalue) const
{
	if (this == &rvalue)
	{
		return true;
	}
	
	return (this->mCenter == rvalue.mCenter &&
			this->mRadius == rvalue.mRadius &&
			this->mSubSpheresCapacity == rvalue.mSubSpheresCapacity &&
			this->mCountSubSpheres == rvalue.mCountSubSpheres &&
			*(this->mpSubSpheres) == *(rvalue.mpSubSpheres));
}

bool BoundingSphere::operator!=(const BoundingSphere& rvalue) const
{
	return !(this == &rvalue);
}


/************************************************************************/

//						PRIVATE METHODS									//
//						 other methods									//
/************************************************************************/

BoundingSphere::BoundingSphere(const BoundingSphere& i_boundingSphere)
	: Shape(*i_boundingSphere.mDesc)
	, mCenter(i_boundingSphere.mCenter)
	, mRadius(i_boundingSphere.mRadius)
	, mSubSpheresCapacity(i_boundingSphere.mSubSpheresCapacity)
	, mCountSubSpheres(i_boundingSphere.mCountSubSpheres)
{
	if(mSubSpheresCapacity != 0)
	{	
		mpSubSpheres = new BoundingSphere[mSubSpheresCapacity];
		for (size_t i = 0; i < mCountSubSpheres; ++i)
		{
			mpSubSpheres[i] = i_boundingSphere.mpSubSpheres[i];
		}
	}
	else
	{
		mpSubSpheres = nullptr;
	}
}

const BoundingSphere* BoundingSphere::shapeCollidedWith(const BoundingSphere &i_sphere) const
{
	float d2CenterCenter = (mCenter.mX - i_sphere.mCenter.mX)*(mCenter.mX - i_sphere.mCenter.mX) + (mCenter.mY - i_sphere.mCenter.mY)*(mCenter.mY - i_sphere.mCenter.mY) + (mCenter.mZ - i_sphere.mCenter.mZ)*(mCenter.mZ - i_sphere.mCenter.mZ);
	d2CenterCenter = sqrtf(d2CenterCenter);
	if (d2CenterCenter <= mRadius + i_sphere.mRadius)
	{
		const BoundingSphere *collisionBound = nullptr;
		for (unsigned int i = 0; i < mCountSubSpheres; ++i)
		{
			collisionBound = mpSubSpheres[i].shapeCollidedWith(i_sphere);
			if (collisionBound != nullptr)
			{
				return collisionBound;
			}
		}
		return this;
	}
	return nullptr;
}