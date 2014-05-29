#include <typeinfo>
#include "DrawError.h"
#include "Shape.h"

void Shape::addSubShape(Shape &i_subShape)
{
	mSubShapes.push_back(&i_subShape);
}

void Shape::addSubShapeArray(Shape * i_subShapes, unsigned int i_numberOfSubShapes)
{
	
}

void Shape::addCapacity(unsigned int i_value)
{
	mSubShapes.reserve(mSubShapes.capacity() + i_value);
}

bool Shape::operator==(const Shape& rvalue) const
{
	bool shapeEqual = true;
	if (this != &rvalue)
	{
		for (unsigned int i = 0; shapeEqual && i < mSubShapes.size(); ++i)
		{
			Shape *thisSubShape = mSubShapes[i];
			Shape *rvalueSubShape = rvalue.mSubShapes[i];
			if (thisSubShape->mDesc != rvalueSubShape->mDesc 
				|| thisSubShape->mType != rvalueSubShape->mType 
				|| thisSubShape != rvalueSubShape)
			{
				shapeEqual = false;
			}
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
		mSubShapes = rvalue.mSubShapes;
	}
	return *this;
}