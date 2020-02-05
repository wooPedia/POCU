#include "CircleLawn.h"

namespace lab5
{
	CircleLawn::CircleLawn(size_t radiusMeter)
		: mRadiusMeter(radiusMeter) {}

	CircleLawn::~CircleLawn() {}

	unsigned int CircleLawn::GetArea() const
	{
		const double PI = 3.14;
		double area = static_cast<double>(mRadiusMeter)* mRadiusMeter* PI;

		// ¹Ý¿Ã¸²
		if (static_cast<size_t>(area) == static_cast<size_t>(area + 0.5))
		{
			return static_cast<size_t>(area);
		}
		else
		{
			return static_cast<size_t>(area + 1);
		}
	}
}