#pragma once

#include <iostream>
#include <memory>

namespace samples
{
	void VariadicTemplateFunctionExample();

	// T Ÿ�� 1���� ���� ���ڸ� �޽��ϴ�.
	template <typename T, typename... TArgs>
	T* Create(TArgs... args)
	{
		std::cout << "Creating instance" << std::endl;
		T* object = new T(args...);

		return object;
	}
}