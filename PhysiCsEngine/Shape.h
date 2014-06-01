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
	\brief Default constructor. It sets nullptr to m_desc.
	*/
	Shape(const EnumShapeDesc i_desc = ESD_NONE, const EnumShapeDescType i_type = ESDT_NONE, unsigned int i_capacity = 0)
		: m_desc(i_desc)
		, m_type(i_type)
		, m_subShapes(i_capacity)
	{}

	virtual ~Shape(){};

	/*!
	\brief Getter for m_desc
	\return m_desc
	*/
	inline const EnumShapeDesc getDescription() const			{return m_desc;}
	
	/*!
	\brief Getter for m_type
	\return m_type
	*/
	inline const EnumShapeDescType getDescriptionType() const	{return m_type;}

	/*!
	\brief Adds a Shape to mpSubShapes array. If mpSubShapes array is full, it adds some space copying the array in a new memory fragment, deleting old memory allocated.
	\param [in] i_subShapeArray The Shape to add.
	*/
	virtual void addSubShape(Shape &i_subShapeArray);

	virtual void addSubShape(const PCEVector<Shape *>& i_subShapeVector);

	virtual void addSubShape(Shape** i_subShapeArray, const unsigned int i_numberOfElements);

	/*!
	\brief Getter for mpSubShapes attribute.
	\return A pointer to the sub shapes' vector.
	*/
	inline const PCEVector<Shape*>& getSubShapes() const		{return m_subShapes;}

// 	virtual bool operator==(const Shape& rvalue) const;
// 	virtual bool operator!=(const Shape& rvalue) const;
// 	virtual Shape& operator=(const Shape& rvalue);

protected:
	EnumShapeDesc m_desc;				/*!< \brief The description name of shape. */
	EnumShapeDescType m_type;			/*!< \brief The description type of shape. */
										
	PCEVector<Shape*> m_subShapes;		/*!< \brief A PCEVector of Shape.*/

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
	virtual const bool shapeCollidedWith(const PCEPoint &i_point,  const Collider * o_shapeCollided) const = 0;

	/*!
	\brief Check for collision.
	\param [in] i_shape The Shape that could be involved in collision with this Shape.
	\param [out] o_shapeCollided The Collider actually collided with input shape.
	\return This Shape or a subShape that are involved in collision with i_shape. 
			nullptr if neither shape and its sub shapes are involved in collision.
	*/
	virtual const bool shapeCollidedWith(const Collider * i_shape, const Collider * o_shapeCollided) const = 0;
};

class Mesh : public Shape
{

};

#endif