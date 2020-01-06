#include <limits>

#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab1/Add.h"
#include "../Lab1/Add.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		int a, b, sum;

		TEST_METHOD(AddTwoPositive)
		{
			a = INT_MAX;
			b = INT_MAX-1;
			sum = a + b;
			Assert::AreEqual(sum, lab1::Add(a, b));
		}
		TEST_METHOD(AddTwoNegative)
		{
			a = -12124212;
			b = -98293482;
			sum = a + b;
			Assert::AreEqual(sum, lab1::Add(a, b));
		}
		TEST_METHOD(AddPositiveAndNegative)
		{
			a = -2312382;
			b = 92142146;
			sum = a + b;
			Assert::AreEqual(sum, lab1::Add(a, b));
		}


	};
}
