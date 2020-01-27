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
		inline void SetX(float x);
		inline void SetY(float y);

		float mX;
		float mY;
	};

	void Point::SetX(float x)
	{
		mX = x;
	}

	void Point::SetY(float y)
	{
		mY = y;
	}
}