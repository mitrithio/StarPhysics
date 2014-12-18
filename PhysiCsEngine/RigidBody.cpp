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

RigidBody::RigidBody(Shape& i_oOwner, double i_fMass, const PCEHVector3& i_vInertialMass, const PCEHVector3& i_vPosition, const PCEHVector3& i_vEulerAngles) 
	: m_pOwner(&i_oOwner)
	, m_fMass(i_fMass)
	, m_vInertialMatrixTrace(i_vInertialMass)
	, m_vPos(i_vPosition)
	, m_oRotation(i_vEulerAngles)
{
	SetupOtherMembers();
}

RigidBody::RigidBody(Shape& i_oOwner, double i_fMass, const PCEHVector3& i_vInertialMass, const PCEHVector3& i_vPosition, const PCEQuaternion& i_oRotation) 
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
	PCEHVector3 vRelativeAngularMomentum = RelativeRotation( m_oRotationMatrix, m_vAngularMomentum );

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

void RigidBody::ApplyForce( const PCEHVector3& i_vForce, const PCEPoint& i_oPointOfApplication )
{
	PCEHVector3 vArm;

	m_vTotalForce += i_vForce;
	vArm = i_oPointOfApplication - m_vPos;
	m_vTotalAngularMomentum += CrossProduct(vArm, i_vForce);
}

void RigidBody::SetOwner( Shape& val )
{
	m_pOwner = &val;
}

void RigidBody::SetElasticConstant( double val )
{
	m_fElasticConstant = val;
}

void RigidBody::SetVelocity( const PCEHVector3& val )
{
	m_vVelocity = val;

	m_vMomentum = m_vVelocity * m_fMass;
}

void RigidBody::SetAngularVelocity( const PCEHVector3& val )
{
	m_vAngVelocity = val;

	m_vAngularMomentum = AbsoluteRotation(m_oRotationMatrix, WiseProduct(m_vAngVelocity,m_vInertialMatrixTrace));
}

void RigidBody::SetMomentum( const PCEHVector3& val )
{
	m_vMomentum = val;
}

void RigidBody::SetAngularMomentum( const PCEHVector3& val )
{
	m_vAngularMomentum = val;
}

void RigidBody::SetTotalForce( const PCEHVector3& val )
{
	m_vTotalForce = val;
}

void RigidBody::SetTotalAngularMomentum( const PCEHVector3& val )
{
	m_vTotalAngularMomentum = val;
}

const Shape& RigidBody::GetOwner() const
{
	return *m_pOwner;
}

double RigidBody::GetElasticConstant() const
{
	return m_fElasticConstant;
}

const PCEHVector3& RigidBody::GetVelocity() const
{
	return m_vVelocity;
}

const PCEHVector3& RigidBody::GetAngularVelocity() const
{
	return m_vAngVelocity;
}

const PCEHVector3& RigidBody::GetMomentum() const
{
	return m_vMomentum;
}

const PCEHVector3& RigidBody::GetAngularMomentum() const
{
	return m_vAngularMomentum;
}

const PCEHVector3& RigidBody::GetTotalForce() const
{
	return m_vTotalForce;
}

const PCEHVector3& RigidBody::GetTotalAngularMomentum() const
{
	return m_vTotalAngularMomentum;
}

bool RigidBody::operator==(const RigidBody& i_other) const
{

}

bool RigidBody::operator!=(const RigidBody& i_other) const
{

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
