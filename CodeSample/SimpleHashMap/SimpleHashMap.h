#pragma once

#include <memory>

#include "Node.h"
#include "SimpleData.h"

namespace samples
{
	class SimpleHashMap final
	{
	public:
		using nodePointer = std::shared_ptr<Node>;

		SimpleHashMap() = default;
		~SimpleHashMap() = default;

		void Add(const char* key, unsigned long hash, int value);
		int Get(const char* key, unsigned long hash) const;
		void Print() const;

	private:
		static constexpr int MAX_SIZE = 10;

		// Node* 데이터를 저장합니다.
		// Node 구조체는 <string, int>를 key,value 쌍으로 가집니다. 
		// collision이 발생할 경우를 위해 다음 노드를 가리키는 포인터를 가집니다.
		nodePointer mArray[MAX_SIZE]; 
	};
}