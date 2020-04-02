#include "Node.h"


namespace samples
{
	Node::Node(const char* key, int data)
		: mKey(std::string(key))
		, mData(data)
	{
	}

	// next의 주소값을 변경할 수 없습니다.
	// 다음 노드를 next 노드로 설정합니다.
	void Node::SetNext(nodePointer const next)
	{
		mNext = next;
	}

	Node::nodePointer Node::GetNext() const
	{
		return mNext;
	}

	int Node::GetData() const
	{
		return mData;
	}

	const std::string& Node::GetKey() const
	{
		return mKey;
	}
}