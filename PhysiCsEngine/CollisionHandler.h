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

	void RegisterShape( const RigidBody& i_oRigidBody );
	unsigned int DetectCollisions() const;
	
private:
	class CollisionItem
	{
	public:
		CollisionItem(const Shape& i_oFirstShape, const Shape& i_oSecondShape);
		
		float Deformazione;
		PCEVector3 PuntoImpatto;
		PCEVector3 Normale;
		PCEVector3 VelImpatto;

		void ApplicaForzeCollisione(RigidBody *c1, RigidBody *c2, float K, float L, float m)
		{
			float f;
			float vn;
			float modVtang;
			PCEHVector3 Vtang;
			PCEHVector3 Ftang;
			PCEHVector3 Fnorm;

			vn = VelImpatto * Normale;
			Vtang = Normale * vn;
			Vtang = VelImpatto - Vtang;

			f = (K * Deformazione) + (L * vn);
			if(f < 0) f = 0;
			MoltiplicaVettoreScalare(Normale, f, Fnorm);

			f *= m;		// forza attrito (modulo)
			modVtang = ModuloVettore(Vtang);
			MoltiplicaVettoreScalare(Vtang, f, Ftang);

			if(modVtang > 9.8f * DT) DividiVettoreScalare(Ftang, modVtang, Ftang);
			else DividiVettoreScalare(Ftang, 9.8f * DT, Ftang);

			SommaVettori(Fnorm, Ftang, Fnorm);	// ora Fnorm e' la F totale

			if(c1 != NULL) c1->ApplicaForza(Fnorm, PuntoImpatto);
			Fnorm[0] = -Fnorm[0];
			Fnorm[1] = -Fnorm[1];
			Fnorm[2] = -Fnorm[2];
			if(c2 != NULL) c2->ApplicaForza(Fnorm, PuntoImpatto);
		}


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

class RigidBody
{

public:

	float Massa;
	float Inerzia[3];

	PCEHVector3 Pos;
	PCEQuaternion Rot;
	PCEHVector3 Vel;
	PCEHVector3 Vang;

	PCEHVector3 Qmoto;
	PCEHVector3 Mang;

	PCEMatrix<3,3> MRot;

	PCEHVector3 Fris;
	PCEHVector3 Mris;

	void ApplicaForza(const PCEHVector3& Forza, const PCEHVector3& PuntoApplicazione)
	{
		PCEHVector3 b;

		Fris = Forza + Fris;
		b = PuntoApplicazione - Pos;
		b = CrossProduct(b, Forza);
		Mris = b + Mris;
	}

	void IntegraStato(float dt)
	{
		PCEHVector3 v;
		PCEQuaternion q;

		v = Fris * dt;
		Qmoto = v + Qmoto;
		v = Mris * dt;
		Mang = v + Mang;

		Vel = Qmoto / Massa;
		v = Vel * dt;
		Pos = v + Pos;

		Mang = RelativeRotation( MRot, Mang );

		Vang[0] /= Inerzia[0];
		Vang[1] /= Inerzia[1];
		Vang[2] /= Inerzia[2];
		q[0] = 1;
		q[1] = Vang[0] * dt / 2;
		q[2] = Vang[1] * dt / 2;
		q[3] = Vang[2] * dt / 2;

		q = q.Normal();
		Rot = Rot * q;
		Rot = Rot.Normal();

		Vang = AbsoluteRotation(MRot,Vang);

		MRot = MatriceDaQuaternione(Rot);
	}

};

#endif  //COLLISIONHANDLER_H