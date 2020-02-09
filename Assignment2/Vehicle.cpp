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
		// ���� ������
		// other�� ž���ڸ� ��� �� ��ۼ������� �ű��
		// other�� ž���ڴ� ��� �����Ѵ�.
		// mPassengerList[i]�� other.mPassengerList[i]�� ��� �ű� �� �ִ�.
		// �׸��� other.mPassengerList�� ��� ���Ҹ� ������ �� �ִ�.
		//mPassengerList = other.mPassengerList; 

		mPassengerList = new const Person * [mMaxPassengersCount];
		//for (int i = 0; i != mCurPassengersCount; ++i)
		//{
		//	mPassengerList[i] = new Person(other.mPassengerList[i]->GetName().c_str(), other.mPassengerList[i]->GetWeight());
		//}
		//// other�� ž���� �ʱ�ȭ
		//// other.mPassengerList�� �����
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

		// ��� ���� set ����
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

		// ������ �°� ��ġ���� ��ĭ�� ������ ���
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