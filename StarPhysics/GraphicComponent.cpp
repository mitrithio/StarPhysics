#include "GraphicComponent.h"

GraphicComponent::GraphicComponent( const PCEString* i_sImagePath, PCEVector2 i_oPosition, float i_fRotation, const PositionableObject * i_oOwner, bool i_bEnabled /*= true*/ )
	: Component( GRAPHIC, i_oPosition, i_fRotation )
{
	CreateBitmap( i_sImagePath->getStringAsChar() );
}


GraphicComponent::~GraphicComponent(void)
{
	DestroyBitmap();
}

void GraphicComponent::OnRender(Bitmap* renderTarget)
{
	mp_image->DrawRotatedTo( renderTarget, m_oAbsolutePosition.mX, m_oAbsolutePosition.mY, m_oRelativePosition.mX, m_oRelativePosition.mY, GetAbsoluteRotation() );
}
