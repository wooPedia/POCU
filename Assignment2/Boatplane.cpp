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
			- a�� b �°��� �ּҸ� ���� ����� �״�� Boatplane���� �̵�
			- a�� b���� �� �̻� �̵��� �°��鿡 ���� �������� ������ �ȵǹǷ�
			- a�� b�� �°����� �����ߴ� mPassengerList�� �Ҹ��ڸ� ���� ����.
			- ��, mPassengerList�� ���Ҹ� �����ϸ� �°����� �ּҰ� ������Ƿ�
			- mPassengerList�� �����Ͽ� ���Ҹ� �ܼ��� �Ҿ�������� ��.
			- ���� a�� b�� mPassengerCount�� 0���� ���� �� �Ҹ��ڸ� ȣ���ؾ� ��
		*/

		// �°��� �ּ� �״�� �ű�ϴ�.
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

		// �°� ���� �����Ͽ� �Ҹ��ڿ��� �� ���ҿ� ���ؼ��� delete�� ���ϵ��� �մϴ�.
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

	//Boatplane& Boatplane::operator=(const Boatplane& rhs)
	//{
	//	// boatplane = boatplane�̶�� ��ī���ϸ� �Ǵµ� 
	//	// boatplane = a+b�� ��� ��� �ϳ�?
	//	// ��������ڰ� ȣ����� �ʵ��� object�� ��ȯ�� �� ������
	//	// �Ҵ翬���ڴ� �̹� �����ϴ� ��ü�� �Ҵ� �� ������ ȣ���
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

	//	// �ִ� ž�°� ���� �����ϴٸ� ���Ҵ��� �ʿ䰡 �����ϴ�.
	//	if (mMaxPassengersCount != rhs.mMaxPassengersCount)
	//	{
	//		delete[] mPassengerList;
	//		mMaxPassengersCount = rhs.mMaxPassengersCount;
	//		mPassengerList = new const Person * [mMaxPassengersCount];
	//	}

	//	// ��� ���� set
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