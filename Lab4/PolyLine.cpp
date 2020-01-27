#include <cstring>
#include <cmath>

#include "PolyLine.h"

namespace lab4
{
	PolyLine::PolyLine()
		: mPointSize(0)
	{
		mPointList[0] = nullptr;
	}

	PolyLine::PolyLine(const PolyLine& other)
		: mPointSize(other.mPointSize)
	{
		mPointList[0] = nullptr;
		if (mPointSize == 0)
		{
			return;
		}

		// mPointList의 각 요소가 가리키는 Point를 모두 복사
		for (size_t i = 0; i != mPointSize; ++i)
		{
			mPointList[i] = new Point(*(other.mPointList[i]));
		}
	}

	PolyLine::~PolyLine()
	{
		for (size_t i = 0; i != mPointSize; ++i)
		{
			deletePoint(i);
		}
	}

	bool PolyLine::AddPoint(float x, float y)
	{
		if (mPointSize > 9)
		{
			return false;
		}

		mPointList[mPointSize] = new Point(x, y);
		if (mPointList[mPointSize] == nullptr)
		{
			return false;
		}

		++mPointSize;

		return true;
	}

	bool PolyLine::AddPoint(const Point* point)
	{
		if (mPointSize > 9)
		{
			return false;
		}

		if (point == nullptr)
		{
			return false;
		}

		mPointList[mPointSize] = point;
		++mPointSize;

		return true;
	}

	bool PolyLine::RemovePoint(unsigned int i)
	{
		if (i >= mPointSize)
		{
			return false;
		}

		if (mPointList[i] == nullptr)
		{
			return false;
		}

		deletePoint(i);
		--mPointSize;

		// i+1 객체부터 한칸씩 당김
		// 그리고 마지막 객체에 nullptr 저장
		for (; i != mPointSize; ++i)
		{
			mPointList[i] = mPointList[i + 1];
		}
		
		// 마지막 객체를 삭제하면 옮긴 객체도 삭제되기 때문에 단순히 nullptr로 만듦
		mPointList[mPointSize] = nullptr;

		return true;
	}

	bool PolyLine::TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const
	{
		// mPointList의 점들 중 가장 작은 x와 y => outMin
		// mPointList의 점들 중 가장 큰   x와 y => outMax

		// 점이 1개 이하면 만들 수 없음.
		if (mPointSize < 2)
		{
			return false;
		}

		float minX = mPointList[0]->GetX();
		float minY = mPointList[0]->GetY();
		float maxX = minX;
		float maxY = minY;

		for (size_t i = 1; i != mPointSize; ++i)
		{
			minX = fmin(minX, mPointList[i]->GetX());
			minY = fmin(minY, mPointList[i]->GetY());
			maxX = fmax(maxX, mPointList[i]->GetX());
			maxY = fmax(maxY, mPointList[i]->GetY());
		}

		if (minX == 0.0f && minY == 0.0f && maxX == 0.0f && maxY == 0.0f)
		{
			outMin->setX(0.0f);
			outMin->setY(0.0f);
			outMax->setX(0.0f);
			outMax->setY(0.0f);

			return true;
		}

		if (minX == maxX || minY == maxY)
		{
			return false;
		}

		outMin->setX(minX);
		outMin->setY(minY);
		outMax->setX(maxX);
		outMax->setY(maxY);

		return true;
	}

	PolyLine& PolyLine::operator=(const PolyLine& rhs)
	{
		// PolyLine pl1;
		// pl1 = pl2;
		if (this == &rhs)
		{
			return *this;
		}

		if (mPointSize != 0)
		{
			for (size_t i = 0; i != mPointSize; ++i)
			{
				deletePoint(i);
			}
		}

		mPointSize = rhs.mPointSize;

		for (size_t i = 0; i != mPointSize; ++i)
		{
			mPointList[i] = new Point(*(rhs.mPointList[i]));
		}

		return *this;
	}


	const Point* PolyLine::operator[](unsigned int i) const
	{
		if (i >= mPointSize)
		{
			return NULL;
		}

		return mPointList[i];
	}

	/*
		private 함수
	*/

	void PolyLine::deletePoint(unsigned int i)
	{
		delete mPointList[i];
	}
}