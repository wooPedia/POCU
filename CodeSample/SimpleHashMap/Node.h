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

		// <string, int>�� key,value ������ �����ϴ�. 
		// collision�� �߻��� ��츦 ���� ���� ��带 ����Ű�� �����͸� �����ϴ�.

		std::string mKey;
		int mData;
		nodePointer mNext;
	};
}
