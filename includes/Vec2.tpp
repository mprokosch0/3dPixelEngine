#include "Vec2.hpp"

//operators------------------------------------------------

template<typename T>
Vec2<T> &Vec2<T>::operator=(Vec2<T> const &rhs)
{
	if (this == &rhs)
		return *this;
	this->_x = rhs._x;
	this->_y = rhs._y;
	return *this;
}

template<typename T>
T &Vec2<T>::operator[](int index)
{
	if (index <= 0)
		return this->_x;
	return this->_y;
}

template<typename T>
bool Vec2<T>::operator==(Vec2<T> const &rhs) const
{
	return this->_x == rhs._x && this->_y == rhs._y;
}

template<typename T>
bool Vec2<T>::operator!=(Vec2<T> const &rhs) const
{
	return !(*this == rhs);
}

template<typename T>
Vec2<T> &Vec2<T>::operator+=(Vec2<T> const &rhs)
{
	this->_x += rhs._x;
    this->_y += rhs._y;
	return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator+=(T rhs)
{
	this->_x += rhs;
    this->_y += rhs;
	return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator+(Vec2<T> const &rhs) const
{
	return Vec2<T>(this->_x + rhs._x, this->_y + rhs._y);
}

template<typename T>
Vec2<T> Vec2<T>::operator+(T rhs) const
{
	return Vec2<T>(this->_x + rhs, this->_y + rhs);
}

template<typename T>
Vec2<T> &Vec2<T>::operator-=(Vec2<T> const &rhs)
{
	this->_x -= rhs._x;
    this->_y -= rhs._y;
	return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator-=(T rhs)
{
	this->_x -= rhs;
    this->_y -= rhs;
	return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator-(Vec2<T> const &rhs) const
{
	return Vec2<T>(this->_x - rhs._x, this->_y - rhs._y);
}

template<typename T>
Vec2<T> Vec2<T>::operator-(T rhs) const
{
	return Vec2<T>(this->_x - rhs, this->_y - rhs);
}

template<typename T>
Vec2<T> &Vec2<T>::operator*=(Vec2<T> const &rhs)
{
	this->_x *= rhs._x;
    this->_y *= rhs._y;
	return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator*=(T rhs)
{
	this->_x *= rhs;
    this->_y *= rhs;
	return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator*(Vec2<T> const &rhs) const
{
	return Vec2<T>(this->_x * rhs._x, this->_y * rhs._y);
}

template<typename T>
Vec2<T> Vec2<T>::operator*(T rhs) const
{
	return Vec2<T>(this->_x * rhs, this->_y * rhs);
}

template<typename T>
Vec2<T> &Vec2<T>::operator/=(Vec2<T> const &rhs)
{
	this->_x /= rhs._x;
    this->_y /= rhs._y;
	return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator/=(T rhs)
{
	this->_x /= rhs;
    this->_y /= rhs;
	return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator/(Vec2<T> const &rhs) const
{
	return Vec2<T>(this->_x / rhs._x, this->_y / rhs._y);
}

template<typename T>
Vec2<T> Vec2<T>::operator/(T rhs) const
{
	return Vec2<T>(this->_x / rhs, this->_y / rhs);
}

//constructors/destructors---------------------------------

template<typename T>
Vec2<T>::Vec2(void): _x(0), _y(0)
{}

template<typename T>
Vec2<T>::Vec2(T x, T y): _x(x), _y(y)
{}

template<typename T>
Vec2<T>::Vec2(Vec2<T> const &rhs): _x(rhs._x), _y(rhs._y)
{}

template<typename T>
Vec2<T>::~Vec2(void)
{}

//Member functions-----------------------------------------

template<typename T>
T Vec2<T>::dot(Vec2<T> const &rhs) const
{
	return (this->_x * rhs._x + this->_y * rhs._y);
}

template<typename T>
T Vec2<T>::cross(Vec2<T> const &rhs) const
{
	return (this->_x * rhs._y - this->_y * rhs._x);
}

template<typename T>
void Vec2<T>::normalize(void)
{
	T len = sqrt(this->_x*this->_x + this->_y*this->_y);
	if (len == 0)
		return ;
	*this /= len;
}

template<typename T>
Vec2<T> Vec2<T>::normalized(void)
{
	T len = sqrt(this->_x*this->_x + this->_y*this->_y);
	if (len == 0)
		return ;
	return Vec2<T>(*this / len);
}	