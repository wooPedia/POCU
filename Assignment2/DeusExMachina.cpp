#include "DeusExMachina.h"

namespace assignment2
{
	DeusExMachina::DeusExMachina()
		: mManagedVehicleCount(0) {}

	// static 멤버 변수 초기화
	DeusExMachina* DeusExMachina::mInstance = nullptr;

	DeusExMachina* DeusExMachina::GetInstance()
	{
		static bool bExist = false;

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

		size_t indexOfFurthestTravelled = 0;
		for (size_t i = 1; i < mManagedVehicleCount; ++i)
		{
			indexOfFurthestTravelled =
				(mManagedVehicle[indexOfFurthestTravelled]->GetMovedDistanceKM() > mManagedVehicle[i]->GetMovedDistanceKM()) ?
				indexOfFurthestTravelled : i;
		}

		// 움직인 운송 수단이 없다면 첫 번째 운송 수단을 반환합니다.
		if (mManagedVehicle[indexOfFurthestTravelled]->GetMovedDistanceKM() == 0)
		{
			return mManagedVehicle[0];
		}

		return mManagedVehicle[indexOfFurthestTravelled];
	}
}