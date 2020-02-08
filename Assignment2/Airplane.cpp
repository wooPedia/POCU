#include <cmath>

#include "Airplane.h"
#include "Boat.h"

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount) {}

	Airplane::~Airplane() { std::cout << "~Airplane" << std::endl; }

	Boatplane Airplane::operator+(Boat& boat)
	{
		// Airplane a;
		// Boat b;
		// Boatplane bp = a + b;
		unsigned int newMaxPC = mMaxPassengersCount + boat.GetMaxPassengersCount();
		unsigned int apPC = mPassengersCount;
		unsigned int boatPC = boat.GetPassengersCount();

		Boatplane bp(newMaxPC);
		size_t j = 0;
		for (size_t i = 0; i != apPC + boatPC; ++i)
		{
			/*
				bp던 *bp던 리턴하면 
				1. 소멸자 호출
				2. a+b 임시 객체에 생성에 대한 복사 생성자 호출
				3. 좌변으로 복사 생성자 또는 할당 연산자 호출

				1. Person*을 얕은 복사로 그대로 옮기기.
					- 빠르지만 해당 함수에서 두 운송 수단의 메모리를 해제해야하기 때문에 안됨.
					- 아니면 두 운송 수단

				2. 따로 메모리를 생성하여 복사하고 ap, boat 개체의 탑승객 리스트는 삭제시키기.
					- 1번보다 느리지만 어쩔수 없음
			*/
			if (i < apPC)
			{
				bp.AddPassenger(new Person(mPassengerList[i]->GetName().c_str(), mPassengerList[i]->GetWeight()));
			}
			else
			{
				bp.AddPassenger(new Person(boat.GetPassenger(j)->GetName().c_str(), boat.GetPassenger(j)->GetWeight()));
				++j;
			}
		}

		/*
			*this와 boat에 동적으로 할당된 승객 리스트들이 삭제됩니다.
			따라서 생성자에서 생성된 승객 리스트의 메모리가 해제되었기 때문에 
			더 이상은 두 운송 수단에 승객 추가가 불가. 즉 운송 수단으로서의 기능X
			두 운송 수단을 합체해서 새로운 운송 수단을 만들었기 때문에 
			두 운송 수단은 더 이상 안쓰인다고 판단.
		*/
		this->~Airplane();
		boat.~Boat();

		// Boatplane 복사 생성자를 호출
		return bp;
	}


	// 상속 받은 함수

	unsigned int Airplane::GetMaxSpeed() const
	{
		return GetFlySpeed();
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		double speed = 4 * exp((400 - mPassengersWeightSum) / static_cast<double>(70));

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return static_cast<unsigned int>(speed);
		}
		else
		{
			return static_cast<unsigned int>(speed + 1);
		}
	}

	unsigned int Airplane::GetFlySpeed() const
	{
		double speed = 200 * exp((800 - mPassengersWeightSum) / static_cast<double>(500));

		if (static_cast<unsigned int>(speed + 0.5) != static_cast<unsigned int>(speed + 1))
		{
			return static_cast<unsigned int>(speed);
		}
		else
		{
			return static_cast<unsigned int>(speed + 1);
		}
	}

	void Airplane::Move()
	{
		// Airplane: 한 번 이동 후 세 번 쉽니다.

		// 충분히 쉬었다면 이동 가능합니다.
		if (mBreakCount == AIRPLANE)
		{
			mbMovable = true;
		}

		// 이동할 수 없다면 break 합니다.
		if (!mbMovable)
		{
			++mBreakCount;
			assert(mBreakCount <= AIRPLANE);
		}
		else
		{
			mMovedDistanceKM += GetMaxSpeed();
			mBreakCount = 0;
			mbMovable = false;
		}
	}
}
