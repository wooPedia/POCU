#pragma once

#include "SquareLawn.h"

namespace lab5
{
	// 정사각형으로 부터 상속을 받습니다.
	class RectangleLawn : public SquareLawn
	{
	public:
		RectangleLawn(size_t widthMeter, size_t heightMeter);
		virtual ~RectangleLawn();

		virtual unsigned int GetMinimumFencesCount() const;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const;
		virtual unsigned int GetArea() const;

	private:
		size_t mHeightMeter;
	};
}