#include "Airplane.h"
#include "Boat.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
		, mMovedCount(0) {}

	Boat::~Boat() {}

	Boatplane Boat::operator+(Airplane& plane)
	{
		return Boatplane(&plane, this);
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
	}

	unsigned int Boat::GetSailSpeed() const
	{
		const unsigned int MAX_WEIGHT = 78;
		if (mPassengersWeightSum >= MAX_WEIGHT)
		{
			return 20;
		}

		unsigned int speed = 800 - 10 * mPassengersWeightSum;

		return (speed > 20) ? speed : 20;
	}

	void Boat::Move()
	{
		// Boat: �� �� �̵� �� �� �� ���ϴ�.
		const size_t POSSIBLE_MOVE_COUNT = 2;
		
		// ����� �����ٸ� �̵� �����մϴ�.
		if (mBreakCount == BOAT)
		{
			mMovedCount = 0;
			mbMovable = true;
		}

		// �̵��� �� ���ٸ� break �մϴ�.
		if (!mbMovable)
		{
			++mBreakCount;
			assert(mBreakCount <= BOAT);
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
}