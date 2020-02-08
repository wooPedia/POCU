#pragma once

#include "Boatplane.h"
#include "IDrivable.h"
#include "IFlyable.h"
#include "Vehicle.h"

namespace assignment2
{
	class Boat;

	class Airplane : public Vehicle, public IDrivable, public IFlyable
	{
	public:
		Airplane(unsigned int maxPassengersCount);
		Airplane(const Airplane& other);
		~Airplane();
		
		virtual unsigned int GetMaxSpeed() const;
		virtual unsigned int GetDriveSpeed() const;
		virtual unsigned int GetFlySpeed() const;
		virtual void Move();

		Boatplane operator+(Boat& boat);
		Airplane& operator=(const Airplane& rhs);
	};
}