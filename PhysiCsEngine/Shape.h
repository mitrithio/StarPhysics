#ifndef PCE_SHAPE_H
#define PCE_SHAPE_H

#include "..\PCEUtilities\PCEUtilities.h"
#include "EnumDefinitions.h"
#include "ErrorDefinitions.h"

/*!
	A Shape is a description of bounds of an object.
*/
class Shape{
public:
	/*!
	\brief Default constructor. It sets nullptr to mDesc.
	*/
	Shape(const EnumShapeDesc i_desc = ESD_NONE, const EnumShapeDescType i_type = ESDT_NONE, unsigned int i_capacity = 0)
		: mDesc(i_desc)
		, mType(i_type)
		, mSubShapes(i_capacity)
	{}

	/*!
	\brief Getter for mDesc
	\return mDesc
	*/
	inline const EnumShapeDesc getDescription() const			{return mDesc;}
	
	/*!
	\brief Getter for mType
	\return mType
	*/
	inline const EnumShapeDescType getDescriptionType() const	{return mType;}

	/*!
	\brief Setter for initial capacity of sub shapes' array.
	\param [in] i_numberOfSubShapes The number of initial capacity.
	*/
	void setSubShapesInitialCapacity(unsigned int i_numberOfSubShapes);

	/*!
	\brief Adds a Shape to mpSubShapes array. If mpSubShapes array is full, it adds some space copying the array in a new memory fragment, deleting old memory allocated.
	\param [in] i_subShape The Shape to add.
	*/
	virtual void addSubShape(Shape &i_subShape);

	/*!
	\brief Adds a Shape to mpSubShapes array. If mpSubShapes array is full, it adds some space copying the array in a new memory fragment, deleting old memory allocated.
	\param [in] i_subShapes The pointer to first Shape to add.
	\param [in] i_numberOfSubShapes The length of the array.
	*/
	virtual void addSubShapeArray(Shape* i_subShapes, unsigned int i_numberOfSubShapes);

	/*!
	\brief Getter for mpSubShapes attribute.
	\return A pointer to the sub shapes' vector.
	*/
	inline const PCEVector<Shape*>& getSubShapes() const		{return mSubShapes;}
	
	/*!
	\brief Getter for mCountSubShapes attribute
	\return The number of sub shapes used.
	*/
	inline const size_t getSubShapesCount() const	{return mSubShapes.size();}

	/*!
	\brief Getter for mSubShapesCapacity attribute
	\return The number of sub shapes used.
	*/
	inline const size_t getSubShapesCapacity() const	{return mSubShapes.capacity();}

	virtual bool operator==(const Shape& rvalue) const = 0;
	virtual bool operator!=(const Shape& rvalue) const = 0;
	virtual const Shape& operator=(const Shape& rvalue) = 0;

protected:
	EnumShapeDesc mDesc;				/*!< \brief The description name of shape. */
	EnumShapeDescType mType;			/*!< \brief The description type of shape. */
										
	PCEVector<Shape*> mSubShapes;		/*!< \brief A PCEVector of Shape.*/

private:
	/*!
	\brief Adds i_value capacity to capacity of sub shapes' array.
	\param [in] i_value The number of augmented capacity.
	\return A PCE_ERROR: PCE_OK if the operation went well, PCE_CAPACITY if memory if full.
	*/
	void addCapacity(unsigned int i_value);
};

class Collider : public Shape
{
public:

	Collider(const EnumShapeDesc i_desc = ESD_NONE, unsigned int i_capacity = 0)
		: Shape(i_desc, ESDT_COLLIDER, i_capacity)
	{}



	/*!
	\brief Check for collision.
	\param [in] i_point The point where collision could be.
	\return This Shape or a subShape that are involved in collision with i_shape. 
			nullptr if neither shape and its sub shapes are involved in collision.
	*/
	virtual const Collider* shapeCollidedWith(const PCEPoint& i_point) const = 0;

	/*!
	\brief Check for collision.
	\param [in] i_shape The Shape that could be involved in collision with this Shape.
	\return This Shape or a subShape that are involved in collision with i_shape. 
			nullptr if neither shape and its sub shapes are involved in collision.
	*/
	virtual const Collider* shapeCollidedWith(const Collider& i_shape) const = 0;
};

class Mesh : public Shape
{

};

#endif