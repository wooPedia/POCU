#include "Motorcycle.h"

namespace assignment2
{
	Motorcycle::Motorcycle()
		: Vehicle(2)
		, mMovedCount(0) {}

	Motorcycle::~Motorcycle() {}

	unsigned int Motorcycle::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	unsigned int Motorcycle::GetDriveSpeed() const
	{
		if (mPassengersWeightSum > 130)
		{
			return 0;
		}

		double speed = (2.0 * mPassengersWeightSum + 400) - pow(mPassengersWeightSum / 15.0, 3);

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return static_cast<unsigned int>(speed);
		}
		else
		{
			return static_cast<unsigned int>(speed + 1);
		}
	}

	void Motorcycle::Move()
	{
		// Motorcycle: �ټ� �� �̵� �� �� �� ���ϴ�.
		const size_t POSSIBLE_MOVE_COUNT = 5;

		// ����� �����ٸ� �̵� �����մϴ�.
		if (mBreakCount == MOTORCYCLE)
		{
			mMovedCount = 0;
			mbMovable = true;
		}

		// �̵��� �� ���ٸ� break �մϴ�.
		if (!mbMovable)
		{
			++mBreakCount;
			assert(mBreakCount <= MOTORCYCLE);
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