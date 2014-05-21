#ifndef PCE_BOUNGDING_SPHERE_H
#define PCE_BOUNGDING_SPHERE_H

#include "PCESystemApi.h"
#include "Shape.h"

typedef enum PCE_ERROR BOUNDING_SPHERE_ERROR;

class BoundingSphere : public Shape
{
public:

	BoundingSphere();
	BoundingSphere(const BoundingSphere& i_boundingSphere);

	/************************************************************************/
	/*
	Creates a sphere from radius and coordinates 2D or 3D of the center.
	*/
	/************************************************************************/
	BoundingSphere(float i_r, float i_x, float i_y, float i_z = 0);

	~BoundingSphere();

	/************************************************************************/
	/*
	Sets the number of sub spheres if not set yet, then allocates the sub spheres array.
	*/
	/************************************************************************/
	BOUNDING_SPHERE_ERROR setSubSpheresInitialCapacity(size_t i_numberOfSubSpheres);

	/************************************************************************/
	/*
	Adds a BoundingSphere as subSphere of this BoundingSphere.
	If sub spheres' array is full, adds some space copying the array in a new memory fragment.
	*/
	/************************************************************************/
	BOUNDING_SPHERE_ERROR addSubSphere(const BoundingSphere &i_subSphere);

	/************************************************************************/
	/*
	Creates a sub sphere from radius and coordinates 2D or 3D of the center.
	If sub spheres' array is full, adds some space copying the array in a new memory fragment. 
	*/
	/************************************************************************/
	BOUNDING_SPHERE_ERROR addSubSphere(float i_r, float i_x, float i_y, float i_z = 0);

	/************************************************************************/
	/*
	Adds a BoundingSphere's array as subSpheres of this BoundingSphere.
	If sub spheres' array is full, adds some space copying the array in a new memory fragment. 
	*/
	/************************************************************************/
	BOUNDING_SPHERE_ERROR addSubSphereArray(const BoundingSphere* i_subSphere, size_t i_numberOfSubSpheres);

	/************************************************************************/
	/* 
	Adds capacity to sub spheres' array, copying the old array in a newer bigger.
	*/
	/************************************************************************/
	BOUNDING_SPHERE_ERROR addCapacity(size_t i_value);

	inline const Point getCenter() const					{return mCenter;}
	inline void setCenter(const Point i_center)				{mCenter = i_center;}
	inline const float getRadius() const					{return mRadius;}
	inline void setRadius(const float i_radius)				{mRadius = i_radius;}
	inline const BoundingSphere* getSubSpheres() const		{return mpSubSpheres;}
	inline const unsigned int getSubSpheresCount() const	{return mCountSubSpheres;}

	/************************************************************************/
	/*
	Search if a point is in this sphere or in its sub spheres.
	Return the bounding sphere having the point.
	*/
	/************************************************************************/
	const Shape* shapeCollidedWith(const Point &i_point) const;

	const Shape* shapeCollidedWith(const Shape &i_shape) const;

private:
	Point mCenter;
	float mRadius;

	BoundingSphere *mpSubSpheres;
	size_t mSubSpheresCapacity;
	size_t mCountSubSpheres;
	

	/************************************************************************/
	/*
	BE CAREFULL: this operator do not deallocate nothing in the lValue!!
	*/
	/************************************************************************/
	BoundingSphere& operator=(const BoundingSphere& rvalue);

	bool operator==(const BoundingSphere& rvalue) const;
	bool operator!=(const BoundingSphere& rvalue) const;
	const BoundingSphere* shapeCollidedWith(const BoundingSphere &i_sphere) const;

};



#endif