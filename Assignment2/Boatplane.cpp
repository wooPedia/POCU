#include <cmath>

#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount) {}

	Boatplane::Boatplane(Airplane* a, Boat* b)
		: Vehicle(*a, *b)
	{
		/*
			- a와 b 승객의 주소를 얕은 복사로 그대로 Boatplane으로 이동
			- a와 b에서 더 이상 이동한 승객들에 대한 소유권을 가지면 안되므로
			- a와 b가 승객들을 저장했던 mPassengerList를 소멸자를 통해 해제.
			- 단, mPassengerList의 원소를 해제하면 승객들의 주소가 사라지므로
			- mPassengerList만 해제하여 원소를 단순히 잃어버리도록 함.
			- 따라서 a와 b의 mPassengerCount를 0으로 수정 후 소멸자를 호출해야 함
		*/

		// 승객을 주소 그대로 옮깁니다.
		size_t j = 0;
		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			if (i < a->GetPassengersCount())
			{
				mPassengerList[i] = a->GetPassenger(i);
			}
			else
			{
				mPassengerList[i] = b->GetPassenger(j);
				++j;
			}
		}

		// 승객 수를 변경하여 소멸자에서 각 원소에 대해서는 delete를 못하도록 합니다.
		a->mPassengersCount = 0;
		b->mPassengersCount = 0;
		
		a->~Airplane();
		b->~Boat();
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

	//Boatplane& Boatplane::operator=(const Boatplane& rhs)
	//{
	//	// boatplane = boatplane이라면 딥카피하면 되는데 
	//	// boatplane = a+b일 경우 어떻게 하나?
	//	// 복사생성자가 호출되지 않도록 object를 반환할 순 있지만
	//	// 할당연산자는 이미 존재하는 개체에 할당 시 무조건 호출됨
	//	if (this == &rhs)
	//	{
	//		return *this;
	//	}

	//	assert(mPassengerList != nullptr);
	//	for (size_t i = 0; i < mPassengersCount; ++i)
	//	{
	//		delete mPassengerList[i];
	//		mPassengerList[i] = nullptr;
	//	}

	//	// 최대 탑승객 수가 동일하다면 재할당할 필요가 없습니다.
	//	if (mMaxPassengersCount != rhs.mMaxPassengersCount)
	//	{
	//		delete[] mPassengerList;
	//		mMaxPassengersCount = rhs.mMaxPassengersCount;
	//		mPassengerList = new const Person * [mMaxPassengersCount];
	//	}

	//	// 멤버 변수 set
	//	mPassengersCount = rhs.mPassengersCount;
	//	mPassengersWeightSum = rhs.mPassengersWeightSum;
	//	mBreakCount = 0;
	//	mMovedDistanceKM = 0;

	//	assert(mMaxPassengersCount >= mPassengersCount);
	//	for (size_t i = 0; i < mPassengersCount; ++i)
	//	{
	//		mPassengerList[i] = new Person(*(rhs.mPassengerList[i]));
	//		assert(mPassengerList[i]->GetName() == rhs.mPassengerList[i]->GetName());
	//		assert(mPassengerList[i]->GetWeight() == rhs.mPassengerList[i]->GetWeight());
	//	}

	//	return *this;
	//}
}