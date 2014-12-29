#ifndef PCE_SPHERE_COLLIDER_H
#define PCE_SPHERE_COLLIDER_H

#include "PCESystemApi.h"
#include "Shape.h"

class Sphere3DCollider : public Collider
{
public:

	Sphere3DCollider();
	Sphere3DCollider(float i_r, float i_x, float i_y, float i_z);
	Sphere3DCollider(const PCEPoint3D& i_oCenter, float i_rRadius)

	const PCEPoint3D getCenter() const				{return mCenter;}
	void setCenter(const PCEPoint3D i_center)			{mCenter = i_center;}
	const float getRadius() const					{return mRadius;}
	void setRadius(const float i_radius)			{mRadius = i_radius;}

	float CheckCollisionWith(const PCEVector3D& i_point) const;
	float CheckCollisionWith(const Collider& i_collider) const;

private:
	PCEPoint3D mCenter;
	float mRadius;

	const Collider* Sphere3DCollider::CheckCollisionWith(const Sphere3DCollider* i_sphere) const;
};



#endif