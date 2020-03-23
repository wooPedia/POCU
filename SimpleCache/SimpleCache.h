#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>

#include "MyVector2D.h"

namespace samples
{
	class SimpleCache final
	{
	public:
		SimpleCache() = default;
		~SimpleCache() = default;

		void Add(std::string key, std::weak_ptr<MyVector2D> ptr);
		std::shared_ptr<MyVector2D> Get(std::string key);

	private:
		std::unordered_map<std::string, std::weak_ptr<MyVector2D>> mMap;
	};
}