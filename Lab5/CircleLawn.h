#pragma once

#include "Lawn.h"

namespace lab5
{
	class CircleLawn : public Lawn
	{
	public:
		CircleLawn(size_t radiusMeter);
		virtual ~CircleLawn();

		virtual unsigned int GetArea() const;

	private:
		size_t mRadiusMeter;
	};
}