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

		// Node* �����͸� �����մϴ�.
		// Node ����ü�� <string, int>�� key,value ������ �����ϴ�. 
		// collision�� �߻��� ��츦 ���� ���� ��带 ����Ű�� �����͸� �����ϴ�.
		nodePointer mArray[MAX_SIZE]; 
	};
}