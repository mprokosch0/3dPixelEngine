#include "Vec3.hpp"

//operators------------------------------------------------

template<typename T>
Vec3<T> &Vec3<T>::operator=(Vec3<T> const &rhs)
{
	if (this == &rhs)
		return *this;
	this->_x = rhs._x;
	this->_y = rhs._y;
	this->_z = rhs._z;
	return *this;
}

template<typename T>
T &Vec3<T>::operator[](int index)
{
	if (index <= 0)
		return this->_x;
	else if (index == 1)
		return this->_y;
	return this->_z;
}

template<typename T>
bool Vec3<T>::operator==(Vec3<T> const &rhs) const
{
	return this->_x == rhs._x && this->_y == rhs._y && this->_z == rhs._z;
}

template<typename T>
bool Vec3<T>::operator!=(Vec3<T> const &rhs) const
{
	return !(*this == rhs);
}

template<typename T>
Vec3<T> &Vec3<T>::operator+=(Vec3<T> const &rhs)
{
	this->_x += rhs._x;
    this->_y += rhs._y;
	this->_z += rhs._z;
	return *this;
}

template<typename T>
Vec3<T> &Vec3<T>::operator+=(T rhs)
{
	this->_x += rhs;
    this->_y += rhs;
	this->_z += rhs;
	return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator+(Vec3<T> const &rhs) const
{
	return Vec3<T>(this->_x + rhs._x, this->_y + rhs._y, this->_z + rhs._z);
}

template<typename T>
Vec3<T> Vec3<T>::operator+(T rhs) const
{
	return Vec3<T>(this->_x + rhs, this->_y + rhs, this->_z + rhs);
}

template<typename T>
Vec3<T> &Vec3<T>::operator-=(Vec3<T> const &rhs)
{
	this->_x -= rhs._x;
    this->_y -= rhs._y;
	this->_z -= rhs._z;
	return *this;
}

template<typename T>
Vec3<T> &Vec3<T>::operator-=(T rhs)
{
	this->_x -= rhs;
    this->_y -= rhs;
	this->_z -= rhs;
	return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator-(Vec3<T> const &rhs) const
{
	return Vec3<T>(this->_x - rhs._x, this->_y - rhs._y, this->_z - rhs._z);
}

template<typename T>
Vec3<T> Vec3<T>::operator-(T rhs) const
{
	return Vec3<T>(this->_x - rhs, this->_y - rhs, this->_z - rhs);
}

template<typename T>
Vec3<T> &Vec3<T>::operator*=(Vec3<T> const &rhs)
{
	this->_x *= rhs._x;
    this->_y *= rhs._y;
	this->_z *= rhs._z;
	return *this;
}

template<typename T>
Vec3<T> &Vec3<T>::operator*=(T rhs)
{
	this->_x *= rhs;
    this->_y *= rhs;
	this->_z *= rhs;
	return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator*(Vec3<T> const &rhs) const
{
	return Vec3<T>(this->_x * rhs._x, this->_y * rhs._y, this->_z * rhs._z);
}

template<typename T>
Vec3<T> Vec3<T>::operator*(T rhs) const
{
	return Vec3<T>(this->_x * rhs, this->_y * rhs, this->_z * rhs);
}

template<typename T>
Vec3<T> &Vec3<T>::operator/=(Vec3<T> const &rhs)
{
	this->_x /= rhs._x;
    this->_y /= rhs._y;
	this->_z /= rhs._z;
	return *this;
}

template<typename T>
Vec3<T> &Vec3<T>::operator/=(T rhs)
{
	this->_x /= rhs;
    this->_y /= rhs;
	this->_z /= rhs;
	return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator/(Vec3<T> const &rhs) const
{
	return Vec3<T>(this->_x / rhs._x, this->_y / rhs._y, this->_z / rhs._z);
}

template<typename T>
Vec3<T> Vec3<T>::operator/(T rhs) const
{
	return Vec3<T>(this->_x / rhs, this->_y / rhs, this->_z / rhs);
}

//constructors/destructors---------------------------------

template<typename T>
Vec3<T>::Vec3(void): _x(0), _y(0), _z(0)
{}

template<typename T>
Vec3<T>::Vec3(T x, T y, T z): _x(x), _y(y), _z(z)
{}

template<typename T>
Vec3<T>::Vec3(Vec3<T> const &rhs): _x(rhs._x), _y(rhs._y), _z(rhs._z)
{}

template<typename T>
Vec3<T>::~Vec3(void)
{}

//Member functions-----------------------------------------

template<typename T>
T Vec3<T>::dot(Vec3<T> const &rhs) const
{
	return (this->_x * rhs._x + this->_y * rhs._y + this->_z * rhs._z);
}

template<typename T>
Vec3<T> Vec3<T>::cross(Vec3<T> const &rhs) const
{
	Vec3<T> res (this->_y * rhs._z - this->_z * rhs._y,
				 this->_z * rhs._x - this->_x * rhs._z,
				 this->_x * rhs._y - this->_y * rhs._x);
	return res;
}

template<typename T>
void Vec3<T>::normalize(void)
{
	T len = sqrt(this->_x*this->_x + this->_y*this->_y + this->_z*this->_z);
	if (len == 0)
		return ;
	*this /= len;
}

template<typename T>
Vec3<T> Vec3<T>::normalized(void)
{
	T len = sqrt(this->_x*this->_x + this->_y*this->_y + this->_z*this->_z);
	if (len == 0)
		return ;
	return Vec3<T>(*this / len);
}