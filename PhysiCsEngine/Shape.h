#ifndef PCE_SHAPE_H
#define PCE_SHAPE_H

#include "..\PCEUtilities\PCEUtilities.h"
#include "ErrorDefinitions.h"

namespace PCEIds
{
	static const PCEObjectId DESC_BOUNDING_SPHERE("BoundingSphereDesc");
	static const PCEObjectId DESC_PLANE("PlaneDesc");

	static const PCEObjectId TYPE_COLLIDER("TypeCollider");
}


/*!
	\brief A Shape is a description of bounds of an object.
*/
class Shape{
public:
	/*!
	\brief Default constructor. It sets nullptr to m_desc.
	*/
	Shape(const PCEObjectId& i_desc = INVALID_OBJECT_ID, const PCEObjectId& i_type = INVALID_OBJECT_ID, unsigned int i_capacity = 0)
		: m_desc(i_desc)
		, m_type(i_type)
		, m_subShapes(i_capacity)
	{}

	virtual ~Shape(){};

	/*!
	\brief Getter for m_desc
	\return m_desc
	*/
	inline const PCEObjectId& getDescription() const			{return m_desc;}
	
	/*!
	\brief Getter for m_type
	\return m_type
	*/
	inline const PCEObjectId& getDescriptionType() const	{return m_type;}

	/*!
	\brief Adds a Shape to mpSubShapes array. If mpSubShapes array is full, it adds some space copying the array in a new memory fragment, deleting old memory allocated.
	\param [in] i_subShape The Shape to add.
	*/
	virtual void addSubShape(Shape& i_subShape);

	/*!
	\brief Adds an array of pointer to shape to mpSubShapes array. If mpSubShapes array is full, it adds some space copying the array in a new memory fragment, deleting old memory allocated.
	\param [in] i_subShapeVector The array of pointer to shape to add.
	*/
	virtual void addSubShape(const PCEVector<Shape *>& i_subShapeVector);

	/*!
	\brief Getter for mpSubShapes attribute.
	\return A pointer to the sub shapes' vector.
	*/
	inline const PCEVector<Shape*>& getSubShapes() const		{return m_subShapes;}

protected:
	PCEObjectId m_desc;				/*!< \brief The description name of shape. */
	PCEObjectId m_type;			/*!< \brief The description type of shape. */
										
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

	Collider(const PCEObjectId& i_desc = INVALID_OBJECT_ID, unsigned int i_capacity = 0)
		: Shape(i_desc, PCEIds::TYPE_COLLIDER, i_capacity)
	{}

	/*!
	\brief Check for collision.
	\param [in] i_point The point where collision could be.
	\return The distance between this collider and the point.
	*/
	virtual double CheckCollisionWith(const PCEVector3D& i_point) const = 0;

	/*!
	\brief Check for collision.
	\param [in] i_collider The Shape that could be involved in collision with this Shape.
	\return The distance between this collider and the other.
	*/
	virtual double CheckCollisionWith(const Collider& i_collider) const = 0;
};

class Mesh : public Shape
{
public:

	virtual void drawShape() = 0;
};

#endif