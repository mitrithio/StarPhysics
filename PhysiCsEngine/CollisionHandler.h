#ifndef COLLISIONHANDLER_H 
#define COLLISIONHANDLER_H

#include "../PCEUtilities/PCEUtilities.h"

class RigidBody;
class Shape;


class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	void RegisterRigidBody( const RigidBody& i_oRigidBody );
	void UnregisterRigidBody( const RigidBody& i_oRigidBody );
	unsigned int DetectCollisions() const;
	
private:
	class CollisionItem
	{
	public:
		CollisionItem(const Shape& i_oFirstShape, const Shape& i_oSecondShape);
		
		double Deformazione;
		PCEHVector3 PuntoImpatto;
		PCEHVector3 Normale;
		PCEHVector3 VelImpatto;

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
	
	PCEVector<CollisionItem>	m_mCollisions;
};

#endif  //COLLISIONHANDLER_H