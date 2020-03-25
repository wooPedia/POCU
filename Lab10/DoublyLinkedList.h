#pragma once

#include <memory>
#include <cassert>
#include "Node.h"

namespace lab10
{
	template <typename T>
	class Node;

	enum class eTraversing
	{
		HEAD_TO_TAIL,
		TAIL_TO_HEAD
	};

	template <typename T>
	class DoublyLinkedList final
	{
	public:
		DoublyLinkedList();
		~DoublyLinkedList() = default;
		DoublyLinkedList(const DoublyLinkedList<T>&) = default;
		DoublyLinkedList& operator=(const DoublyLinkedList<T>&) = default;

		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;

		std::shared_ptr<Node<T>> operator[](unsigned int index) const;
		inline unsigned int GetLength() const;

		/*void Print() const
		{
			auto traversingNode = mHead->Next;
			while (traversingNode != nullptr)
			{
				assert(traversingNode != mTail);
				std::cout << *(traversingNode->Data) << "->";
				traversingNode = traversingNode->Next;
			}
		}*/

	private:
		using nodePointer = std::shared_ptr<Node<T>>;

		void insertFront(std::unique_ptr<T> data);
		void linkPrevNewNext(nodePointer prevNode, nodePointer newNode, nodePointer nextNode);
		eTraversing findNodeWithIndex(size_t index, nodePointer& traversingNode) const;
		bool findNodeWithData(const T& data, nodePointer& traversingNode) const;

		nodePointer mHead;
		nodePointer mTail;
		size_t mLength;
	};

	template <typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
		: mHead(std::make_shared<Node<T>>(std::make_unique<T>(NULL)))
		, mTail(std::make_shared<Node<T>>(std::make_unique<T>(NULL), mHead))
		, mLength(0)
	{
		mHead->Next = mTail;
	}

	template <typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		// 새 노드를 list의 마지막에 추가합니다.

		nodePointer newNode;

		auto tailPrev = mTail->Previous.lock();

		// 첫 노드일 경우
		if (tailPrev == mHead)
		{
			newNode = std::make_shared<Node<T>>(std::move(data), nullptr);
		}
		else
		{
			newNode = std::make_shared<Node<T>>(std::move(data), tailPrev);
		}

		tailPrev->Next = newNode;
		mTail->Previous = newNode;

		++mLength;
	}

	template <typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		// index 위치에 새 노드를 추가합니다.
		// index가 리스트 범위 밖이라면 마지막에 추가합니다.

		if (index >= mLength || mLength == 0)
		{
			Insert(std::move(data));
			return;
		}

		if (index == 0)
		{
			insertFront(std::move(data));
			return;
		}

		// index가 tail보다 head에 가깝다면 head부터 순회합니다.
		nodePointer traversingNode;

		if (findNodeWithIndex(index, traversingNode) == eTraversing::HEAD_TO_TAIL)
		{
			auto prev = traversingNode->Previous.lock();
			auto newNode = std::make_shared<Node<T>>(std::move(data), prev);
			linkPrevNewNext(prev, newNode, traversingNode);

			++mLength;
			return;
		}
		else
		{
			// index가 head보다 tail에 가깝다면 tail부터 순회합니다.
			auto prevOfNewNode = traversingNode->Previous.lock();
			auto newNode = std::make_shared<Node<T>>(std::move(data), prevOfNewNode);
			linkPrevNewNext(prevOfNewNode, newNode, traversingNode);

			++mLength;
			return;
		}
	}

	template <typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		// 리스트에서 data와 처음 일치하는 노드를 찾아 삭제 후 true를 반환하고
		// 찾지 못했다면 false를 반환합니다.

		nodePointer traversingNode;
		if (findNodeWithData(data, traversingNode))
		{
			// 찾았다면 삭제할 노드의 앞뒤 노드를 연결합니다.

			// 크기가 1일 경우
			if (mLength == 1)
			{
				mHead->Next = mTail;
				mTail->Previous = mHead;
				--mLength;

				return true;
			}

			// 첫 노드일 경우
			if (mHead->Next == traversingNode)
			{
				mHead->Next = traversingNode->Next;
				--mLength;

				return true;
			}
			else if (mTail->Previous.lock() == traversingNode)
			{
				// 마지막 노드일 경우
				auto prev = traversingNode->Previous.lock();
				prev->Next = nullptr;
				mTail->Previous = prev;
				--mLength;

				return true;
			}

			// 일반적인 경우
			auto prev = traversingNode->Previous.lock();
			auto next = traversingNode->Next;

			prev->Next = next;
			next->Previous = prev;
			--mLength;

			return true;
		}

		return false;
	}

	template <typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		// data와 일치하는 값을 가진 노드를 찾았다면 true
		// 그렇지 않다면 false를 반환합니다.

		nodePointer traversingNode;
		return findNodeWithData(data, traversingNode);
	}

	template <typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{
		if (index >= mLength)
		{
			return nullptr;
		}

		nodePointer traversingNode;
		findNodeWithIndex(index, traversingNode);

		return traversingNode;
	}

	template <typename T>
	inline unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}


	// private method

	template <typename T>
	void DoublyLinkedList<T>::insertFront(std::unique_ptr<T> data)
	{
		// 리스트의 0번째 인덱스에 삽입하니다.
		// 추가할 노드의 다음 노드가 tail이 아니여야 합니다.

		assert(mHead->Next != mTail);

		auto next = mHead->Next;
		auto newNode = std::make_shared<Node<T>>(std::move(data));

		mHead->Next = newNode;
		newNode->Next = next;
		next->Previous = newNode;

		++mLength;
	}


	template <typename T>
	void DoublyLinkedList<T>::linkPrevNewNext(nodePointer prevNode
		, nodePointer newNode
		, nodePointer nextNode)
	{
		// prev, new, next node를 연결합니다.
		// newNode의 prev는 설정되어 있다고 가정합니다.
		prevNode->Next = newNode;
		newNode->Next = nextNode;
		nextNode->Previous = newNode;
	}

	template <typename T>
	eTraversing DoublyLinkedList<T>::findNodeWithIndex(size_t index, nodePointer& traversingNode) const
	{
		/*
			indexNode를 찾아 traversingNode에 저장합니다.
			index가 head에 가깝다면 head부터
			tail에 가깝다면 tail부터 순회합니다.
		*/

		size_t midIndex = mLength / 2;
		size_t curIndex = 0;

		if (index <= midIndex)
		{
			/*
				head부터 tail 방향으로 순회합니다.
			*/
			traversingNode = mHead->Next;
			while (traversingNode != nullptr && curIndex != index)
			{
				traversingNode = traversingNode->Next;
				++curIndex;
			}

			return eTraversing::HEAD_TO_TAIL;
		}
		else
		{
			/*
				tail부터 head 방향으로 순회합니다.
			*/
			assert(mLength >= 1);
			curIndex = mLength - 1;

			traversingNode = mTail->Previous.lock();
			while (traversingNode != nullptr && curIndex != index)
			{
				traversingNode = traversingNode->Previous.lock();
				--curIndex;
			}

			return eTraversing::TAIL_TO_HEAD;
		}
	}

	template <typename T>
	bool DoublyLinkedList<T>::findNodeWithData(const T& data, nodePointer& traversingNode) const
	{
		// 현재 리스트에서 data와 일치하는 값을 가진 node가 있다면
		// true를 반환하고, 그렇지 않다면 false를 반환합니다.

		traversingNode = mHead->Next;
		while (traversingNode != nullptr && *traversingNode->Data != data)
		{
			traversingNode = traversingNode->Next;
		}

		assert(traversingNode != mHead || traversingNode != mTail);

		return traversingNode != nullptr ? true : false;
	}
} // namespace