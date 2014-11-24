#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "shape.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(void);
	~BoxCollider(void);
};

#endif //BOXCOLLIDER_H