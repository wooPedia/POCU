#include "Airplane.h"

#include "DeusExMachina.h"

namespace assignment2
{
	// static 멤버 변수 초기화
	DeusExMachina* DeusExMachina::instance = nullptr;

	DeusExMachina* DeusExMachina::GetInstance()
	{
		static bool bExist = false;

		if (!bExist)
		{
			instance = new DeusExMachina;
			bExist = true;
			return instance;
		}
		else
		{
			return instance;
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

	// friend function in Vehicle class
	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if (mManagedVehicleCount == 0)
		{
			return NULL;
		}

		size_t IndexOfFurthestTravelled = 0;
		for (size_t i = 1; i < mManagedVehicleCount; ++i)
		{
			IndexOfFurthestTravelled =
				(mManagedVehicle[IndexOfFurthestTravelled]->mMovedDistanceKM > mManagedVehicle[i]->mMovedDistanceKM) ?
				IndexOfFurthestTravelled : i;
		}

		return mManagedVehicle[IndexOfFurthestTravelled];
	}
}