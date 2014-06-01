#include <typeinfo>
#include "DrawError.h"
#include "Shape.h"

void Shape::addSubShape(Shape &i_subShape)
{
	m_subShapes.push_back(&i_subShape);
}

void Shape::addSubShape(Shape** i_subShapeArray, const unsigned int i_numberOfElements)
{
	m_subShapes.push_back(i_subShapeArray, i_numberOfElements);
}

void Shape::addSubShape(const PCEVector<Shape *>& i_subShapeVector)
{
	m_subShapes.push_back(i_subShapeVector);
}

void Shape::addCapacity(unsigned int i_value)
{
	m_subShapes.resize(m_subShapes.capacity() + i_value);
}

/*
bool Shape::operator==(const Shape& rvalue) const
{
	bool shapeEqual = true;
	if (this != &rvalue)
	{
		for (unsigned int i = 0; shapeEqual && i < m_subShapes.size(); ++i)
		{
			Shape *thisSubShape = m_subShapes[i];
			Shape *rvalueSubShape = rvalue.m_subShapes[i];
			shapeEqual = (thisSubShape->mDesc == rvalueSubShape->mDesc && 
						  thisSubShape->mType == rvalueSubShape->mType &&
						  thisSubShape == rvalueSubShape);
		}
	}
	return shapeEqual;
}

bool Shape::operator!=(const Shape& rvalue) const
{
	return !(*this == rvalue);
}

Shape& Shape::operator=(const Shape& rvalue)
{
	if (this != &rvalue)
	{
		mDesc = rvalue.mDesc;
		mType = rvalue.mType;
		m_subShapes = rvalue.m_subShapes;
	}
	return *this;
}*/