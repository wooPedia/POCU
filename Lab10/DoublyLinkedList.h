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

	private:
		using nodePointer = std::shared_ptr<Node<T>>;

		void linkPrevNewNext(nodePointer prevNode, nodePointer newNode, nodePointer nextNode);
		eTraversing findNodeWithIndex(size_t index, nodePointer& traversingNode) const;
		bool findNodeWithData(const T& data, nodePointer& traversingNode) const;

		nodePointer mDummyHead;
		nodePointer mDummyTail;
		nodePointer mHead;
		nodePointer mTail;
		size_t mLength;
	};

	template <typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
		: mDummyHead(std::make_shared<Node<T>>(std::make_unique<T>(NULL)))
		, mDummyTail(std::make_shared<Node<T>>(std::make_unique<T>(NULL), mDummyHead))
		, mHead(std::make_shared<Node<T>>(std::make_unique<T>(NULL)))
		, mTail(std::make_shared<Node<T>>(std::make_unique<T>(NULL), mDummyTail))
		, mLength(0)
	{
		// 초기 노드들을 연결합니다.
		mHead->Next = mDummyHead;
		mDummyHead->Next = mDummyTail;
	}

	template <typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		// 새 노드를 list의 마지막에 추가합니다.

		// head -> ... <-> dummyTailPrev <-> dummyTail
		auto dummyTailPrev = mDummyTail->Previous.lock();
		auto newNode = std::make_shared<Node<T>>(std::move(data), dummyTailPrev);

		// 세개의 노드를 연결합니다.
		// dummyTailPrev <-> newNode <-> dummyTail
		linkPrevNewNext(dummyTailPrev, newNode, mDummyTail);
		++mLength;
	}

	template <typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		// index 위치에 새 노드를 추가합니다.
		// index가 리스트 범위 밖이라면 마지막에 추가합니다.

		if (index >= mLength)
		{
			Insert(std::move(data));
			return;
		}
		
		// index가 tail보다 head에 가깝다면 head부터 순회합니다.
		nodePointer traversingNode;
		if (findNodeWithIndex(index, traversingNode) == eTraversing::HEAD_TO_TAIL)
		{
			auto newNode = std::make_shared<Node<T>>(std::move(data), traversingNode);
			linkPrevNewNext(traversingNode, newNode, traversingNode->Next);
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
		// 그렇지 않다면 false를 반환합니다.

		nodePointer traversingNode;
		if (findNodeWithData(data, traversingNode))
		{
			// 찾았다면 삭제할 노드의 앞뒤 노드를 연결합니다.
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
		if (findNodeWithIndex(index, traversingNode) == eTraversing::HEAD_TO_TAIL)
		{
			return traversingNode->Next;
		}
		else
		{
			return traversingNode->Previous.lock();
		}
	}

	template <typename T>
	inline unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}


	// private method

	template <typename T>
	void DoublyLinkedList<T>::linkPrevNewNext(nodePointer prevNode
		, nodePointer newNode
		, nodePointer nextNode)
	{
		// prev, new, next node를 연결합니다.
		// newNode의 prev는 설정되어 있다고 가정합니다.

		assert(newNode->Previous.lock() == prevNode);

		prevNode->Next = newNode;
		newNode->Next = nextNode;
		nextNode->Previous = newNode;
	}

	template <typename T>
	eTraversing DoublyLinkedList<T>::findNodeWithIndex(size_t index, nodePointer& traversingNode) const
	{
		// index가 head에 가깝다면 head부터
		// tail에 가깝다면 tail부터 순회합니다.
		size_t midIndex = mLength / 2;
		size_t curIndex = 0;

		if (index <= midIndex)
		{
			/*
				dummyHead부터 tail 방향으로 순회합니다.
				루프가 종료되면 traversingNode는 index 노드의 prev 노드입니다.
				dummyHead <-> ... <-> traversingNode <-> indexNode <->  ... <-> dummyTail
			*/
			for (traversingNode = mDummyHead; curIndex != index; ++curIndex, traversingNode = traversingNode->Next);

			return eTraversing::HEAD_TO_TAIL;
		}
		else
		{
			/*
				dummyTail부터 head 방향으로 순회합니다.
				루프가 종료되면 traversingNode는 index 노드의 next 노드입니다.
				dummyHead <-> ... <-> indexNode <-> traversingNode <-> ... <-> dummyTail
			*/
			curIndex = mLength - 1;
			for (traversingNode = mDummyTail; curIndex != index; --curIndex, traversingNode = traversingNode->Previous.lock());

			return eTraversing::TAIL_TO_HEAD;
		}
	}


	template <typename T>
	bool DoublyLinkedList<T>::findNodeWithData(const T& data, nodePointer& traversingNode) const
	{
		// 현재 리스트에서 data와 일치하는 값을 가진 node가 있다면
		// true를 반환하고, 그렇지 않다면 false를 반환합니다.

		traversingNode = mDummyHead->Next;
		while (traversingNode != mDummyTail && *traversingNode->Data != data)
		{
			traversingNode = traversingNode->Next;
		}

		return traversingNode != mDummyTail ? true : false;
	}
} // namespace