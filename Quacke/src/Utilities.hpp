#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>

struct mVector3 {
	float x, y, z;
	float length;

	mVector3();
	mVector3(double value);
	mVector3(double X, double Y, double Z);
	mVector3(const mVector3& rhs);

	mVector3& operator+(const mVector3& rhs);
	mVector3& operator-(const mVector3& rhs);
	mVector3& operator*(const mVector3& rhs);
	mVector3& operator=(const mVector3& rhs);
	mVector3& operator+=(const mVector3& rhs);
	mVector3& operator-=(const mVector3& rhs);

	mVector3& operator*(float multiplier);
	mVector3& operator/(float divider);

	bool operator==(const mVector3& rhs);
	bool operator!=(const mVector3& rhs);


	friend std::ostream& operator<<(std::ostream& os, const mVector3& rhs);

	void calculateLength();

};

namespace mUtilities 
{
	const float PI = 3.1416f;

	double distance(const mVector3& pos0, const mVector3& pos1);
	mVector3 normalize(const mVector3& vector);
	mVector3 cross(const mVector3& vec0, const mVector3& vec1);
	double dot(mVector3 vec0, mVector3 vec1);
}




#endif // !UTILITIES_H