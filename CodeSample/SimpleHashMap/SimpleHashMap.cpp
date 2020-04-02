#include <string>
#include <algorithm>
#include <iostream>

#include "SimpleData.h"
#include "SimpleHashMap.h"

namespace samples
{
	void SimpleHashMap::Add(const char* key, unsigned long hash, int value)
	{
		/*
			<key, value> ���� �߰��մϴ�.
			
			���� hash���� ���� ���� �ε����� �̹� �����Ͱ� ������ ���
			���� ���� key�� ������ key���� Ȯ���մϴ�. �����ϴٸ� �����͸� ����ϴ�.

			�������� �ʴٸ� ����ִ� ��带 ã�� ������ �ݺ����� ���鼭
			����ִ� ��忡 �� ��带 �߰��մϴ�. 
			
			���� ���߿� ������� ���� ����� key�� ���� ���� key�� ���ٸ�
			�ش� ��带 �� ���� ��ü�մϴ�.
		*/

		nodePointer newNode = std::make_shared<Node>(key, value);

		size_t index = hash % MAX_SIZE;

		if (mArray[index] == nullptr)
		{
			mArray[index] = newNode;
			return;
		}

		if (mArray[index]->GetKey() == key)
		{
			newNode->SetNext(mArray[index]->GetNext());
			mArray[index] = newNode;
			return;
		}

		nodePointer current = mArray[index];
		while (current->GetNext() != nullptr)
		{
			if (current->GetNext()->GetKey() == key)
			{
				newNode->SetNext(current->GetNext()->GetNext());
				current->SetNext(newNode);
				return;
			}

			current = current->GetNext();
		}

		current->SetNext(newNode);
	}

	int SimpleHashMap::Get(const char* key, unsigned long hash) const
	{
		/*
			key�� ��ġ�ϴ� ��带 ã�� value�� ��ȯ�մϴ�.
		*/

		size_t index = hash % MAX_SIZE;

		if (mArray[index] == nullptr)
		{
			return -1;
		}

		nodePointer current = mArray[index];
		while (current != nullptr)
		{
			if (current->GetKey() == key)
			{
				return current->GetData();
			}

			current = current->GetNext();
		}

		return -1;
	}

	void SimpleHashMap::Print() const
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (mArray[i] != nullptr)
			{
				nodePointer current = mArray[i];

				while (current != nullptr)
				{
					std::cout << "Key: " << current->GetKey() << ", Value: " << current->GetData() << std::endl;
					current = current->GetNext();
				}
			}
		}
	}
}