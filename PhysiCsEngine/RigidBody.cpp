#include "RigidBody.h"

RigidBody::RigidBody( const RigidBody& i_other ) 
{
	m_pOwner = nullptr;
	m_fMass = i_other.m_fMass;
	m_vInertialMatrixTrace = i_other.m_vInertialMatrixTrace;
	m_vPos = i_other.m_vPos;
	m_oRotation = i_other.m_oRotation;
	m_fElasticConstant = i_other.m_fElasticConstant;
	m_vVelocity	= i_other.m_vVelocity;
	m_vAngVelocity = i_other.m_vAngVelocity;
	m_vMomentum = i_other.m_vMomentum;
	m_vAngularMomentum = i_other.m_vAngularMomentum;
	m_oRotationMatrix = i_other.m_oRotationMatrix;
	m_vTotalForce = i_other.m_vTotalForce;
	m_vTotalAngularMomentum = i_other.m_vTotalAngularMomentum;
}

RigidBody::RigidBody(Collider& i_oOwner, double i_fMass, const PCEVector3D& i_vInertialMass, const PCEVector3D& i_vPosition, const PCEVector3D& i_vEulerAngles) 
	: m_pOwner(&i_oOwner)
	, m_fMass(i_fMass)
	, m_vInertialMatrixTrace(i_vInertialMass)
	, m_vPos(i_vPosition)
	, m_oRotation(i_vEulerAngles)
{
	SetupOtherMembers();
}

RigidBody::RigidBody(Collider& i_oOwner, double i_fMass, const PCEVector3D& i_vInertialMass, const PCEVector3D& i_vPosition, const PCEQuaternion& i_oRotation) 
	: m_pOwner(&i_oOwner)
	, m_fMass( i_fMass )
	, m_vInertialMatrixTrace( i_vInertialMass )
	, m_vPos( i_vPosition )
	, m_oRotation( i_oRotation )
{
	SetupOtherMembers();
}

void RigidBody::SetupOtherMembers()
{
	m_fElasticConstant = 0.0f;
	m_vVelocity *= 0.0f;
	m_vAngVelocity *= 0.0f;
	m_vMomentum = m_vVelocity * m_fMass;
	m_vAngularMomentum = WiseProduct(m_vAngVelocity, m_vInertialMatrixTrace);
	m_oRotationMatrix = MatriceDaQuaternione(m_oRotation);
	m_vTotalForce *= 0.0f;
	m_vTotalAngularMomentum *= 0.0f;
}

void RigidBody::Update( double dt )
{
	m_vMomentum += (m_vTotalForce * dt);

	m_vAngularMomentum += (m_vTotalAngularMomentum * dt);

	m_vVelocity = m_vMomentum / m_fMass;
	m_vPos += ( m_vVelocity * dt );
	
	{
	PCEVector3D vRelativeAngularMomentum = RelativeRotation( m_oRotationMatrix, m_vAngularMomentum );

	m_vAngVelocity = WiseProduct(vRelativeAngularMomentum, 1/m_vInertialMatrixTrace);
	}
	{
	PCEQuaternion oTmpQuaternion( 1, m_vAngVelocity[0] * dt / 2, m_vAngVelocity[1] * dt / 2, m_vAngVelocity[2] * dt / 2 );

	oTmpQuaternion = oTmpQuaternion.Normal();
	m_oRotation *= oTmpQuaternion;
	m_oRotation = m_oRotation.Normal();
	}

	m_vAngVelocity = AbsoluteRotation(m_oRotationMatrix, m_vAngVelocity);

	m_oRotationMatrix = MatriceDaQuaternione(m_oRotation);
}

void RigidBody::ApplyForce( const PCEVector3D& i_vForce, const PCEPoint3D& i_oPointOfApplication )
{
	PCEVector3D vArm;

	m_vTotalForce += i_vForce;
	vArm = i_oPointOfApplication - m_vPos;
	m_vTotalAngularMomentum += CrossProduct(vArm, i_vForce);
}

RigidBody& RigidBody::operator=(const RigidBody& i_other)
{
	if (this != &i_other)
	{
		m_pOwner = i_other.m_pOwner;
		m_fMass = i_other.m_fMass;
		m_vInertialMatrixTrace = i_other.m_vInertialMatrixTrace;
		m_vPos = i_other.m_vPos;
		m_oRotation = i_other.m_oRotation;
		m_fElasticConstant = i_other.m_fElasticConstant;
		m_vVelocity	= i_other.m_vVelocity;
		m_vAngVelocity = i_other.m_vAngVelocity;
		m_vMomentum = i_other.m_vMomentum;
		m_vAngularMomentum = i_other.m_vAngularMomentum;
		m_oRotationMatrix = i_other.m_oRotationMatrix;
		m_vTotalForce = i_other.m_vTotalForce;
		m_vTotalAngularMomentum = i_other.m_vTotalAngularMomentum;
	}

	return *this;
}
