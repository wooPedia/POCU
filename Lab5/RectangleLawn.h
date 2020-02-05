#pragma once

#include "IFenceable.h"
#include "Lawn.h"

namespace lab5
{
	class RectangleLawn : public IFenceable, public Lawn
	{
	public:
		RectangleLawn(size_t widthMeter, size_t heightMeter);
		virtual ~RectangleLawn();

		virtual unsigned int GetMinimumFencesCount() const;
		virtual unsigned int GetFencePrice(eFenceType fenceType) const;
		virtual unsigned int GetArea() const;

	protected:
		size_t mWidthMeter;
		size_t mHeightMeter;
	};
}