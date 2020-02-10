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

	private:
		DeusExMachina(); // ╫л╠шео

		static DeusExMachina* mInstance;
		Vehicle* mManagedVehicle[10] = { 0, };
		unsigned int mManagedVehicleCount;
	};
}