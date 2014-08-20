#pragma once

#include "../WinDraw/WinDraw.h"					//load the whole WinDraw library
#include "../PCEUtilities/PCEUtilities.h"
#include "Component.h"
#include "GameObject.h"

class GraphicComponent : public Component
{
public:
	GraphicComponent(const PCEString* i_sImagePath, PCEVector2 i_oPosition, float i_fRotation, const PositionableObject * i_oOwner, bool i_bEnabled = true);
	~GraphicComponent(void);

	void OnRender(Bitmap* renderTarget);

	void setOwner(GameObject & i_owner)
	{
		mp_ownerObject = &i_owner;
	}

private:

	GameObject * mp_ownerObject;
	Bitmap * mp_image;
	
	void CreateBitmap(const char* i_imagePath)
	{
		mp_image = new Bitmap(i_imagePath);
	}

	void DestroyBitmap()
	{
		delete mp_image;
	}
};

