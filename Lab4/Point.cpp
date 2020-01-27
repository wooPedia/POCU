#include <iostream>

#include "Point.h"

namespace lab4
{
	Point::Point(float x, float y)
		: mX(x), mY(y)
	{
		if (x == NULL)
		{
			mX = 0.0f;
		}
		if (y == NULL)
		{
			mY = 0.0f;
		}
	}

	Point::Point(const Point& other)
		: mX(other.mX), mY(other.mY) {}

	Point::~Point() {}

	void Point::operator=(const Point& rhs)
	{
		// p1 = p2;
		if (this == &rhs)
		{
			return;
		}

		mX = rhs.mX;
		mY = rhs.mY;
	}

	Point Point::operator+(const Point& other) const
	{
		return Point(mX + other.mX, mY + other.mY);
	}

	Point Point::operator-(const Point& other) const
	{
		return Point(mX - other.mX, mY - other.mY);
	}

	float Point::Dot(const Point& other) const
	{
		return (mX * other.mX) + (mY * other.mY);
	}

	Point Point::operator*(float operand) const
	{
		return Point(mX * operand, mY * operand);
	}

	float Point::GetX() const
	{
		return mX;
	}

	float Point::GetY() const
	{
		return mY;
	}


	// friend ÇÔ¼ö (float * Point)
	Point operator*(float operand, const Point& rhs)
	{
		return Point::Point(operand * rhs.mX, operand * rhs.mY);
	}
}