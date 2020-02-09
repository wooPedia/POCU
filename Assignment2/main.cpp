#include <cassert>
#include <iostream>
#include <iomanip>

#include "Vehicle.h"
#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"
#include "Motorcycle.h"
#include "Sedan.h"
#include "UBoat.h"
#include "Trailer.h"
#include "DeusExMachina.h"
#include "Person.h"


#define STR(name) #name

using namespace assignment2;
using namespace std;

int main()
{

	//Person* p = new Person("Bob", 85);
	//Person* p2 = new Person("James", 75);
	//Person* p3 = new Person("Tina", 52);
	//Person* p4 = new Person("Peter", 78);
	//Person* p5 = new Person("Jane", 48);
	//Person* p6 = new Person("Steve", 88);

	//Airplane a(5);
	//a.AddPassenger(p);
	//a.AddPassenger(p2);
	//a.AddPassenger(p3);

	//Boat b(5);
	//b.AddPassenger(p4);
	//b.AddPassenger(p5);
	//b.AddPassenger(p6);

	//Boatplane bp = b + a; // Airplane + Boat
	//assert(bp.GetPassengersCount() == 6); // 6을 반환
	//assert(bp.GetMaxPassengersCount() == 10); // 10을 반환

	//assert(a.GetPassengersCount() == 0); // 0을 반환
	//assert(b.GetPassengersCount() == 0); // 0을 반환
	//
	//assert(bp.GetPassenger(0) == p);

	//Boatplane bp2(bp);
	//for (int i = 0; i != bp.GetPassengersCount(); ++i)
	//{
	//	assert(bp2.GetPassenger(i) != bp.GetPassenger(i));
	//}
	//assert(bp.GetMaxPassengersCount() == bp2.GetMaxPassengersCount());
	//assert(bp.GetPassengersCount() == bp2.GetPassengersCount());
	//assert(bp.GetPassengersWeightSum() == bp2.GetPassengersWeightSum());

	//Boatplane bp3(20);
	//bp3 = a + b;
	//for (int i = 0; i != bp2.GetPassengersCount(); ++i)
	//{
	//	assert(bp2.GetPassenger(i) != bp3.GetPassenger(i));
	//}
	//assert(bp.GetMaxPassengersCount() == bp2.GetMaxPassengersCount());
	//assert(bp.GetPassengersCount() == bp2.GetPassengersCount());
	//assert(bp.GetPassengersWeightSum() == bp2.GetPassengersWeightSum());
	//a.AddPassenger(p2);
	//a.AddPassenger(p3);

	//a.GetMaxSpeed();

	const char* MAX_SPEED_LABLE = "Max Speed: ";
	const char* CUR_P_LABLE = "Current Person: ";
	const unsigned int MAX_CAPACITY = 10;

	Vehicle* air = new Airplane(MAX_CAPACITY);

	Person* toAdd;
	const unsigned int personWeight = 10;

	for (size_t i = 0; i < MAX_CAPACITY + 10; i++)
	{
		toAdd = new Person(STR(i), i);
		if (air->AddPassenger(toAdd) == false)
		{
			delete toAdd;
		}

		cout << MAX_SPEED_LABLE << air->GetMaxSpeed() << endl
			<< CUR_P_LABLE << air->GetPassengersCount() << endl;
	}

	while (air->RemovePassenger(0))
	{
		cout << CUR_P_LABLE << air->GetPassengersCount() << endl;
	}

	Person* overlapTest = new Person("Overlap Test", 100);
	//air->AddPassenger(overlapTest);
	air->AddPassenger(overlapTest);
	assert(air->GetPassengersCount() == 1);  // error

	//toAdd = NULL;
	//assert(air->AddPassenger(toAdd) == false);

	delete air;

	Airplane dockingTest1(10);
	Boat dockingTest2(10);

	for (size_t i = 0; i < 5; i++)
	{
		dockingTest1.AddPassenger(new Person(STR(i), i));
		dockingTest2.AddPassenger(new Person(STR(i), i));
	}

	const Person* comp1 = dockingTest1.GetPassenger(0);

	Boatplane bp1 = dockingTest1 + dockingTest2;
	Boatplane bp2 = dockingTest2 + dockingTest1;

	const Person* comp2 = bp1.GetPassenger(0);

	assert(comp1 == comp2);
	assert(dockingTest1.GetPassengersCount() == 0);
	assert(dockingTest2.GetPassengersCount() == 0);
	assert(bp1.GetPassengersCount() == 10);
	assert(bp2.GetPassengersCount() == 0);

	Boatplane copyConstuctorTest(bp1);

	for (size_t i = 0; i < bp1.GetPassengersCount(); i++)
	{
		const Person* p1 = bp1.GetPassenger(i);
		const Person* p2 = copyConstuctorTest.GetPassenger(i);
		assert(p1 != p2);
	}
	assert(bp1.GetMaxPassengersCount() == copyConstuctorTest.GetMaxPassengersCount());
	assert(bp1.GetPassengersCount() == copyConstuctorTest.GetPassengersCount());
	assert(bp1.GetMaxSpeed() == copyConstuctorTest.GetMaxSpeed());

	Sedan sedanTest;
	Trailer* t1 = new Trailer(10);
	Trailer* t2 = new Trailer(20);

	assert(sedanTest.AddTrailer(t1));
	assert(!sedanTest.AddTrailer(t1));
	assert(!sedanTest.AddTrailer(t2));
	assert(sedanTest.RemoveTrailer());
	assert(sedanTest.AddTrailer(t2));
	assert(sedanTest.RemoveTrailer());

	DeusExMachina* d = DeusExMachina::GetInstance();
	Vehicle* demAirplain = new Airplane(MAX_CAPACITY);
	Vehicle* demBoat = new Airplane(MAX_CAPACITY);
	Vehicle* demBoatplain = new Boatplane(MAX_CAPACITY);
	Vehicle* demMotorcycle = new Motorcycle();
	Vehicle* demSedan1 = new Sedan();
	Vehicle* demSedan2 = new Sedan();
	Trailer* demTrailer = new Trailer(10);
	static_cast<Sedan*>(demSedan2)->AddTrailer(demTrailer);
	Vehicle* demUBoat = new UBoat();

	d->AddVehicle(demAirplain);
	d->AddVehicle(demBoat);
	d->AddVehicle(demBoatplain);
	d->AddVehicle(demMotorcycle);
	d->AddVehicle(demSedan1);
	d->AddVehicle(demSedan2);
	d->AddVehicle(demUBoat);

	for (size_t i = 0; i < 7; i++)
	{
		Vehicle* tempVPointer = d->GetVehicle(i);
		for (size_t j = tempVPointer->GetPassengersCount(); j < tempVPointer->GetMaxPassengersCount(); j++)
		{
			tempVPointer->AddPassenger(new Person(STR((i + j)), 10));
		}
	}

	for (size_t i = 0; i < 10; i++)
	{
		d->Travel();
	}

	delete d;

	return 0;
}