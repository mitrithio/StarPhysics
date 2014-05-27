#include <typeinfo>
#include "DrawError.h"
#include "Shape.h"

void Shape::setSubShapesInitialCapacity(size_t i_numberOfSubShapes)
{
	if (i_numberOfSubShapes != 0)
	{
		mSubShapes.reserve(i_numberOfSubShapes);
	}
}

void Shape::addSubShape(Shape &i_subShape)
{
	addSubShapeArray(&i_subShape, 1);
}

void Shape::addSubShapeArray(Shape* i_subShapes, unsigned int i_numberOfSubShapes)
{
	if (i_subShapes != nullptr)
	{
		for (size_t i = 0; i < i_numberOfSubShapes; ++i)
		{ 
			mSubShapes.push_back(&i_subShapes[i]);
		}
	}
}

void Shape::addCapacity(unsigned int i_value)
{
	if(i_value != 0)
	{
		mSubShapes.reserve(mSubShapes.capacity() + i_value);
	}
}

// bool Shape::operator==(const Shape& rvalue) const
// {
// 	bool shapeEqual = true;
// 	if (this != &rvalue)
// 	{
// 		for (unsigned int i = 0; shapeEqual && i < mSubShapes.size(); ++i)
// 		{
// 			Shape *thisSubShape = mSubShapes[i];
// 			Shape *rvalueSubShape = rvalue.mSubShapes[i];
// 			if (thisSubShape->mDesc != rvalueSubShape->mDesc 
// 				|| thisSubShape->mType != rvalueSubShape->mType 
// 				|| thisSubShape != rvalueSubShape)
// 			{
// 				shapeEqual = false;
// 			}
// 		}
// 	}
// 	return shapeEqual;
// }
// 
// bool Shape::operator!=(const Shape& rvalue) const
// {
// 	return !(*this == rvalue);
// }
// 
// const Shape& Shape::operator=(const Shape& rvalue)
// {
// 	if (this != &rvalue)
// 	{
// 		mDesc = rvalue.mDesc;
// 		mType = rvalue.mType;
// 		mSubShapes = rvalue.mSubShapes;
// 	}
// 	return *this;
// }