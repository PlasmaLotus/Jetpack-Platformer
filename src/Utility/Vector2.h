#ifndef __Vector2__
#define __Vector2__
//#include "Vector2.h"
//#include <SFML/Graphics.hpp>

//Vector of 2 floats

//namespace pl {

class Vector2
{
public:
	Vector2(float val);
	Vector2(float x, float y);
	//Vector2(const Vector2&vector);
	~Vector2() = default;

	///Default Basic assignment operator
	Vector2& operator=(Vector2 const& v) = default;

	///Default Move copy constructor
	Vector2& operator=(Vector2&& v) = default;

	/// Default lhs copy constructor
	Vector2(Vector2 const & v) = default;

	/// Default rhs copy constructor
	Vector2(Vector2&& p) = default;

	//operators
	//Overload of unary operator -
	//Vector2 operator- (const Vector2& right);
	
	/**
			Addition operator.
			Add the respective X and Y coordinates together.
		*/
	Vector2 operator+(Vector2 const & vec);

	/**
		Substraction operator.
		Substract the respective X and Y coordinates together.
	*/
	Vector2 operator-(Vector2 const & vec);

	/**
		Multiplication operator.
		Multiply both coordinates with the given value.
	*/
	Vector2 operator*(float value);

	/**
		Division operator.
		Divide both coordinates with the given value.
	*/
	Vector2 operator/(float value);

	/**
		Less Than comparison operator.
		Compare vectors based on magnitude, then x coord.
	*/
	bool operator<(Vector2 const & vec) const;

	/**
		Greater Than comparison operator.
		Compare vectors based on magnitude , then x coord.
	*/
	bool operator>(Vector2 const & vec) const;

	/**
		Equal comparison operator.
		Compare vector based on the magnitude x and y coordonates.
	*/
	bool operator==(Vector2 const & vec) const;


	float x() const;
	float y() const;

	//Ref to X value
	float& rx();
	//Ref to Y value
	float& ry();

	void setX(float x);
	void setY(float y);
	void setXY(float x, float y);
		

	//Vector coresponding to a direction of magnitude 1.0f
	Vector2 unitV() const ;

	//The length of the vector, The strait distance from 0,0 to x,y
	float norm() const;
	//The length of the vector, The strait distance from 0,0 to x,y
	float mag() const;
	//The length of the vector, The strait distance from 0,0 to x,y
	float length() const;

	static Vector2 Zero();
	static Vector2 I();
	static Vector2 J();

	/**
		Dot product or Scalar product 
	
	*/
	//float dot(Vector2 const & ve);
protected:
	float mX;
	float mY;
};

///Binary Vector operators

//Overload of binary operator +=.More...
Vector2& operator+= (Vector2& left, const Vector2& right);

//Overload of binary operator -=.More...
Vector2& operator-= (Vector2&left, const Vector2&right);

//Overload of binary operator +.More...
Vector2 operator+ (const Vector2&left, const Vector2&right);

//Overload of binary operator -.More...
Vector2 operator- (const Vector2 &left, const Vector2&right);

//Overload of binary operator *.More...
Vector2 operator* (const Vector2&left, float right);

//Overload of binary operator *.More...
Vector2 operator* (float left, const Vector2&right);

//Overload of binary operator *=.More...
Vector2& operator*= (Vector2 &left, float right);

//Overload of binary operator /.More...
Vector2 operator/ (const Vector2&left, float right);

//Overload of binary operator /=.More...
Vector2& operator/= (Vector2 &left, float right);

//Overload of binary operator ==.More...
//Not yet implemented
bool operator== (const Vector2&left, const Vector2 &right);

//Overload of binary operator !=.More...
//Not yet implemented
bool operator!= (const Vector2 &left, const Vector2 &right);

//}//Namespace pl


#endif // !__Vector2__

