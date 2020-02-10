#include <cmath>

#include "UBoat.h"

namespace assignment2
{
	UBoat::UBoat()
		: Vehicle(50)
		, mMovedCount(0) {}

	UBoat::UBoat(const UBoat& other)
		: Vehicle(other)
		, mMovedCount(other.mMovedCount) {}

	UBoat::~UBoat() {}

	unsigned int UBoat::GetMaxSpeed() const
	{
		unsigned int sailSpeed = GetSailSpeed();
		unsigned int diveSpeed = GetDiveSpeed();

		return (sailSpeed > diveSpeed) ? sailSpeed : diveSpeed;
	}

	unsigned int UBoat::GetSailSpeed() const
	{
		double speed = 550 - mPassengersWeightSum / 10.0;

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return (speed > 200) ? static_cast<unsigned int>(speed) : 200;
		}
		else
		{
			return (speed > 200) ? static_cast<unsigned int>(speed + 1) : 200;
		}
	}

	unsigned int UBoat::GetDiveSpeed() const
	{
		double speed = 500 * log((mPassengersWeightSum + 150.0) / 150) + 30;

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return static_cast<unsigned int>(speed);
		}
		else
		{
			return static_cast<unsigned int>(speed + 1);
		}
	}

	void UBoat::Move()
	{
		// UBoat: �� �� �̵� �� �� �� ���ϴ�.
		const size_t POSSIBLE_MOVE_COUNT = 2;

		// ����� �����ٸ� �̵� �����մϴ�.
		if (mBreakCount == UBOAT)
		{
			mMovedCount = 0;
			mbMovable = true;
		}

		// �̵��� �� ���ٸ� break �մϴ�.
		if (!mbMovable)
		{
			++mBreakCount;
			assert(mBreakCount <= UBOAT);
		}
		else
		{
			mMovedDistanceKM += GetMaxSpeed();
			++mMovedCount;
			mBreakCount = 0;

			assert(mMovedCount <= POSSIBLE_MOVE_COUNT);

			// ����� �̵������� ����� �մϴ�.
			if (mMovedCount == POSSIBLE_MOVE_COUNT)
			{
				mbMovable = false;
			}
		}
	}
} // namespace