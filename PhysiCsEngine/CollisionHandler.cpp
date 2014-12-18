#include "CollisionHandler.h"
#include "RigidBody.h"

void CollisionHandler::CollisionItem::ApplyCollision( RigidBody *pRigidBody1, RigidBody *pRigidBody2, double L, double m, double DT )
{
	double f;
	double vn;
	double modVtang;
	double fTotalElasticConst;
	{
		double fK1 = pRigidBody1 ? pRigidBody1->GetElasticConstant() : 0;
		double fK2 = pRigidBody2 ? pRigidBody2->GetElasticConstant() : 0;
		fTotalElasticConst = fK1 * fK2 / (fK1 + fK2);
	}

	PCEHVector3 vTangVelocity;
	PCEHVector3 vTangForce;
	PCEHVector3 vNormForce;

	vn = DotProduct(VelImpatto,Normale);
	vTangVelocity = Normale * vn;
	vTangVelocity = VelImpatto - vTangVelocity;

	f = (fTotalElasticConst * Deformazione) + (L * vn);
	if(f < 0) 
	{
		f = 0;
	}

	vNormForce = Normale * f;

	f *= m;
	modVtang = vTangVelocity.Module();
	vTangForce = vTangVelocity * f;

	if(modVtang > 9.8f * DT)
	{
		vTangForce /= modVtang;
	}
	else
	{
		vTangForce /= ( 9.8f * DT );
	}

	vNormForce += vTangForce;	// ora vNormForce e' la F totale

	if(pRigidBody1 != NULL) 
	{
		pRigidBody1->ApplyForce(vNormForce, PuntoImpatto);
	}

	vNormForce[0] = -vNormForce[0];
	vNormForce[1] = -vNormForce[1];
	vNormForce[2] = -vNormForce[2];

	if(pRigidBody2 != NULL) 
	{
		pRigidBody2->ApplyForce(vNormForce, PuntoImpatto);
	}
}
