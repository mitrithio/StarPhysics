#include <typeinfo>
#include "DrawError.h"
#include "Shape.h"

void Shape::addSubShape(Shape& i_subShape)
{
	m_subShapes.push_back(&i_subShape);
}

void Shape::addSubShape(const PCEVector<Shape *>& i_subShapeVector)
{
	m_subShapes.push_back(i_subShapeVector);
}

void Shape::addCapacity(unsigned int i_value)
{
	m_subShapes.resize(m_subShapes.capacity() + i_value);
}