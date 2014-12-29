#include <typeinfo>
#include "DrawError.h"
#include "Shape.h"

void Shape::AddSubShape(Shape& i_oShape)
{
	m_vSubShapes.push_back(&i_oShape);
}

void Shape::AddSubShape(const PCEVector<Shape*>& i_vShape)
{
	m_vSubShapes.insert(m_vSubShapes.end(),i_vShape.begin(),i_vShape.end());
}