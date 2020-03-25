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
		// �ʱ� ������ �����մϴ�.
		mHead->Next = mDummyHead;
		mDummyHead->Next = mDummyTail;
	}

	template <typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		// �� ��带 list�� �������� �߰��մϴ�.

		// head -> ... <-> dummyTailPrev <-> dummyTail
		auto dummyTailPrev = mDummyTail->Previous.lock();
		auto newNode = std::make_shared<Node<T>>(std::move(data), dummyTailPrev);

		// ������ ��带 �����մϴ�.
		// dummyTailPrev <-> newNode <-> dummyTail
		linkPrevNewNext(dummyTailPrev, newNode, mDummyTail);
		++mLength;
	}

	template <typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		// index ��ġ�� �� ��带 �߰��մϴ�.
		// index�� ����Ʈ ���� ���̶�� �������� �߰��մϴ�.

		if (index >= mLength)
		{
			Insert(std::move(data));
			return;
		}
		
		// index�� tail���� head�� �����ٸ� head���� ��ȸ�մϴ�.
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
			// index�� head���� tail�� �����ٸ� tail���� ��ȸ�մϴ�.
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
		// ����Ʈ���� data�� ó�� ��ġ�ϴ� ��带 ã�� ���� �� true�� ��ȯ�ϰ�
		// �׷��� �ʴٸ� false�� ��ȯ�մϴ�.

		nodePointer traversingNode;
		if (findNodeWithData(data, traversingNode))
		{
			// ã�Ҵٸ� ������ ����� �յ� ��带 �����մϴ�.
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
		// data�� ��ġ�ϴ� ���� ���� ��带 ã�Ҵٸ� true
		// �׷��� �ʴٸ� false�� ��ȯ�մϴ�.

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
		// prev, new, next node�� �����մϴ�.
		// newNode�� prev�� �����Ǿ� �ִٰ� �����մϴ�.

		assert(newNode->Previous.lock() == prevNode);

		prevNode->Next = newNode;
		newNode->Next = nextNode;
		nextNode->Previous = newNode;
	}

	template <typename T>
	eTraversing DoublyLinkedList<T>::findNodeWithIndex(size_t index, nodePointer& traversingNode) const
	{
		// index�� head�� �����ٸ� head����
		// tail�� �����ٸ� tail���� ��ȸ�մϴ�.
		size_t midIndex = mLength / 2;
		size_t curIndex = 0;

		if (index <= midIndex)
		{
			/*
				dummyHead���� tail �������� ��ȸ�մϴ�.
				������ ����Ǹ� traversingNode�� index ����� prev ����Դϴ�.
				dummyHead <-> ... <-> traversingNode <-> indexNode <->  ... <-> dummyTail
			*/
			for (traversingNode = mDummyHead; curIndex != index; ++curIndex, traversingNode = traversingNode->Next);

			return eTraversing::HEAD_TO_TAIL;
		}
		else
		{
			/*
				dummyTail���� head �������� ��ȸ�մϴ�.
				������ ����Ǹ� traversingNode�� index ����� next ����Դϴ�.
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
		// ���� ����Ʈ���� data�� ��ġ�ϴ� ���� ���� node�� �ִٸ�
		// true�� ��ȯ�ϰ�, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.

		traversingNode = mDummyHead->Next;
		while (traversingNode != mDummyTail && *traversingNode->Data != data)
		{
			traversingNode = traversingNode->Next;
		}

		return traversingNode != mDummyTail ? true : false;
	}
} // namespace