#pragma once

#include "Vehicle.h"

namespace assignment2
{
	class Vehicle;

	class DeusExMachina
	{
	public:
		static DeusExMachina* GetInstance();
		void Travel() const;
		bool AddVehicle(Vehicle* vehicle);
		bool RemoveVehicle(unsigned int i);
		const Vehicle* GetFurthestTravelled() const;

		Vehicle* GetVehicle(unsigned int i) const
		{
			return mManagedVehicle[i];
		}

	private:
		static DeusExMachina* instance;
		Vehicle* mManagedVehicle[10]{ nullptr };
		unsigned int mManagedVehicleCount{ 0 };
	};
}