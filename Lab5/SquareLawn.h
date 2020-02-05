#pragma once

#include "IFenceable.h"
#include "Lawn.h"

namespace lab5
{
	class SquareLawn : public IFenceable, public Lawn
	{
	public:
		SquareLawn(size_t widthMeter);
		virtual ~SquareLawn();

		virtual unsigned int GetMinimumFencesCount() const;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const;
		virtual unsigned int GetArea() const;

	protected:
		size_t mWidthMeter;
	};
}