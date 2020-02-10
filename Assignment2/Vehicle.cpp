#include "Airplane.h"
#include "Boat.h"
#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mMaxPassengersCount(maxPassengersCount)
		, mPassengersCount(0)
		, mPassengersWeightSum(0)
		, mBreakCount(0)
		, mMovedDistanceKM(0)
		, mbMovable(true)
	{
		mPassengerList = new const Person * [mMaxPassengersCount];
	}

	Vehicle::Vehicle(const Airplane& a, const Boat& b)
		: mMaxPassengersCount(a.GetMaxPassengersCount() + b.GetMaxPassengersCount())
		, mPassengersCount(a.GetPassengersCount() + b.GetPassengersCount())
		, mPassengersWeightSum(a.GetPassengersWeightSum() + b.GetPassengersWeightSum())
		, mBreakCount(0)
		, mMovedDistanceKM(0)
		, mbMovable(true)
	{
		mPassengerList = new const Person * [mMaxPassengersCount];
	}

	Vehicle::Vehicle(const Vehicle& other)
		: mMaxPassengersCount(other.mMaxPassengersCount)
		, mPassengersCount(other.mPassengersCount)
		, mPassengersWeightSum(other.mPassengersWeightSum)
		, mBreakCount(other.mBreakCount)
		, mMovedDistanceKM(other.mMovedDistanceKM)
		, mbMovable(other.mbMovable)
	{
		mPassengerList = new const Person * [mMaxPassengersCount];

		assert(mPassengersCount <= mMaxPassengersCount);
		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			mPassengerList[i] = new Person(*(other.mPassengerList[i]));
		}
	}

	Vehicle::~Vehicle()
	{
		for (size_t i = 0; i != mPassengersCount; ++i)
		{
			delete mPassengerList[i];
			mPassengerList[i] = nullptr;
		}
		delete[] mPassengerList;
		mPassengerList = nullptr;

		// 멤버 변수 set 보류
		//mMaxPassengersCount = 0;
		mPassengersCount = 0;
		mPassengersWeightSum = 0;
		mBreakCount = 0;
		mMovedDistanceKM = 0;
		mbMovable = true;
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		if (mPassengersCount >= mMaxPassengersCount)
		{
			return false;
		}
		assert(person != nullptr);

		mPassengerList[mPassengersCount] = person;
		++mPassengersCount;
		mPassengersWeightSum += person->GetWeight();

		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (i >= mPassengersCount)
		{
			return false;
		}

		mPassengersWeightSum -= mPassengerList[i]->GetWeight();
		--mPassengersCount;

		delete mPassengerList[i];
		mPassengerList[i] = nullptr;

		// 삭제한 승객 위치부터 한칸씩 앞으로 당김
		for (int x = i; x != mPassengersCount; ++x)
		{
			mPassengerList[x] = mPassengerList[x + 1];
		}
		mPassengerList[mPassengersCount] = nullptr;

		return true;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i >= mPassengersCount)
		{
			return NULL;
		}
		assert(mPassengerList[i] != nullptr);

		return mPassengerList[i];
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengersCount;
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mPassengersCount;
	}

	unsigned int Vehicle::GetPassengersWeightSum() const
	{
		return mPassengersWeightSum;
	}

	unsigned int Vehicle::GetMovedDistanceKM() const
	{
		return mMovedDistanceKM;
	}

	Vehicle& Vehicle::operator=(const Vehicle& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		
		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			delete mPassengerList[i];
		}

		// 최대 탑승객 수가 동일하다면 재할당하지 않습니다.
		if (mMaxPassengersCount != rhs.mMaxPassengersCount)
		{
			delete[] mPassengerList;
			mMaxPassengersCount = rhs.mMaxPassengersCount;
			mPassengerList = new const Person * [mMaxPassengersCount];
		}

		mPassengersCount = rhs.mPassengersCount;
		mPassengersWeightSum = rhs.mPassengersWeightSum;
		mBreakCount = rhs.mBreakCount;
		mMovedDistanceKM = rhs.mMovedDistanceKM;
		mbMovable = rhs.mbMovable;

		assert(mPassengersCount <= mMaxPassengersCount);
		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			mPassengerList[i] = new Person(*(rhs.mPassengerList[i]));
		}

		return *this;
	}
}