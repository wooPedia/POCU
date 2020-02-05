#include <cmath>

#include "EquilateralTriangleLawn.h"

namespace lab5
{
	EquilateralTriangleLawn::EquilateralTriangleLawn(size_t oneSideMeter)
		: mOneSideMeter(oneSideMeter) {}

	EquilateralTriangleLawn::~EquilateralTriangleLawn() {}

	unsigned int EquilateralTriangleLawn::GetMinimumFencesCount() const
	{
		const size_t FENCE_PER_METER = 4;
		const size_t TRIANGLE_SIDE_COUNT = 3;

		return mOneSideMeter * FENCE_PER_METER * TRIANGLE_SIDE_COUNT;
	}

	unsigned int EquilateralTriangleLawn::GetFencePrice(eFenceType fenceType) const
	{
		const size_t FENCE_PER_METER = 4;
		return static_cast<size_t>(
			(static_cast<double>(fenceType) / FENCE_PER_METER) * GetMinimumFencesCount()
			);
	}

	unsigned int EquilateralTriangleLawn::GetArea() const
	{
		double area = (sqrt(3) / 4) * mOneSideMeter * mOneSideMeter;

		// ¹Ý¿Ã¸²
		if (static_cast<size_t>(area) == static_cast<size_t>(area + 0.5))
		{
			return static_cast<size_t>(area);
		}
		else
		{
			return static_cast<size_t>(area + 1);
		}
	}
}