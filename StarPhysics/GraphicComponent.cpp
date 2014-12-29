#include "GraphicComponent.h"

GraphicComponent::GraphicComponent( const PCEString& i_sImagePath, PCEPoint3D i_oPosition, double i_fRotation, const PositionableObject * i_oOwner, bool i_bEnabled /*= true*/ )
	: Component( GRAPHIC_COMPONENT, i_oPosition, i_fRotation )
{
	CreateBitmap( i_sImagePath.c_str() );
}


GraphicComponent::~GraphicComponent(void)
{
	DestroyBitmap();
}

void GraphicComponent::OnRender(Bitmap* renderTarget)
{
	const PCEPoint3D& pAbsolutePosition = GetAbsolutePosition();
	mp_image->DrawRotatedTo( renderTarget, pAbsolutePosition[0], pAbsolutePosition[1], m_oRelativePosition[0], m_oRelativePosition[1], GetAbsoluteRotation() );
}

void GraphicComponent::setOwner( GameObject & i_owner )
{
	mp_ownerObject = &i_owner;
}

void GraphicComponent::CreateBitmap( const char* i_imagePath )
{
	m_oFile.load( i_imagePath );
	m_oFile.RawData->BgraInfoData.a = 0; 
	mp_image = new Bitmap( &m_oFile );
}

void GraphicComponent::DestroyBitmap()
{
	delete mp_image;
}

void GraphicComponent::update( double /*i_deltaTime*/ /*= 0 */ )
{

}
