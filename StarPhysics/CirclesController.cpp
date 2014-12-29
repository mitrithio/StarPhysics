#include "CirclesController.h"
#include "Circle.h"
#include "PhysicComponent.h"
#include "GraphicComponent.h"

const PCEString CirclesController::IMAGES_CIRCLE_PATH( "Sphere0");


CirclesController::CirclesController()
	: m_uiNextCircleFree( 0 )
{
}

CirclesController::CirclesController( unsigned int i_uiNumberOfCircles )
{
	CreateCirclePool( i_uiNumberOfCircles );
}


CirclesController::~CirclesController()
{
	for ( PCEMap<PCEObjectId,Circle*>::iterator it = m_oCirclesMap.begin(); it != m_oCirclesMap.end(); ++it )
	{
		delete (*it).second;
	}
}

void CirclesController::CreateCircle( PCEPoint3D i_oPosition, double i_fRotation )
{
	Circle * pCircle = new Circle( i_oPosition, i_fRotation );
	pCircle->SetEnable( false );
	PCEString szKey( "Circle" );
	szKey += PCEString::INT_TO_STRING( m_oCirclesMap.size() );
	pCircle->SetID( szKey.c_str() );
	pCircle->RegisterComponent( new PhysicComponent( i_oPosition, i_fRotation, true, pCircle ) );
	pCircle->setLevel( 1 );
	
	PCEString szImagePath = IMAGES_CIRCLE_PATH;
	szImagePath += PCEString::INT_TO_STRING( pCircle->getLevel() ) + ".tga";
	pCircle->RegisterComponent( new GraphicComponent( szImagePath.c_str(), i_oPosition, i_fRotation, pCircle, true ) );
	m_oCirclesMap[PCEObjectId(szKey)] = pCircle;
	m_vIsCircleFree.push_back( true );
}

void CirclesController::CreateCirclePool( unsigned int i_uiNumberOfCircle )
{
	if ( m_oCirclesMap.size() == 0 )
	{
		for ( unsigned int uiIndex = 0; uiIndex < i_uiNumberOfCircle; ++uiIndex )
		{
			CreateCircle( PCEPoint3D( 0, 0, 0 ), 0.f );
		}
		m_uiNextCircleFree = 0;
	}
}

void CirclesController::Update( double i_fDeltaTime )
{
	for ( PCEMap<PCEObjectId,Circle*>::iterator it = m_oCirclesMap.begin(); it != m_oCirclesMap.end(); ++it )
	{
		(*it).second->Update( i_fDeltaTime );
	}
}

const PCEObjectId& CirclesController::GetNextFreeCircleID()
{
	for ( unsigned int uiIndex = 0; uiIndex < m_vIsCircleFree.size(); ++uiIndex )
	{
		if ( m_vIsCircleFree.at(uiIndex) && ( m_oCirclesMap.begin() + uiIndex != m_oCirclesMap.end() ) )
		{
			return (*( m_oCirclesMap.begin() + uiIndex )).second->GetID();
		}
	}

	return INVALID_CIRCLE.GetID();
}
