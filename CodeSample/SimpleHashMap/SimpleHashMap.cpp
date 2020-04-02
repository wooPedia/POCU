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
			<key, value> 쌍을 추가합니다.
			
			만약 hash값을 통해 얻은 인덱스에 이미 데이터가 존재할 경우
			새로 들어온 key와 동일한 key인지 확인합니다. 동일하다면 데이터를 덮어씁니다.

			동일하지 않다면 비어있는 노드를 찾을 때까지 반복문을 돌면서
			비어있는 노드에 새 노드를 추가합니다. 
			
			만약 도중에 비어있지 않은 노드의 key가 새로 들어온 key와 같다면
			해당 노드를 새 노드로 교체합니다.
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
			key와 일치하는 노드를 찾아 value를 반환합니다.
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