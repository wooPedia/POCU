#include "DeusExMachina.h"

namespace assignment2
{
	DeusExMachina::DeusExMachina()
		: mManagedVehicleCount(0) {}

	// static ��� ���� �ʱ�ȭ
	DeusExMachina* DeusExMachina::mInstance = nullptr;

	DeusExMachina* DeusExMachina::GetInstance()
	{
		static bool bExist = false;

		// �ν��Ͻ��� �������� �ʴ´ٸ� �����ϰ�, 
		// �̹� �����Ѵٸ� ���� �ν��Ͻ��� ��ȯ�մϴ�.
		if (!bExist)
		{
			mInstance = new DeusExMachina;
			bExist = true;
			return mInstance;
		}
		else
		{
			return mInstance;
		}
	}

	void DeusExMachina::Travel() const
	{
		for (size_t i = 0; i < mManagedVehicleCount; ++i)
		{
			mManagedVehicle[i]->Move();
		}
	}

	bool DeusExMachina::AddVehicle(Vehicle* vehicle)
	{
		const size_t MAX_VEHICLE_COUNT = 10;
		if (mManagedVehicleCount >= MAX_VEHICLE_COUNT)
		{
			return false;
		}
		assert(vehicle != nullptr);

		mManagedVehicle[mManagedVehicleCount] = vehicle;
		++mManagedVehicleCount;

		return true;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		if (i >= mManagedVehicleCount)
		{
			return false;
		}

		delete mManagedVehicle[i];
		--mManagedVehicleCount;

		for (int x = i; x != mManagedVehicleCount; ++x)
		{
			mManagedVehicle[x] = mManagedVehicle[x + 1];
		}
		mManagedVehicle[mManagedVehicleCount] = nullptr;

		return true;
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if (mManagedVehicleCount == 0)
		{
			return NULL;
		}

		size_t theFurthest = 0;
		for (size_t i = 1; i < mManagedVehicleCount; ++i)
		{
			theFurthest =
				(mManagedVehicle[theFurthest]->GetMovedDistanceKM() > mManagedVehicle[i]->GetMovedDistanceKM()) ?
				theFurthest : i;
		}

		// ������ ��� ������ ���ٸ� ù ��° ��� ������ ��ȯ�մϴ�.
		if (mManagedVehicle[theFurthest]->GetMovedDistanceKM() == 0)
		{
			return mManagedVehicle[0];
		}

		return mManagedVehicle[theFurthest];
	}
}