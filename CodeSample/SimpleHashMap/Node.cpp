#include "Node.h"


namespace samples
{
	Node::Node(const char* key, int data)
		: mKey(std::string(key))
		, mData(data)
	{
	}

	// next�� �ּҰ��� ������ �� �����ϴ�.
	// ���� ��带 next ���� �����մϴ�.
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