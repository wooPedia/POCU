#include <memory>
#include <iostream>
#include <cassert>
#include "CacheExample.h"
#include "SimpleCache.h"
#include "MyVector2D.h"

using namespace std;

namespace samples
{
	void CacheExample()
	{
		// vector1 -> MyVector2D(0, 1), strong ref: 1
		// vector2 -> MyVector2D(2, 5), strong ref: 1 
		// vector3 -> MyVector2D(8, 4), strong ref: 1 
		shared_ptr<MyVector2D> vector1 = make_shared<MyVector2D>(0, 1);
		shared_ptr<MyVector2D> vector2 = make_shared<MyVector2D>(2, 5);
		shared_ptr<MyVector2D> vector3 = make_shared<MyVector2D>(8, 4);

		SimpleCache cache;

		// "Candy"    , vector1(0, 1), weak ref: 1
		// "IceCream" , vector2(2, 5), weak ref: 1
		// "Chocolate", vector3(8, 4), weak ref: 1
		cache.Add("Candy", vector1);
		cache.Add("IceCream", vector2);
		cache.Add("Chocolate", vector3);

		// cachedVector2 -> vector2(2, 5)
		// strong ref: 2, weak ref: 1
		shared_ptr<MyVector2D> cachedVector2 = cache.Get("IceCream");

		// s.r: 2
		// X: 2, Y: 5
		cout << "Usage of cachedVector2: " << cachedVector2.use_count() << endl;
		cout << "IceCream values: X: " << cachedVector2->GetX() << ", Y: " << cachedVector2->GetY() << endl;

		// "IceCream", vector3(8, 4), weak ref: 2
		//             vector2(2, 5), weak ref: 0
		cache.Add("IceCream", vector3);

		// cachedVector2 -> vector3(8, 4), strong ref: 2
		cachedVector2 = cache.Get("IceCream");

		cout << "IceCream values: X: " << cachedVector2->GetX() << ", Y: " << cachedVector2->GetY() << endl;

		// "Candy", vector1(nullptr), strong ref: 0
		vector1 = nullptr;

		shared_ptr<MyVector2D> cachedVector1 = cache.Get("Candy");

		assert(cachedVector1 == nullptr);
	}
}