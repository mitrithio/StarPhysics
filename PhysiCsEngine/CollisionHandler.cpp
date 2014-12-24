#include "CollisionHandler.h"
#include "RigidBody.h"
#include "Shape.h"

CollisionHandler::CollisionHandler( const Config& i_oConfiguration )
	: m_oConfiguration( i_oConfiguration )
{
}

void CollisionHandler::RegisterDynamicRigidBody( const PCEObjectId& i_oId, RigidBody& i_oDynamicRigidBody )
{
	if ( m_mDynamicObjects.find(i_oId) == m_mDynamicObjects.end() );
	{ 
		m_mDynamicObjects[i_oId] = &i_oDynamicRigidBody;
	}
}

void CollisionHandler::RegisterEverStaticRigidBody( const PCEObjectId& i_oId, RigidBody& i_oEverStaticRigidBody )
{
	if ( m_mStaticObjects.find(i_oId) == m_mStaticObjects.end() )
	{
		m_mStaticObjects[i_oId] = &i_oEverStaticRigidBody;
	}
}

void CollisionHandler::UnregisterRigidBody( const PCEObjectId& i_oId )
{
	if (m_mDynamicObjects.find(i_oId) != m_mDynamicObjects.end())
	{
		m_mDynamicObjects.erase(i_oId);
	}
}

void CollisionHandler::Update( double i_fFrameTime )
{
	DetectCollisions( i_fFrameTime );
}

unsigned int CollisionHandler::DetectCollisions( double i_rFrameTime )
{
	PCEMap<PCEObjectId,RigidBody*>::iterator itDynamics = m_mDynamicObjects.begin();
	PCEMap<PCEObjectId,RigidBody*>::iterator itDynamicsEnd = m_mDynamicObjects.end();
	PCEMap<PCEObjectId,RigidBody*>::iterator itNextDynamic = itDynamics + 1;

	PCEMap<PCEObjectId,RigidBody*>::iterator itStatics = m_mStaticObjects.begin();
	PCEMap<PCEObjectId,RigidBody*>::iterator itStaticsEnd = m_mStaticObjects.end();
	
	for ( ; itDynamics != itDynamicsEnd; ++itDynamics )
	{
		for ( ; itNextDynamic != itDynamicsEnd; ++itNextDynamic)
		{
			const Collider& pFirstShape = (*itDynamics).second->Owner();
			const Collider& pSecondShape = (*itNextDynamic).second->Owner();
			double distance = pSecondShape.CheckCollisionWith( pFirstShape );
		}
	}
}

void CollisionHandler::CollisionItem::ApplyCollision( RigidBody& i_oRigidBody1, RigidBody& i_oRigidBody2, double i_rMu, double /*i_rFrameTime*/ )
{
	// i_oRigidBody2 collides with i_oRigidBody1.
	// Total elastic force:
	double rTotalElasticConst;
	{
		double fK1 = i_oRigidBody1.ElasticConstant();
		double fK2 = i_oRigidBody2.ElasticConstant();
		if ( *(int*)&fK1 != 0 && *(int*)&fK2 != 0 ) // the two bodies' behavior is the same as two spring in series 
		{
			rTotalElasticConst = fK1 * fK2 / (fK1 + fK2);
		}
		else if ( *(int*)&fK1 == 0 )				// only the second body produce elastic force
		{
			rTotalElasticConst = fK2;
		}
		else										// only the first body produce elastic force or neither
		{
			rTotalElasticConst = fK1;
		}
	}

	PCEVector3D vElasticForce = m_vImpactNormal * ( rTotalElasticConst * m_rDeformation );

	// Fluid Friction:
	PCEVector3D vTotalFluidFriction = ( i_oRigidBody1.Velocity() * i_oRigidBody1.Muv() ) + ( i_oRigidBody2.Velocity() * i_oRigidBody2.Muv() );
	PCEVector3D vNormalFluidFriction = DotProduct(vTotalFluidFriction, m_vImpactNormal) * m_vImpactNormal;
	PCEVector3D vTangFluidFriction = vTotalFluidFriction - vNormalFluidFriction;

	// Force Normal Component: elastic force + fluid friction normal
	double rNormalForceModule = DotProduct( vElasticForce + vNormalFluidFriction, m_vImpactNormal );
	if(rNormalForceModule < 0) 
	{
		rNormalForceModule = 0;
	}

	PCEVector3D vNormForce = m_vImpactNormal * rNormalForceModule;

	// Force Tangent Component: dry friction and fluid friction tangent
	PCEVector3D vTangVelocity = m_vImpactVelocity - (DotProduct(m_vImpactVelocity,m_vImpactNormal) * m_vImpactNormal);
	double rFrictionForceModule = rNormalForceModule * i_rMu;
	PCEVector3D vTangForce = ( vTangVelocity * rFrictionForceModule ) + vTangFluidFriction;

/*
	double modVtang = vTangVelocity.Module();
	if(modVtang > 9.81f * i_rFrameTime)
	{
		vTangForce /= modVtang;
	}
	else
	{
		vTangForce /= ( 9.8f * i_rFrameTime );
	}
*/

	vNormForce += vTangForce;	// now vNormForce is the total force

	i_oRigidBody1.ApplyForce(vNormForce, m_vImpactPoint);

	vNormForce[0] = -vNormForce[0];
	vNormForce[1] = -vNormForce[1];
	vNormForce[2] = -vNormForce[2];

	i_oRigidBody2.ApplyForce(vNormForce, m_vImpactPoint);
}