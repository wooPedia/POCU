#include "SquareLawn.h"

namespace lab5
{
	SquareLawn::SquareLawn(size_t widthMeter)
		: mWidthMeter(widthMeter) {}

	SquareLawn::~SquareLawn() {}

	unsigned int SquareLawn::GetMinimumFencesCount() const
	{
		const size_t FENCE_PER_METER = 4;
		return (mWidthMeter + mWidthMeter) * FENCE_PER_METER * 2;
	}

	unsigned int SquareLawn::GetFencePrice(eFenceType fenceType) const
	{
		const size_t FENCE_PER_METER = 4;
		return static_cast<size_t>(
			(static_cast<double>(fenceType) / FENCE_PER_METER)* GetMinimumFencesCount()
			);
	}

	unsigned int SquareLawn::GetArea() const
	{
		return mWidthMeter * mWidthMeter;
	}
}