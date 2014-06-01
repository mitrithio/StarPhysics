#ifndef PCE_BOUNGDING_SPHERE_H
#define PCE_BOUNGDING_SPHERE_H

#include "PCESystemApi.h"
#include "Shape.h"

//typedef enum PCE_ERROR BOUNDING_SPHERE_ERROR;

class BoundingSphere : public Collider
{
public:

	BoundingSphere();
//	BoundingSphere(const BoundingSphere& i_boundingSphere);

	/************************************************************************/
	/*
	Creates a sphere from radius and coordinates 2D or 3D of the center.
	*/
	/************************************************************************/
	BoundingSphere(float i_r, float i_x, float i_y, float i_z = 0);

	const PCEPoint getCenter() const					{return mCenter;}
	void setCenter(const PCEPoint i_center)				{mCenter = i_center;}
	const float getRadius() const					{return mRadius;}
	void setRadius(const float i_radius)				{mRadius = i_radius;}

	/************************************************************************/
	/*
	Search if a point is in this sphere or in its sub spheres.
	Return the bounding sphere having the point.
	*/
	/************************************************************************/
	const bool shapeCollidedWith(const PCEPoint &i_point,  const Collider * o_shapeCollided) const;

	const bool shapeCollidedWith(const Collider * i_shape, const Collider * o_shapeCollided) const;

	/*bool operator==(const Shape& rvalue) const;
	bool operator!=(const Shape& rvalue) const;
	Shape& operator=(const Shape& rvalue);*/
	
	/************************************************************************/
	/*
	BE CAREFULL: this operator do not deallocate nothing in the lValue!!
	*/
	/************************************************************************/
// 	BoundingSphere& operator=(const BoundingSphere& rvalue);
// 
// 	
// 	bool operator==(const BoundingSphere& rvalue) const;
// 	bool operator!=(const BoundingSphere& rvalue) const;

private:
	PCEPoint mCenter;
	float mRadius;

	
	const bool shapeCollidedWith(const BoundingSphere * i_shape, const Collider * o_shapeCollided) const;
};



#endif