#pragma once

#include <string>

namespace samples
{
	class Goo final
	{
	public:
		Goo() = delete;
		Goo(const char* name, unsigned int age);
		~Goo() = default;

	private:
		std::string mName;
		unsigned int mAge;
	};

	Goo::Goo(const char* name, unsigned int age)
		: mName(std::string(name))
		, mAge(age) 
	{
	}
}