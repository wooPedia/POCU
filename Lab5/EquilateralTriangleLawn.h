#pragma once

#include "IFenceable.h"
#include "Lawn.h"

namespace lab5
{
	class EquilateralTriangleLawn : public IFenceable, public Lawn
	{
	public:
		EquilateralTriangleLawn(size_t oneSideMeter);
		virtual ~EquilateralTriangleLawn();

		virtual unsigned int GetMinimumFencesCount() const;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const;
		virtual unsigned int GetArea() const;

	private:
		size_t mOneSideMeter;
	};
}