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

		// �ִ� ž�°� ���� �����ϴٸ� ���Ҵ��� �ʿ䰡 �����ϴ�.
		if (mMaxPassengersCount != rhs.mMaxPassengersCount)
		{
			delete[] mPassengerList;
			mPassengerList = nullptr;
		}

		// ��� ���� set
		mMaxPassengersCount = rhs.mMaxPassengersCount;
		mPassengersCount = rhs.mPassengersCount;
		mPassengersWeightSum = rhs.mPassengersWeightSum;
		mBreakCount = 0;
		mMovedDistanceKM = 0;

		// nullptr�� �ƴ� ��� �޸𸮸� ���Ҵ����� �ʽ��ϴ�. 
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