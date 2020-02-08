#pragma once

#include <cassert>
#include <iostream>

#include "DeusExMachina.h"
#include "Person.h"

#define Assert(expression, message) assert(expression && message)

namespace assignment2
{
	// ��� ���ܺ� �޽� Ƚ��
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

	// ��� ��� ���� Ŭ������ �ش� Ŭ������ ��� �޾ƾ� �մϴ�.
	class Vehicle
	{
		friend const Vehicle* DeusExMachina::GetFurthestTravelled() const;
	public:
		Vehicle(unsigned int maxPassengersCount);
		Vehicle(const Vehicle& other);
		virtual ~Vehicle();

		// ��� ��� ���� Ŭ������ �ְ� �ӵ��� ��ȯ�ϴ� �Լ��� �����ؾ� �մϴ�.
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
		
		unsigned int mBreakCount;	    // �޽��� Ƚ��
		unsigned int mMovedDistanceKM;  // �̵��� �Ÿ�  
		bool mbMovable;				    // �̵� ���� ���� 
	};
}