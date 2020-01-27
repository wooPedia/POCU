#pragma once

namespace lab4
{
	class Point
	{
		friend class PolyLine;
		friend Point operator*(float operand, const Point& rhs);
	public:
		Point(float x, float y);
		Point(const Point& other);
		~Point();

		void operator=(const Point& other);
		Point operator+(const Point& other) const;
		Point operator-(const Point& other) const;
		float Dot(const Point& other) const;
		Point operator*(float operand) const;

		float GetX() const;
		float GetY() const;

	private:
		inline void setX(float x);
		inline void setY(float y);

		float mX;
		float mY;
	};

	void Point::setX(float x)
	{
		mX = x;
	}

	void Point::setY(float y)
	{
		mY = y;
	}
}