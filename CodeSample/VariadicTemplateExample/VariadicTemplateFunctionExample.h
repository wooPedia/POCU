#pragma once

#include <iostream>
#include <memory>

namespace samples
{
	void VariadicTemplateFunctionExample();

	// T 타입 1개와 가변 인자를 받습니다.
	template <typename T, typename... TArgs>
	T* Create(TArgs... args)
	{
		std::cout << "Creating instance" << std::endl;
		T* object = new T(args...);

		return object;
	}
}