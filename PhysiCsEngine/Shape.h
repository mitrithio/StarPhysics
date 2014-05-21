#ifndef PCE_SHAPE_H
#define PCE_SHAPE_H

#include "..\PCEUtilities\PCEUtilities.h"
#include "EnumDefinitions.h"

class Shape{
public:
	static class Point{
	public:
		float mX;
		float mY;
		float mZ;

		inline bool operator== (const Point& rvalue) const		{return mX == rvalue.mX && mY == rvalue.mY && mZ == rvalue.mZ;}

		inline bool operator!= (const Point& rvalue) const		{return !(*this == rvalue);}	
		
		Point& operator= (const Point& rvalue)					{mX = rvalue.mX; 
																 mY = rvalue.mY; 
																 mZ = rvalue.mZ;
																 return *this;
																}

		Point(float i_x, float i_y, float i_z = 0)
			: mX(i_x)
			, mY(i_y)
			, mZ(i_z)
		{}
	};

	static class Description{
	public:

		EnumShapeDesc mDescName;
		EnumShapeDescType mType;

		//Description(): mDescName(nullptr), mType(nullptr){};
		Description(const EnumShapeDesc i_descName, const EnumShapeDescType i_typeName)
		{
			mDescName = i_descName;
			mType = i_typeName;
		}

		inline Description& operator=(const Description& rvalue)
		{
			mDescName = rvalue.mDescName;
			mType = rvalue.mType;
			return *this;
		}

		inline bool operator==(const Description& rvalue)
		{
			return mDescName == rvalue.mDescName && mType == rvalue.mType;
		}

		inline bool operator!=(const Description& rvalue)
		{
			return !(*this == rvalue);
		}
	};

	Shape() : mDesc(nullptr){}
	Shape(const Description& i_desc){ mDesc = new Description(i_desc.mDescName, i_desc.mType);}
	Shape(const EnumShapeDesc i_descName, const EnumShapeDescType i_descType){mDesc = new Description(i_descName, i_descType);}
	~Shape()
	{
		if (mDesc != nullptr)
		{
			delete mDesc;
		}
	}

	inline const Description& getDescription() const	{return *mDesc;}

	virtual const Shape* shapeCollidedWith(const Point& i_point) const = 0;
	virtual const Shape* shapeCollidedWith(const Shape& i_shape) const = 0;

protected:
	Description * mDesc;
};

#endif