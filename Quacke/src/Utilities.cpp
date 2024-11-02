#include "Utilities.hpp"

mVector3::mVector3()
	:
	x(0.f),
	y(0.f),
	z(0.f),
	length(0)
{
	calculateLength();
}
mVector3::mVector3(float value)
	:
	x(value),
	y(value),
	z(value),
	length(0.)
{
	calculateLength();
}
mVector3::mVector3(float X, float Y, float Z)
	:
	x(X),
	y(Y),
	z(Z),
	length(0.f)
{
	calculateLength();
}
mVector3::mVector3(const mVector3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->length = rhs.length;
}
mVector3& mVector3::operator+(const mVector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	calculateLength();
	return *this;
}
mVector3& mVector3::operator-(const mVector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	calculateLength();
	return *this;
}
mVector3& mVector3::operator*(const mVector3& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	calculateLength();
	return *this;
}
mVector3& mVector3::operator=(const mVector3& rhs)
{
	if (this == &rhs)
		return *this;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	length = rhs.length;
	return *this;
}

mVector3& mVector3::operator+=(const mVector3& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	calculateLength();
	return *this;
}

mVector3& mVector3::operator-=(const mVector3& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	calculateLength();
	return *this;
}

mVector3& mVector3::operator*(float multiplier)
{
	x *= multiplier;
	y *= multiplier;
	z *= multiplier;
	calculateLength();
	return *this;
}

mVector3& mVector3::operator/(float divider)
{
	x /= divider;
	y /= divider;
	z /= divider;
	calculateLength();
	return *this;
}

bool mVector3::operator==(const mVector3& rhs)
{
	if (this->x == rhs.x && this->y == rhs.y && this->z == z)
		return true;
	return false;
}

bool mVector3::operator!=(const mVector3& rhs)
{
	if (this->x != rhs.x || this->y != rhs.y || this->z != z)
		return true;
	return false;
}

void mVector3::calculateLength()
{
	length = sqrt(x * x + y * y + z * z);
}

std::ostream& operator<<(std::ostream& os, const mVector3& rhs)
{
	os << "(" << rhs.x << "," << rhs.y << "," << rhs.z << ")";
	return os;
}

double mUtilities::distance(const mVector3& pos0, const mVector3& pos1)
{
	mVector3 tmp(pos0);
	tmp -= pos1;
	tmp.calculateLength();
	return tmp.length;
}

mVector3 mUtilities::normalize(const mVector3& vector)
{
	mVector3 tmp = vector;
	tmp.calculateLength();
	double vecLeng = tmp.length;
	tmp.x = vector.x / vecLeng;
	tmp.y = vector.y / vecLeng;
	tmp.z = vector.z / vecLeng;
	tmp.length = 1;
	return tmp;

}

mVector3 mUtilities::cross(const mVector3& vec0, const mVector3& vec1)
{
	mVector3 tmp;
	tmp.x = vec0.y * vec1.z - vec0.z * vec1.y;
	tmp.y = vec0.z * vec1.x - vec0.x * vec1.z;
	tmp.z = vec0.x * vec1.y - vec0.y * vec1.x;
	tmp.calculateLength();
	return tmp;
}

double mUtilities::dot(mVector3 vec0, mVector3 vec1)
{
	return vec0.x * vec1.x + vec0.y * vec1.y + vec0.z * vec1.z;
}
