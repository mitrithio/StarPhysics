#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../PCEUtilities/PCEMath.h"

class Shape;

class RigidBody
{
public:

	RigidBody(Shape& i_oOwner, double i_fMass, const PCEVector3D& i_vInertialMass, const PCEVector3D& i_vPosition, const PCEQuaternion& i_oRotation);
	RigidBody(Shape& i_oOwner, double i_fMass, const PCEVector3D& i_vInertialMass, const PCEVector3D& i_vPosition, const PCEVector3D& i_vEulerAngles);
	
	// this will not copy owner shape pointer, so set it manually
	RigidBody(const RigidBody& i_other);

	void ApplyForce(const PCEVector3D& i_vForce, const PCEPoint& i_oPointOfApplication);

	void Update(double dt);

	void SetOwner(Shape& val);
	void SetElasticConstant(double val);
	void SetVelocity(const PCEVector3D& val);
	void SetAngularVelocity(const PCEVector3D& val);
	void SetMomentum(const PCEVector3D& val);
	void SetAngularMomentum(const PCEVector3D& val);
	void SetTotalForce(const PCEVector3D& val);
	void SetTotalAngularMomentum(const PCEVector3D& val);

	const Shape& GetOwner() const;
	double GetElasticConstant() const;
	const PCEVector3D& GetVelocity() const;
	const PCEVector3D& GetAngularVelocity() const;
	const PCEVector3D& GetMomentum() const;
	const PCEVector3D& GetAngularMomentum() const;
	const PCEVector3D& GetTotalForce() const;
	const PCEVector3D& GetTotalAngularMomentum() const;

	bool operator==(const RigidBody& i_other) const;
	bool operator!=(const RigidBody& i_other) const;
	RigidBody& operator=(const RigidBody& i_other);

private:

	void SetupOtherMembers();

private:
	Shape*			m_pOwner;
	double			m_fElasticConstant;
	double			m_fMass;
	PCEVector3D		m_vInertialMatrixTrace;

	PCEPoint		m_vPos;
	PCEQuaternion	m_oRotation;
	PCEVector3D		m_vVelocity;
	PCEVector3D		m_vAngVelocity;
	PCEVector3D		m_vMomentum;
	PCEVector3D		m_vAngularMomentum;
	PCEMatrix<3,3>	m_oRotationMatrix;

	PCEVector3D		m_vTotalForce;
	PCEVector3D		m_vTotalAngularMomentum;
};

#endif //RIGIDBODY_H