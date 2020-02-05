#pragma once

#include "SquareLawn.h"

namespace lab5
{
	// ���簢������ ���� ����� �޽��ϴ�.
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