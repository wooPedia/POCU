#include <cmath>

#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount) {}

	// Airplane+Boat & Boat+Airplane�� ���� �������Դϴ�.
	Boatplane::Boatplane(Airplane* a, Boat* b)
		: Vehicle(*a, *b)
	{
		size_t j = 0;

		// a�� b�� ž�°��� ���ʴ�� Boatplane���� ����ž�ϴ�.
		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			if (i < a->GetPassengersCount())
			{
				mPassengerList[i] = new Person(*(a->mPassengerList[i]));
			}
			else
			{
				mPassengerList[i] = new Person(*(b->mPassengerList[j]));
				++j;
			}
		}
		
		// a�� b�� ž�°� ����Ʈ�� �����մϴ�.
		a->deletePassengerList();
		b->deletePassengerList();
	}

	Boatplane::~Boatplane() {}

	unsigned int Boatplane::GetMaxSpeed() const
	{
		unsigned int flySpeed = GetFlySpeed();
		unsigned int sailSpeed = GetSailSpeed();

		return (flySpeed > sailSpeed) ? flySpeed : sailSpeed;
	}

	unsigned int Boatplane::GetFlySpeed() const
	{
		double speed = 150 * exp((500 - static_cast<int>(mPassengersWeightSum)) / 300.0);

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return static_cast<unsigned int>(speed);
		}
		else
		{
			return static_cast<unsigned int>(speed + 1);
		}
	}

	unsigned int Boatplane::GetSailSpeed() const
	{
		double speed = 800 - 1.7 * mPassengersWeightSum;
		
		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return (speed > 20) ? static_cast<unsigned int>(speed) : 20;
		}
		else
		{
			return (speed > 20) ? static_cast<unsigned int>(speed + 1) : 20;
		}
	}

	void Boatplane::Move()
	{
		// Boatplane: �� �� �̵� �� �� �� ���ϴ�.

		// ����� �����ٸ� �̵� �����մϴ�.
		if (mBreakCount == BOATPLANE)
		{
			mbMovable = true;
		}

		// �̵��� �� ���ٸ� break �մϴ�.
		if (!mbMovable)
		{
			++mBreakCount;
			assert(mBreakCount <= BOATPLANE);
		}
		else
		{
			mMovedDistanceKM += GetMaxSpeed();
			mBreakCount = 0;
			mbMovable = false;
		}
	}
}