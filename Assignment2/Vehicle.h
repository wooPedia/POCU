#pragma once

#include <cassert>
#include <iostream>

#include "DeusExMachina.h"
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

	class DeusExMachina;

	// 모든 운송 수단 클래스는 해당 클래스를 상속 받아야 합니다.
	class Vehicle
	{
		friend const Vehicle* DeusExMachina::GetFurthestTravelled() const;
	public:
		Vehicle(unsigned int maxPassengersCount);
		Vehicle(const Vehicle& other);
		virtual ~Vehicle();

		// 모든 운송 수단 클래스는 최고 속도를 반환하는 함수를 정의해야 합니다.
		virtual unsigned int GetMaxSpeed() const = 0;
		virtual void Move() = 0;

		bool AddPassenger(const Person* person);
		bool RemovePassenger(unsigned int i);
		const Person* GetPassenger(unsigned int i) const;
		unsigned int GetPassengersCount() const;
		unsigned int GetMaxPassengersCount() const;
		unsigned int GetPassengersWeightSum() const;

	protected:
		unsigned int mMaxPassengersCount; // max 100
		unsigned int mPassengersCount;	  // current
		unsigned int mPassengersWeightSum;
		const Person** mPassengerList; 
		
		unsigned int mBreakCount;	    // 휴식한 횟수
		unsigned int mMovedDistanceKM;  // 이동한 거리  
		bool mbMovable;				    // 이동 가능 여부 
	};
}