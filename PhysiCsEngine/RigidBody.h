#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../PCEUtilities/PCEMath.h"

class Collider;

class RigidBody
{
public:

	RigidBody(Collider& i_oOwner, double i_fMass, const PCEVector3D& i_vInertialMass, const PCEVector3D& i_vPosition, const PCEQuaternion& i_oRotation);
	RigidBody(Collider& i_oOwner, double i_fMass, const PCEVector3D& i_vInertialMass, const PCEVector3D& i_vPosition, const PCEVector3D& i_vEulerAngles);
	
	// this will not copy owner shape pointer, so set it manually
	RigidBody(const RigidBody& i_other);

	void ApplyForce(const PCEVector3D& i_vForce, const PCEPoint3D& i_oPointOfApplication);

	void Update(double dt);

	inline void RigidBody::ElasticConstant( double val )
	{
		m_fElasticConstant = val;
	}

	inline void RigidBody::Muv( double val )
	{
		m_rFluidFrictionCoeff = val;
	}

	inline void RigidBody::InverseMass( double val )
	{
		m_rInverseMass = val;
	}

	inline void RigidBody::Velocity( const PCEVector3D& val )
	{
		m_vVelocity = val;

		m_vMomentum = m_vVelocity * m_fMass;
	}

	inline void RigidBody::AngularVelocity( const PCEVector3D& val )
	{
		m_vAngVelocity = val;

		m_vAngularMomentum = AbsoluteRotation(m_oRotationMatrix, WiseProduct(m_vAngVelocity,m_vInertialMatrixTrace));
	}

	inline void RigidBody::Momentum( const PCEVector3D& val )
	{
		m_vMomentum = val;
	}

	inline void RigidBody::AngularMomentum( const PCEVector3D& val )
	{
		m_vAngularMomentum = val;
	}

	inline void RigidBody::TotalForce( const PCEVector3D& val )
	{
		m_vTotalForce = val;
	}

	inline void RigidBody::TotalAngularMomentum( const PCEVector3D& val )
	{
		m_vTotalAngularMomentum = val;
	}

	inline const Collider& RigidBody::Owner() const
	{
		return *m_pOwner;
	}

	inline double RigidBody::ElasticConstant() const
	{
		return m_fElasticConstant;
	}

	inline double RigidBody::Muv() const
	{
		return m_rFluidFrictionCoeff;
	}

	inline double RigidBody::InverseMass() const
	{
		return m_rInverseMass;
	}

	inline const PCEVector3D& RigidBody::Velocity() const
	{
		return m_vVelocity;
	}

	inline const PCEVector3D& RigidBody::AngularVelocity() const
	{
		return m_vAngVelocity;
	}

	inline const PCEVector3D& RigidBody::Momentum() const
	{
		return m_vMomentum;
	}

	inline const PCEVector3D& RigidBody::AngularMomentum() const
	{
		return m_vAngularMomentum;
	}

	inline const PCEVector3D& RigidBody::TotalForce() const
	{
		return m_vTotalForce;
	}

	inline const PCEVector3D& RigidBody::TotalAngularMomentum() const
	{
		return m_vTotalAngularMomentum;
	}

	RigidBody& operator=(const RigidBody& i_other);

private:

	void SetupOtherMembers();

	bool operator==(const RigidBody& i_other) const;
	bool operator!=(const RigidBody& i_other) const;
private:
	Collider*		m_pOwner;

	double			m_fElasticConstant;
	double			m_rFluidFrictionCoeff;
	double			m_rInverseMass;
	double			m_fMass;

	PCEPoint3D		m_vPos;
	PCEVector3D		m_vInertialMatrixTrace;
	PCEVector3D		m_vVelocity;
	PCEVector3D		m_vAngVelocity;
	PCEVector3D		m_vMomentum;
	PCEVector3D		m_vAngularMomentum;
	PCEVector3D		m_vTotalForce;
	PCEVector3D		m_vTotalAngularMomentum;
	PCEQuaternion	m_oRotation;

	PCEMatrix3x3	m_oRotationMatrix;
};

#endif //RIGIDBODY_H