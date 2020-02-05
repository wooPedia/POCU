#pragma once

#include "RectangleLawn.h"

namespace lab5
{
	// ���簢������ ���� ����� �޽��ϴ�.
	class SquareLawn : public RectangleLawn
	{
	public:
		SquareLawn(size_t widthMeter);
		virtual ~SquareLawn();

		virtual unsigned int GetMinimumFencesCount() const;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const;
	};
}