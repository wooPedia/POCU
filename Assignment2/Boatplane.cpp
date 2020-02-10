#include <cmath>

#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount) {}

	// Airplane+Boat & Boat+Airplane을 위한 생성자입니다.
	Boatplane::Boatplane(Airplane* a, Boat* b)
		: Vehicle(*a, *b)
	{
		size_t j = 0;

		// a와 b의 탑승객이 차례대로 Boatplane으로 갈아탑니다.
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
		
		// a와 b의 탑승객 리스트를 제거합니다.
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
		// Boatplane: 한 번 이동 후 세 번 쉽니다.

		// 충분히 쉬었다면 이동 가능합니다.
		if (mBreakCount == BOATPLANE)
		{
			mbMovable = true;
		}

		// 이동할 수 없다면 break 합니다.
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