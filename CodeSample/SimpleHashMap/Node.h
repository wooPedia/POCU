#pragma once

#include <string>
#include <memory>

namespace samples
{
	class Node final
	{
	public:
		using nodePointer = std::shared_ptr<Node>;

		Node() = delete;
		Node(const char* key, int data);
		~Node() = default;

		void SetNext(nodePointer const next);
		nodePointer GetNext() const;
		int GetData() const;
		const std::string& GetKey() const;

	private:

		// <string, int>를 key,value 쌍으로 가집니다. 
		// collision이 발생할 경우를 위해 다음 노드를 가리키는 포인터를 가집니다.

		std::string mKey;
		int mData;
		nodePointer mNext;
	};
}
