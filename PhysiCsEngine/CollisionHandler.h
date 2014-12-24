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
		Config( double i_rX, double i_rY, double i_rZ )
			: m_vGravity(i_rX,i_rY,i_rZ)
		{
		}
	};

	struct ZeroGravity : Config
	{
		ZeroGravity()
			: Config(0.0,0.0,0.0)
		{
		}
	};

	struct Gravity2D : Config
	{
		Gravity2D()
			:Config(0.0,9.81,0.0)
		{
		}
	};

	struct ReverseGravity2D : Config
	{
		ReverseGravity2D()
			: Config(0.0,-9.81,0.0)
		{
		}
	};

	struct Gravity3D : Config
	{
		Gravity3D()
			: Config(0.0,0.0,9.81)
		{
		}
	};

	struct ReverseGravity3D : Config
	{
		ReverseGravity3D()
			: Config(0.0,0.0,-9.81)
		{
		}
	};

public:

	CollisionHandler(const Config& i_oConfiguration);
	~CollisionHandler();

	void RegisterDynamicRigidBody( const PCEObjectId& i_oId, RigidBody& i_oDynamicRigidBody );
	void RegisterEverStaticRigidBody( const PCEObjectId& i_oId, RigidBody& i_oEverStaticRigidBody );
	void UnregisterRigidBody( const PCEObjectId& i_oId );
	unsigned int DetectCollisions( double i_rFrameTime );
	
	void Update(double i_fFrameTime);

private:

	class CollisionItem
	{
	public:
		CollisionItem(const Shape& i_oFirstShape, const Shape& i_oSecondShape);
		
		double m_rDeformation;
		PCEVector3D m_vImpactPoint;
		PCEVector3D m_vImpactNormal;
		PCEVector3D m_vImpactVelocity;
		PCEVector3D m_vFrictionForce;

		// Supposing RigidBody2(2) hits RigidBody1(1): 1 suffers a deformation (dX), producing an ElasticForce on 2; 1 and 2 have also FrictionForces between them.
		// So the module of TotalForce in the collision is ElasticForce + FrictionForces
		void ApplyCollision( RigidBody& pRigidBody1, RigidBody& pRigidBody2, double i_rMu, double i_rFrameTime);


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