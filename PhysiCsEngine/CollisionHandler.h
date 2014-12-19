#ifndef COLLISIONHANDLER_H 
#define COLLISIONHANDLER_H

#include "../PCEUtilities/PCEUtilities.h"

class RigidBody;
class Shape;


class CollisionHandler
{
public:

	struct Config
	{
		PCEVector3D m_vGravity;
	};

	struct ZeroGravity : Config
	{
		ZeroGravity()
		{
			m_vGravity = 0;
		}
	};

	struct Gravity2D : Config
	{
		Gravity2D()
		{
			m_vGravity[0] = 0;
			m_vGravity[1] = 9.81;
			m_vGravity[2] = 0;
		}
	};

	struct ReverseGravity2D : Config
	{
		ReverseGravity2D()
		{
			m_vGravity[0] = 0;
			m_vGravity[1] = -9.81;
			m_vGravity[2] = 0;
		}
	};

	struct Gravity3D : Config
	{
		Gravity3D()
		{
			m_vGravity[0] = 0;
			m_vGravity[1] = 0;
			m_vGravity[2] = 9.81;
		}
	};

	struct ReverseGravity3D : Config
	{
		ReverseGravity3D()
		{
			m_vGravity[0] = 0;
			m_vGravity[1] = 0;
			m_vGravity[2] = -9.81;
		}
	};

public:

	CollisionHandler(const Config& i_oConfiguration);
	~CollisionHandler();

	void RegisterRigidBody( const RigidBody& i_oRigidBody );
	void UnregisterRigidBody( const RigidBody& i_oRigidBody );
	unsigned int DetectCollisions() const;
	
	void Update(double i_fFrameTime);

private:

	class CollisionItem
	{
	public:
		CollisionItem(const Shape& i_oFirstShape, const Shape& i_oSecondShape);
		
		double m_fDeformation;
		PCEVector3D m_vImpactPoint;
		PCEVector3D m_vImpactNormal;
		PCEVector3D m_vImpactVelocity;
		PCEVector3D m_vFrictionForce;

		// Supposing RigidBody2(2) hits RigidBody1(1): 1 suffers a deformation (dX), producing an ElasticForce on 2; 1 and 2 have also FrictionForces between them.
		// So the module of TotalForce in the collision is ElasticForce + FrictionForces
		void ApplyCollision(RigidBody *pRigidBody1, RigidBody *pRigidBody2, double L, double m, double DT);


	private:
		unsigned int m_uiCollisionsCount;
		Shape* m_pFirstShape;
		Shape* m_pSecondShape;

		CollisionItem(const CollisionItem& i_other);
	};

private:

	PCEMap<PCEObjectId,RigidBody*>	m_mDynamicObjects;
	PCEMap<PCEObjectId,RigidBody*>	m_mStaticObjects;
	
	PCEVector<CollisionItem*>	m_vCollisions;
	Config						m_oConfiguration;
};

#endif  //COLLISIONHANDLER_H