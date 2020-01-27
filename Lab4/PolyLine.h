#pragma once

#include "Point.h"

namespace lab4
{
	class PolyLine
	{
	public:
		PolyLine();
		PolyLine(const PolyLine& other);
		~PolyLine();

		bool AddPoint(float x, float y);
		bool AddPoint(const Point* point);
		bool RemovePoint(unsigned int i);
		bool TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const;

		PolyLine& operator=(const PolyLine& rhs);
		const Point* operator[](unsigned int i) const;

	private:
		inline void deletePoint(unsigned int i);

		const Point* mPointList[10];
		size_t mPointSize;
	};
}