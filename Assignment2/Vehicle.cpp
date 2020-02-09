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
		, mBreakCount(0)
		, mMovedDistanceKM(0)
		, mbMovable(true)
	{
		// 복사 생성자
		// other의 탑승자를 모두 새 운송수단으로 옮기고
		// other의 탑승자는 모두 삭제한다.
		// mPassengerList[i]에 other.mPassengerList[i]를 모두 옮길 순 있다.
		// 그리고 other.mPassengerList의 모든 원소를 삭제할 순 있다.
		//mPassengerList = other.mPassengerList; 

		mPassengerList = new const Person * [mMaxPassengersCount];
		//for (int i = 0; i != mCurPassengersCount; ++i)
		//{
		//	mPassengerList[i] = new Person(other.mPassengerList[i]->GetName().c_str(), other.mPassengerList[i]->GetWeight());
		//}
		//// other의 탑승자 초기화
		//// other.mPassengerList는 사라짐
		//other.~Vehicle();
		//SetPassengersCount(other.GetPassengersCount());
		//SetPassengersWeightSum(other.GetPassengersWeightSum());
	}

	Vehicle::~Vehicle()
	{
		for (int i = 0; i != mPassengersCount; ++i)
		{
			delete mPassengerList[i];
			mPassengerList[i] = nullptr;
		}
		delete[] mPassengerList;
		mPassengerList = nullptr;

		// 멤버 변수 set 보류
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
}