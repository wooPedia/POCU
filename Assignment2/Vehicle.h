#pragma once

#include <cassert>

#include "Person.h"

#define Assert(expression, message) assert(expression && message)

namespace assignment2
{
	// 운송 수단별 휴식 횟수
	enum eVehicleBreakCount
	{
		BOAT = 1,
		MOTORCYCLE = 1,
		SEDAN = 1,
		SEDAN_WITH_TRAILER = 2,
		AIRPLANE = 3,
		BOATPLANE = 3,
		UBOAT = 4
	};

	class Airplane;
	class Boat;

	// 모든 운송 수단 클래스는 해당 클래스를 상속 받아야 합니다.
	class Vehicle
	{
	public:
		Vehicle(unsigned int maxPassengersCount);
		Vehicle(const Airplane& a, const Boat& b);
		Vehicle(const Vehicle& other);
		virtual ~Vehicle();

		virtual unsigned int GetMaxSpeed() const = 0;
		virtual void Move() = 0;

		bool AddPassenger(const Person* person);
		bool RemovePassenger(unsigned int i);
		
		const Person* GetPassenger(unsigned int i) const;
		unsigned int GetPassengersCount() const;
		unsigned int GetMaxPassengersCount() const;
		unsigned int GetPassengersWeightSum() const;
		unsigned int GetMovedDistanceKM() const;

		Vehicle& operator=(const Vehicle& rhs); 

	protected:
		inline void deletePassengerList();

		unsigned int mMaxPassengersCount; // max 100
		unsigned int mPassengersCount;	  // current
		unsigned int mPassengersWeightSum;
		const Person** mPassengerList; 
		
		unsigned int mBreakCount;	    // 휴식한 횟수
		unsigned int mMovedDistanceKM;  // 이동한 거리  
		bool mbMovable;				    // 이동 가능 여부 
	};

	// inline
	void Vehicle::deletePassengerList()
	{
		for (size_t i = 0; i != mPassengersCount; ++i)
		{
			delete mPassengerList[i];
			mPassengerList[i] = nullptr;
		}
		delete[] mPassengerList;
		mPassengerList = nullptr;

		mPassengersCount = 0;
	}
}