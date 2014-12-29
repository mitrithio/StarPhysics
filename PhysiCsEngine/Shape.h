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
	\brief Default constructor.
	*/
	Shape(const PCEObjectId& i_desc = INVALID_OBJECT_ID, const PCEObjectId& i_type = INVALID_OBJECT_ID)
		: m_desc(i_desc)
		, m_type(i_type)
		, m_vSubShapes()
	{}

	virtual ~Shape(){};

	/*!
	\brief Getter for m_desc
	\return m_desc
	*/
	inline const PCEObjectId& GetDescription() const			{return m_desc;}
	
	/*!
	\brief Getter for m_type
	\return m_type
	*/
	inline const PCEObjectId& GetType() const	{return m_type;}

	/*!
	\brief Adds a Shape to mpSubShapes array. If mpSubShapes array is full, it adds some space copying the array in a new memory fragment, deleting old memory allocated.
	\param [in] i_subShape The Shape to add.
	*/
	void AddSubShape(Shape& i_subShape);

	/*!
	\brief Adds an array of pointer to shape to mpSubShapes array. If mpSubShapes array is full, it adds some space copying the array in a new memory fragment, deleting old memory allocated.
	\param [in] i_subShapeVector The array of pointer to shape to add.
	*/
	void AddSubShape(const PCEVector<Shape*>& i_subShapeVector);

	/*!
	\brief Getter for mpSubShapes attribute.
	\return A pointer to the sub shapes' vector.
	*/
	inline const PCEVector<Shape*>& GetSubShapes() const		{return m_vSubShapes;}

private:
	PCEObjectId		  m_desc;			/*!< \brief The description name of shape. */
	PCEObjectId		  m_type;			/*!< \brief The description type of shape. */
										
	PCEVector<Shape*> m_vSubShapes;		/*!< \brief A PCEVector of Shape.*/
};

class Collider : public Shape
{
public:

	Collider(const PCEObjectId& i_desc = INVALID_OBJECT_ID)
		: Shape(i_desc, PCEIds::TYPE_COLLIDER)
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