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
		// Boat b;
		// Airplane a;
		// Boatplane bp = b + a;

		unsigned int newMaxPC = mMaxPassengersCount + plane.GetMaxPassengersCount();
		unsigned int boatPC = mPassengersCount;
		unsigned int apPC = plane.GetPassengersCount();

		Boatplane bp(newMaxPC);
		size_t j = 0;
		for (size_t i = 0; i != apPC + boatPC; ++i)
		{
			if (i < apPC)
			{
				bp.AddPassenger(new Person(plane.GetPassenger(i)->GetName().c_str(), plane.GetPassenger(i)->GetWeight()));
			}
			else
			{
				bp.AddPassenger(new Person(mPassengerList[j]->GetName().c_str(), mPassengerList[j]->GetWeight()));
				++j;
			}
		}

		this->~Boat();
		plane.~Airplane();

		return bp;
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
		// Boat: 두 번 이동 후 한 번 쉽니다.
		const size_t POSSIBLE_MOVE_COUNT = 2;
		
		// 충분히 쉬었다면 이동 가능합니다.
		if (mBreakCount == BOAT)
		{
			mMovedCount = 0;
			mbMovable = true;
		}

		// 이동할 수 없다면 break 합니다.
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

			// 충분히 이동했으면 쉬어야 합니다.
			if (mMovedCount == POSSIBLE_MOVE_COUNT)
			{
				mbMovable = false;
			}
		}
	}
}