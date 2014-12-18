#ifndef PCE_SPHERE_COLLIDER_H
#define PCE_SPHERE_COLLIDER_H

#include "PCESystemApi.h"
#include "Shape.h"

class SphereCollider : public Collider
{
public:

	SphereCollider();
	SphereCollider(double i_r, double i_x, double i_y, double i_z = 0);

	const PCEPoint getCenter() const				{return mCenter;}
	void setCenter(const PCEPoint i_center)			{mCenter = i_center;}
	const double getRadius() const					{return mRadius;}
	void setRadius(const double i_radius)			{mRadius = i_radius;}

	const Collider* subShapeCollidedWith(const PCEHVector3& i_point) const;
	const Collider* subShapeCollidedWith(const Collider& i_collider) const;

private:
	PCEPoint mCenter;
	double mRadius;

	const Collider* SphereCollider::subShapeCollidedWith(const SphereCollider* i_sphere) const;
};



#endif