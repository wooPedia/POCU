#include <cmath>

#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount) {}

	Airplane::~Airplane() {}

	unsigned int Airplane::GetMaxSpeed() const
	{
		unsigned int driveSpeed = GetDriveSpeed();
		unsigned int flySpeed = GetFlySpeed();

		return (flySpeed > driveSpeed) ? flySpeed : driveSpeed;
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		double speed = 4 * exp((400 - static_cast<int>(mPassengersWeightSum)) / 70.0);

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return static_cast<unsigned int>(speed);
		}
		else
		{
			return static_cast<unsigned int>(speed + 1);
		}
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		double speed = 200 * exp((800 - static_cast<int>(mPassengersWeightSum)) / 500.0);

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return static_cast<unsigned int>(speed);
		}
		else
		{
			return static_cast<unsigned int>(speed + 1);
		}
	}

	void Airplane::Move()
	{
		// Airplane: 한 번 이동 후 세 번 쉽니다.

		// 충분히 쉬었다면 이동 가능합니다.
		if (mBreakCount == AIRPLANE)
		{
			mbMovable = true;
		}

		// 이동할 수 없다면 break 합니다.
		if (!mbMovable)
		{
			++mBreakCount;
			assert(mBreakCount <= AIRPLANE);
		}
		else
		{
			mMovedDistanceKM += GetMaxSpeed();
			mBreakCount = 0;
			mbMovable = false;
		}
	}

	Boatplane Airplane::operator+(Boat& boat)
	{
		return Boatplane(this, &boat);
	}
}
