#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../PCEUtilities/PCEMath.h"

class Shape;

class RigidBody
{
public:

	RigidBody(Shape& i_oOwner, double i_fMass, const PCEHVector3& i_vInertialMass, const PCEHVector3& i_vPosition, const PCEQuaternion& i_oRotation);
	RigidBody(Shape& i_oOwner, double i_fMass, const PCEHVector3& i_vInertialMass, const PCEHVector3& i_vPosition, const PCEHVector3& i_vEulerAngles);
	
	// this will not copy owner shape pointer, so set it manually
	RigidBody(const RigidBody& i_other);

	void ApplyForce(const PCEHVector3& i_vForce, const PCEPoint& i_oPointOfApplication);

	void Update(double dt);

	void SetOwner(Shape& val);
	void SetElasticConstant(double val);
	void SetVelocity(const PCEHVector3& val);
	void SetAngularVelocity(const PCEHVector3& val);
	void SetMomentum(const PCEHVector3& val);
	void SetAngularMomentum(const PCEHVector3& val);
	void SetTotalForce(const PCEHVector3& val);
	void SetTotalAngularMomentum(const PCEHVector3& val);

	const Shape& GetOwner() const;
	double GetElasticConstant() const;
	const PCEHVector3& GetVelocity() const;
	const PCEHVector3& GetAngularVelocity() const;
	const PCEHVector3& GetMomentum() const;
	const PCEHVector3& GetAngularMomentum() const;
	const PCEHVector3& GetTotalForce() const;
	const PCEHVector3& GetTotalAngularMomentum() const;

	bool operator==(const RigidBody& i_other) const;
	bool operator!=(const RigidBody& i_other) const;
	RigidBody& operator=(const RigidBody& i_other);

private:

	void SetupOtherMembers();

private:
	Shape*			m_pOwner;
	double			m_fElasticConstant;
	double			m_fMass;
	PCEHVector3		m_vInertialMatrixTrace;

	PCEPoint		m_vPos;
	PCEQuaternion	m_oRotation;
	PCEHVector3		m_vVelocity;
	PCEHVector3		m_vAngVelocity;
	PCEHVector3		m_vMomentum;
	PCEHVector3		m_vAngularMomentum;
	PCEMatrix<3,3>	m_oRotationMatrix;

	PCEHVector3		m_vTotalForce;
	PCEHVector3		m_vTotalAngularMomentum;
};

#endif //RIGIDBODY_H