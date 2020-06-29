#include <math.h>
#include "Vector2.h"
//using namespace pl;

//namespace pl {

Vector2::Vector2(float value = 0.0f):
	Vector2(value, value)
{}

Vector2::Vector2(float x, float y):
	mX{ x }, mY{ y }
{}

Vector2 Vector2::operator+(Vector2 const & vec){
	return Vector2(mX+ vec.mX, mY + vec.mY);
}

Vector2 Vector2::operator-(Vector2 const & vec){
	return Vector2(mX - vec.mX, mY - vec.mY);
}

Vector2 Vector2::operator*(float value){
	return Vector2( mX * value, mY * value);
}

Vector2 Vector2::operator/(float value){
	return Vector2(mX / value, mY / value);
}

bool Vector2::operator<(Vector2 const & vec) const{
	return mag() < vec.mag();
}

bool Vector2::operator>(Vector2 const & vec) const{
	return mX == vec.mX && mY == vec.mY;
	//return mag() > vec.mag();
}

bool Vector2::operator==(Vector2 const & vec) const{
	return mag() == vec.mag();
}

Vector2 & operator+=(Vector2 & left, const Vector2 & right){
	left.rx() += right.x();
	left.ry() += right.y();
	return left;
}

Vector2 & operator-=(Vector2 & left, const Vector2 & right){
	left.rx() -= right.x();
	left.ry() -= right.y();
	return left;
}

Vector2 operator+(const Vector2 & left, const Vector2 & right){
	Vector2 vec(left.x() + right.x(), left.y() + right.y());
	return vec;
}

Vector2 operator-(const Vector2 & left, const Vector2 & right){
	Vector2 vec(left.x() - right.x(), left.y() - right.y());
	return vec;
}

Vector2 operator*(const Vector2 & left, float right){
	Vector2 vec(left.x() * right, left.y() * right);
	return vec;
}

Vector2 operator*(float left, const Vector2 & right){
	Vector2 vec(right.x() * left, right.y() * left);
	return vec;
}

Vector2 & operator*=(Vector2 & left, float right){
	left.rx() *= right;
	left.ry() *= right;
	return left;
}

Vector2 operator/(const Vector2 & left, float right){
	Vector2 vec(left.x() / right , left.y() / right);
	return vec;
}

Vector2 & operator/=(Vector2 & left, float right){
	left.rx() /= right;
	left.ry() /= right;
	return left;
}

bool operator==(const Vector2 & left, const Vector2 & right){
	//TODO: Implement
	return false;
}

bool operator!=(const Vector2 & left, const Vector2 & right){
	//TODO: Implement
	return true;
}

float Vector2::x() const
{
	return mX;
}

float Vector2::y() const
{
	return mY;
}

float & Vector2::rx()
{
	return mX;
}

float & Vector2::ry()
{
	return mY;
}

void Vector2::setX(float x)
{
	mX = x;
}

void Vector2::setY(float y)
{
	mY = y;
}

void Vector2::setXY(float x, float y)
{
	setX(x);
	setY(y);
}

Vector2 Vector2::unitV() const
{
	float m = norm();
	return Vector2(mX/m, mY/m);
}

float Vector2::norm() const
{
	return sqrt(mX*mX + mY * mY);
}

float Vector2::mag() const{ return norm(); }

float Vector2::length() const{ return norm(); }

//Static methods
Vector2 Vector2::Zero()
{
	return Vector2(0.000f, 0.000f);
}

Vector2 Vector2::I()
{
	return Vector2(1.000f, 0.000f);
}

Vector2 Vector2::J()
{
	return Vector2(0.000f, 1.000f);
}

//}//Namespace pl