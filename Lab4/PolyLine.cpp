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

		// mPointList�� �� ��Ұ� ����Ű�� Point�� ��� ����
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

		// i+1 ��ü���� ��ĭ�� ���
		for (; i != mPointSize; ++i)
		{
			mPointList[i] = mPointList[i + 1];
		}

		// ������ ��ü�� �����ϸ� �ű� ��ü�� �����Ǳ� ������ �ܼ��� nullptr�� ����
		mPointList[mPointSize] = nullptr;

		return true;
	}

	bool PolyLine::TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const
	{
		// ���� 0���� �ּ� ��� �簢���� ������ �� �����ϴ�.
		if (mPointSize == 0)
		{
			return false;
		}

		float minX = mPointList[0]->GetX();
		float minY = mPointList[0]->GetY();
		float maxX = minX;
		float maxY = minY;

		// �ּ� ��� '�簢��'������ ���������� �ƴ� ���α׷��� �� ������ �������� �ʺ� 0�̴��� ���������� ���� �մϴ�.
		for (size_t i = 1; i != mPointSize; ++i)
		{
			minX = fmin(minX, mPointList[i]->GetX());
			minY = fmin(minY, mPointList[i]->GetY());
			maxX = fmax(maxX, mPointList[i]->GetX());
			maxY = fmax(maxY, mPointList[i]->GetY());
		}

		outMin->setX(minX);
		outMin->setY(minY);
		outMax->setX(maxX);
		outMax->setY(maxY);

		return true;
	}

	PolyLine& PolyLine::operator=(const PolyLine& rhs)
	{
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
		private �Լ�
	*/

	void PolyLine::deletePoint(unsigned int i)
	{
		delete mPointList[i];
	}
}