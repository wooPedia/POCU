#pragma once

#include "RectangleLawn.h"

namespace lab5
{
	// 직사각형으로 부터 상속을 받습니다.
	class SquareLawn : public RectangleLawn
	{
	public:
		SquareLawn(size_t widthMeter);
		virtual ~SquareLawn();

		virtual unsigned int GetMinimumFencesCount() const;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const;
	};
}