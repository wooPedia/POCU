#pragma once

#include "IFlyable.h"
#include "ISailable.h"
#include "Vehicle.h"

namespace assignment2
{
	class Airplane;
	class Boat;

	class Boatplane : public Vehicle, public IFlyable, public ISailable
	{
	public:
		Boatplane(unsigned int maxPassengersCount);
		Boatplane(Airplane* a, Boat* b);
		Boatplane(const Boatplane& other);
		~Boatplane();

		virtual unsigned int GetMaxSpeed() const;
		virtual unsigned int GetFlySpeed() const;
		virtual unsigned int GetSailSpeed() const;
		virtual void Move();

		Boatplane& operator=(const Boatplane& rhs);
	};
}