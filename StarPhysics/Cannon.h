#ifndef CANNON_H
#define	CANNON_H

#include "gameobject.h"
#include "..\PhysiCsEngine\PCE.h"
#include "CirclesController.h"

class Cannon : public GameObject
{
public:
	Cannon();
	Cannon( PCEPoint3D i_oPosition, double i_fRotation );
	~Cannon();

private:

	CirclesController m_oBallController;
	PCEVector<Shape*> m_vBalls;
};

#endif //CANNON_H