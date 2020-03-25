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
		// �� ��带 list�� �������� �߰��մϴ�.

		nodePointer newNode;

		auto tailPrev = mTail->Previous.lock();

		// ù ����� ���
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
		// index ��ġ�� �� ��带 �߰��մϴ�.
		// index�� ����Ʈ ���� ���̶�� �������� �߰��մϴ�.

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

		// index�� tail���� head�� �����ٸ� head���� ��ȸ�մϴ�.
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
		// ã�� ���ߴٸ� false�� ��ȯ�մϴ�.

		nodePointer traversingNode;
		if (findNodeWithData(data, traversingNode))
		{
			// ã�Ҵٸ� ������ ����� �յ� ��带 �����մϴ�.

			// ũ�Ⱑ 1�� ���
			if (mLength == 1)
			{
				mHead->Next = mTail;
				mTail->Previous = mHead;
				--mLength;

				return true;
			}

			// ù ����� ���
			if (mHead->Next == traversingNode)
			{
				mHead->Next = traversingNode->Next;
				--mLength;

				return true;
			}
			else if (mTail->Previous.lock() == traversingNode)
			{
				// ������ ����� ���
				auto prev = traversingNode->Previous.lock();
				prev->Next = nullptr;
				mTail->Previous = prev;
				--mLength;

				return true;
			}

			// �Ϲ����� ���
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
		// ����Ʈ�� 0��° �ε����� �����ϴϴ�.
		// �߰��� ����� ���� ��尡 tail�� �ƴϿ��� �մϴ�.

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
		// prev, new, next node�� �����մϴ�.
		// newNode�� prev�� �����Ǿ� �ִٰ� �����մϴ�.
		prevNode->Next = newNode;
		newNode->Next = nextNode;
		nextNode->Previous = newNode;
	}

	template <typename T>
	eTraversing DoublyLinkedList<T>::findNodeWithIndex(size_t index, nodePointer& traversingNode) const
	{
		/*
			indexNode�� ã�� traversingNode�� �����մϴ�.
			index�� head�� �����ٸ� head����
			tail�� �����ٸ� tail���� ��ȸ�մϴ�.
		*/

		size_t midIndex = mLength / 2;
		size_t curIndex = 0;

		if (index <= midIndex)
		{
			/*
				head���� tail �������� ��ȸ�մϴ�.
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
				tail���� head �������� ��ȸ�մϴ�.
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
		// ���� ����Ʈ���� data�� ��ġ�ϴ� ���� ���� node�� �ִٸ�
		// true�� ��ȯ�ϰ�, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.

		traversingNode = mHead->Next;
		while (traversingNode != nullptr && *traversingNode->Data != data)
		{
			traversingNode = traversingNode->Next;
		}

		assert(traversingNode != mHead || traversingNode != mTail);

		return traversingNode != nullptr ? true : false;
	}
} // namespace