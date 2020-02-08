#pragma once

#include "Boatplane.h"
#include "ISailable.h"
#include "Vehicle.h"

namespace assignment2
{
	class Airplane;

	class Boat : public Vehicle, public ISailable
	{
	public:
		Boat(unsigned int maxPassengersCount);
		~Boat();

		virtual unsigned int GetMaxSpeed() const;
		virtual unsigned int GetSailSpeed() const;
		virtual void Move();

		Boatplane operator+(Airplane& plane);

	private:
		unsigned int mMovedCount;
	};
}