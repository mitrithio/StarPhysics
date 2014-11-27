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

	void AddShape( const RigidBody& i_oRigidBody );
	unsigned int DetectCollisions() const;
	
private:
	class CollisionItem
	{
	public:
		CollisionItem(const Shape& i_oFirstShape, const Shape& i_oSecondShape);
	};
private:

	PCEMap<PCEObjectId,RigidBody*>	m_mDynamicObjects;
	PCEMap<PCEObjectId,RigidBody*>	m_mStaticObjects;
	
	PCEVector<CollisionItem>	m_mCollisions;
};

#endif  //COLLISIONHANDLER_H