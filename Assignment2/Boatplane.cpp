#include <cmath>

#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount) {}

	Boatplane::Boatplane(const Boatplane& other)
		: Vehicle(other)
	{
		for (size_t i = 0; i != mPassengersCount; ++i)
		{
			mPassengerList[i] = new Person(other.mPassengerList[i]->GetName().c_str(), other.mPassengerList[i]->GetWeight());
			assert(mPassengerList[i]->GetName() == other.mPassengerList[i]->GetName());
			assert(mPassengerList[i]->GetWeight() == other.mPassengerList[i]->GetWeight());
		}
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
		double speed = 150 * exp((500 - mPassengersWeightSum) / static_cast<double>(300));

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

	Boatplane& Boatplane::operator=(const Boatplane& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		assert(mPassengerList != nullptr);

		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			delete mPassengerList[i];
			mPassengerList[i] = nullptr;
		}

		// 최대 탑승객 수가 동일하다면 재할당할 필요가 없습니다.
		if (mMaxPassengersCount != rhs.mMaxPassengersCount)
		{
			delete[] mPassengerList;
			mPassengerList = nullptr;
		}

		// 멤버 변수 set
		mMaxPassengersCount = rhs.mMaxPassengersCount;
		mPassengersCount = rhs.mPassengersCount;
		mPassengersWeightSum = rhs.mPassengersWeightSum;
		mBreakCount = 0;
		mMovedDistanceKM = 0;

		// nullptr이 아닐 경우 메모리를 재할당하지 않습니다. 
		if (mPassengerList == nullptr)
		{
			mPassengerList = new const Person * [mMaxPassengersCount];
		}

		assert(mMaxPassengersCount >= mPassengersCount);
		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			mPassengerList[i] = new Person(rhs.mPassengerList[i]->GetName().c_str(), rhs.mPassengerList[i]->GetWeight());
			assert(mPassengerList[i]->GetName() == rhs.mPassengerList[i]->GetName());
			assert(mPassengerList[i]->GetWeight() == rhs.mPassengerList[i]->GetWeight());
		}

		return *this;
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