#pragma once

#include "../WinDraw/WinDraw.h"					//load the whole WinDraw library
#include "../PCEUtilities/PCEUtilities.h"
#include "Component.h"
#include "GameObject.h"
#include "../WinDraw/TGAFile.h"

class GraphicComponent : public Component
{
public:
	GraphicComponent(const PCEString& i_sImagePath, PCEVector2 i_oPosition, float i_fRotation, const PositionableObject * i_oOwner, bool i_bEnabled = true);
	~GraphicComponent(void);

	void OnRender(Bitmap* renderTarget);

	void setOwner(GameObject & i_owner);

private:

	void CreateBitmap(const char* i_imagePath);

	void DestroyBitmap();

	virtual void update( float i_deltaTime = 0 );

private:

	TGAFile m_oFile;
	GameObject * mp_ownerObject;
	Bitmap * mp_image;

};

