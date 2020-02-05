#include "RectangleLawn.h"

namespace lab5
{
	RectangleLawn::RectangleLawn(size_t widthMeter, size_t heightMeter)
		: SquareLawn(widthMeter)
		, mHeightMeter(heightMeter) {}

	RectangleLawn::~RectangleLawn() {}

	unsigned int RectangleLawn::GetMinimumFencesCount() const
	{
		// 울타리 1개의 폭은 25cm == 0.25m
		const size_t FENCE_PER_METER = 4;
		return (mWidthMeter + mHeightMeter) * FENCE_PER_METER * 2;
	}
	unsigned int RectangleLawn::GetFencePrice(eFenceType fenceType) const
	{
		// fenceType은 1m당 가격이며 울타리 1개는 0.25m
		const size_t FENCE_PER_METER = 4;
		return static_cast<size_t>(
			(static_cast<double>(fenceType) / FENCE_PER_METER)* GetMinimumFencesCount()
			);
	}

	unsigned int RectangleLawn::GetArea() const
	{
		return mWidthMeter * mHeightMeter;
	}
}