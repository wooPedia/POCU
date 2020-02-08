#include "Person.h"
#include <iostream>

namespace assignment2
{
	Person::Person(const char* name, unsigned int weight)
		: mName(name), mWeight(weight) {}

	Person::Person(const Person& other)
		: mName(other.mName)
		, mWeight(other.mWeight) {}

	Person::~Person() 
	{
		std::cout << "~Person" << std::endl;
	}

	const std::string& Person::GetName() const
	{
		return mName;
	}

	unsigned int Person::GetWeight() const
	{
		return mWeight;
	}

	Person& Person::operator=(const Person& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		mName = rhs.mName;
		mWeight = rhs.mWeight;

		return *this;
	}

}