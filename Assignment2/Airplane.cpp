#include <cmath>

#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount) {}

	Airplane::~Airplane() {}

	Boatplane Airplane::operator+(Boat& boat)
	{
		return Boatplane(this, &boat);
	}


	// ��� ���� �Լ�

	unsigned int Airplane::GetMaxSpeed() const
	{
		unsigned int driveSpeed = GetDriveSpeed();
		unsigned int flySpeed = GetFlySpeed();

		return (flySpeed > driveSpeed) ? flySpeed : driveSpeed;
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		double speed = 4 * exp((400 - mPassengersWeightSum) / static_cast<double>(70));

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
		double speed = 200 * exp((800 - mPassengersWeightSum) / static_cast<double>(500));

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
		// Airplane: �� �� �̵� �� �� �� ���ϴ�.

		// ����� �����ٸ� �̵� �����մϴ�.
		if (mBreakCount == AIRPLANE)
		{
			mbMovable = true;
		}

		// �̵��� �� ���ٸ� break �մϴ�.
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
}
