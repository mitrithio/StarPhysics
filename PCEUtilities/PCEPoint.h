#ifndef PCEPOINT_H
#define PCEPOINT_H

/*!
	\brief A simple Point class which contains x, y and z coordinates.
*/
class PCEPoint{

public:
	float mX;	/*!< the local X coordinate */
	float mY;	/*!< the local Y coordinate */
	float mZ;	/*!< the local Z coordinate */

	/*!
		\brief Redefinition of == operator.
	*/
	inline bool operator== (const PCEPoint& rvalue) const;
	
	/*!
		\brief Redefinition of != operator.
	*/
	inline bool operator!= (const PCEPoint& rvalue) const;
		
	/*!
		\brief Redefinition of = operator.
	*/
	PCEPoint& operator= (const PCEPoint& rvalue);
		
	PCEPoint(float i_x, float i_y, float i_z = 0)
		: mX(i_x)
		, mY(i_y)
		, mZ(i_z)
	{
	}

	/*! \return an array of the three coordinates */
	const float* getCoordinates() const;

};

#endif


