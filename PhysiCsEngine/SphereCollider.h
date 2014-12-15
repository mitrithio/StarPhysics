#ifndef PCE_SPHERE_COLLIDER_H
#define PCE_SPHERE_COLLIDER_H

#include "PCESystemApi.h"
#include "Shape.h"

class SphereCollider : public Collider
{
public:

	SphereCollider();
	SphereCollider(float i_r, float i_x, float i_y, float i_z = 0);

	const PCEPoint getCenter() const				{return mCenter;}
	void setCenter(const PCEPoint i_center)			{mCenter = i_center;}
	const float getRadius() const					{return mRadius;}
	void setRadius(const float i_radius)			{mRadius = i_radius;}

	const Collider* subShapeCollidedWith(const PCEHVector3& i_point) const;
	const Collider* subShapeCollidedWith(const Collider& i_collider) const;

private:
	PCEPoint mCenter;
	float mRadius;

	const Collider* SphereCollider::subShapeCollidedWith(const SphereCollider* i_sphere) const;
};



#endif