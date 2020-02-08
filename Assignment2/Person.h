#pragma once

#include <string>

namespace assignment2
{
	class Person
	{
	public:
		Person(const char* name, unsigned int weight);
		Person(const Person& other);
		~Person();

		const std::string& GetName() const;
		unsigned int GetWeight() const;

		Person& operator=(const Person& rhs);

	private:
		std::string mName;
		unsigned int mWeight;
	};
}