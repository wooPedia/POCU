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
				bp�� *bp�� �����ϸ� 
				1. �Ҹ��� ȣ��
				2. a+b �ӽ� ��ü�� ������ ���� ���� ������ ȣ��
				3. �º����� ���� ������ �Ǵ� �Ҵ� ������ ȣ��

				1. Person*�� ���� ����� �״�� �ű��.
					- �������� �ش� �Լ����� �� ��� ������ �޸𸮸� �����ؾ��ϱ� ������ �ȵ�.
					- �ƴϸ� �� ��� ����

				2. ���� �޸𸮸� �����Ͽ� �����ϰ� ap, boat ��ü�� ž�°� ����Ʈ�� ������Ű��.
					- 1������ �������� ��¿�� ����
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
			*this�� boat�� �������� �Ҵ�� �°� ����Ʈ���� �����˴ϴ�.
			���� �����ڿ��� ������ �°� ����Ʈ�� �޸𸮰� �����Ǿ��� ������ 
			�� �̻��� �� ��� ���ܿ� �°� �߰��� �Ұ�. �� ��� �������μ��� ���X
			�� ��� ������ ��ü�ؼ� ���ο� ��� ������ ������� ������ 
			�� ��� ������ �� �̻� �Ⱦ��δٰ� �Ǵ�.
		*/
		this->~Airplane();
		boat.~Boat();

		// Boatplane ���� �����ڸ� ȣ��
		return bp;
	}


	// ��� ���� �Լ�

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
		// Airplane: �� �� �̵� �� �� �� ���ϴ�.

		// ����� �����ٸ� �̵� �����մϴ�.
		if (mBreakCount == AIRPLANE)
		{
			mbMovable = true;
		}

		// �̵��� �� ���ٸ� break �մϴ�.
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
