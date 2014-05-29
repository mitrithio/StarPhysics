#ifndef PCE_BOUNGDING_SPHERE_H
#define PCE_BOUNGDING_SPHERE_H

#include "PCESystemApi.h"
#include "Shape.h"

//typedef enum PCE_ERROR BOUNDING_SPHERE_ERROR;

class BoundingSphere : public Collider
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

	/************************************************************************/
	/*
	Creates a sub sphere from radius and coordinates 2D or 3D of the center.
	If sub spheres' array is full, adds some space copying the array in a new memory fragment. 
	*/
	/************************************************************************/
	void addSubSphere(float i_r, float i_x, float i_y, float i_z = 0);

	inline const PCEPoint getCenter() const					{return mCenter;}
	inline void setCenter(const PCEPoint i_center)				{mCenter = i_center;}
	inline const float getRadius() const					{return mRadius;}
	inline void setRadius(const float i_radius)				{mRadius = i_radius;}

	/************************************************************************/
	/*
	Search if a point is in this sphere or in its sub spheres.
	Return the bounding sphere having the point.
	*/
	/************************************************************************/
	const Collider* shapeCollidedWith(const PCEPoint &i_point) const;

	const Collider* shapeCollidedWith(const Collider &i_shape) const;

	bool operator==(const Shape& rvalue) const;
	bool operator!=(const Shape& rvalue) const;
	Shape& operator=(const Shape& rvalue);
	
	/************************************************************************/
	/*
	BE CAREFULL: this operator do not deallocate nothing in the lValue!!
	*/
	/************************************************************************/
	BoundingSphere& operator=(const BoundingSphere& rvalue);

	
	bool operator==(const BoundingSphere& rvalue) const;
	bool operator!=(const BoundingSphere& rvalue) const;

private:
	PCEPoint mCenter;
	float mRadius;

	
	const Collider* shapeCollidedWith(const BoundingSphere &i_sphere) const;
};



#endif