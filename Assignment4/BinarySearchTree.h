#pragma once

#include <memory>
#include <vector>
#include <cassert>

namespace assignment4
{
	template <typename T>
	class TreeNode;

	template <typename T>
	class BinarySearchTree final
	{
	public:
		BinarySearchTree() = default;
		~BinarySearchTree() = default;
		BinarySearchTree(const BinarySearchTree<T>&) = default;
		BinarySearchTree& operator=(const BinarySearchTree<T>&) = default;

		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);

	private:
		using nodePointer = std::shared_ptr<TreeNode<T>>;

		void insertNode(nodePointer& startNode, std::unique_ptr<T> data);
		bool searchNode(nodePointer& startNode, const T& data);
		static void traverseInOrder(const std::shared_ptr<TreeNode<T>> startNode, std::vector<T>& vec);
		void deleteNodeWithNoChildren(nodePointer& target);
		void deleteNodeWithOneChild(nodePointer& target);
		void deleteNodeWithTwoChildren(nodePointer& target);
		std::shared_ptr<TreeNode<T>> findMin(nodePointer& start) const;

		nodePointer mRoot;
	};

	// public method

	template <typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		/*
			새 노드를 추가합니다.
		*/

		if (!mRoot)
		{
			mRoot = std::make_shared<TreeNode<T>>(std::move(data));
			return;
		}
		else if (*data <= *mRoot->Data)
		{
			nodePointer startNode = mRoot->Left;
			insertNode(startNode, std::move(data));
			return;
		}
		else
		{
			nodePointer startNode = mRoot->Right;
			insertNode(startNode, std::move(data));
			return;
		}
	}

	template <typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRoot;
	}

	template <typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		// 트리에서 data를 찾으면 true를 반환하고 
		// 그렇지 않다면 false를 반환합니다.

		if (!mRoot)
		{
			return false;
		}
		else if (data < *mRoot->Data)
		{
			nodePointer startNode = mRoot->Left;
			if (searchNode(startNode, data))
			{
				return true;
			}
		}
		else if (data > * mRoot->Data)
		{
			nodePointer startNode = mRoot->Right;
			if (searchNode(startNode, data))
			{
				return true;
			}
		}
		else
		{
			// data == *mRoot->Data
			return true;
		}

		return false;
	}

	template <typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		/*
			트리에서 data와 일치하는 데이터를 가진 첫 노드를 찾아 삭제 후 true를 반환합니다.
			찾지 못했다면 false를 반환합니다.

			1. 자식 노드가 없는 경우 그냥 삭제한다.
			2. 자식 노드가 하나일 경우 해당 노드를 자식 노드로 대체한다.
			3. 자식 노드가 2개인 경우
		*/

		// data와 일치하는 노드를 찾아 target에 저장합니다.
		nodePointer target = mRoot;
		if (!searchNode(target, data))
		{
			return false;
		}

		// 자식 노드가 없는 경우
		if (!target->Left && !target->Right)
		{
			deleteNodeWithNoChildren(target);
			return true;
		}
		else if (!target->Left || !target->Right)
		{
			// 자식 노드가 하나일 경우
			deleteNodeWithOneChild(target);
			return true;
		}
		else
		{
			// 자식 노드가 두개인 경우
			deleteNodeWithTwoChildren(target);
			return true;
		}

		return false;
	}

	template <typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		// 트리를 중위 순회한 결과를 벡터에 저장하여 반환합니다.

		std::vector<T> vec;
		if (startNode)
		{
			traverseInOrder(startNode->Left, vec);
			vec.push_back(*startNode->Data);
			traverseInOrder(startNode->Right, vec);
		}

		return vec;
	}


	// private method

	template <typename T>
	void BinarySearchTree<T>::insertNode(nodePointer& startNode, std::unique_ptr<T> data)
	{
		// startNode부터 시작하여 알맞는 위치에 새 노드를 삽입합니다.

		nodePointer parent = mRoot;
		while (startNode)
		{
			assert(startNode->Data);
			if (*data <= *startNode->Data)
			{
				parent = startNode;
				startNode = startNode->Left;
			}
			else
			{
				parent = startNode;
				startNode = startNode->Right;
			}
		}

		assert(parent->Data);
		if (*data <= *parent->Data)
		{
			parent->Left = std::make_shared<TreeNode<T>>(parent, std::move(data));
		}
		else
		{
			parent->Right = std::make_shared<TreeNode<T>>(parent, std::move(data));
		}
	}

	template <typename T>
	bool BinarySearchTree<T>::searchNode(nodePointer& startNode, const T& data)
	{
		// data와 일치하는 노드를 startNode부터 차례로 탐색합니다.

		while (startNode)
		{
			assert(startNode->Data);

			if (data < *startNode->Data)
			{
				startNode = startNode->Left;
			}
			else if (data > * startNode->Data)
			{
				startNode = startNode->Right;
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	template <typename T>
	void BinarySearchTree<T>::traverseInOrder(const std::shared_ptr<TreeNode<T>> startNode, std::vector<T>& vec)
	{
		if (startNode)
		{
			traverseInOrder(startNode->Left, vec);
			vec.push_back(*startNode->Data);
			traverseInOrder(startNode->Right, vec);
		}
	}

	template <typename T>
	void BinarySearchTree<T>::deleteNodeWithNoChildren(nodePointer& target)
	{
		// data와 일치하는 값을 가진 노드(target)를 삭제합니다.
		// 단, 자식이 없는 노드만 해당됩니다.

		assert(target && !target->Left && !target->Right);

		// target이 root일 경우
		if (target == mRoot)
		{
			mRoot = nullptr;
			return;
		}

		// target노드를 parent로부터 삭제합니다.
		(target->Parent.lock()->Left == target) ? (target->Parent.lock()->Left = nullptr) : (target->Parent.lock()->Right = nullptr);
	}

	template <typename T>
	void BinarySearchTree<T>::deleteNodeWithOneChild(nodePointer& target)
	{
		// data와 일치하는 값을 가진 노드(target)를 삭제합니다.
		// 단, 자식이 하나인 노드만 해당됩니다.

		assert(target && (!target->Left || !target->Right));

		// target이 root일 경우
		if (target == mRoot)
		{
			mRoot = (mRoot->Left ? mRoot->Left : mRoot->Right);
			mRoot->Parent.reset();
			return;
		}

		// target의 서브트리가 왼쪽일 경우
		if (target->Left)
		{
			// target의 parent와 target의 서브트리를 연결합니다.
			target->Left->Parent = target->Parent;
			(target->Parent.lock()->Left == target) ? (target->Parent.lock()->Left = target->Left) : (target->Parent.lock()->Right = target->Left);
		}
		else
		{
			// target의 서브트리가 오른쪽일 경우
			target->Right->Parent = target->Parent;
			(target->Parent.lock()->Left == target) ? (target->Parent.lock()->Left = target->Right) : (target->Parent.lock()->Right = target->Right);
		}
	}

	template <typename T>
	void BinarySearchTree<T>::deleteNodeWithTwoChildren(nodePointer& target)
	{
		/*
			data와 일치하는 값을 가진 노드(target)를 삭제합니다.
			단, 자식이 두개인 노드만 해당됩니다.

			1. target의 오른쪽 서브 트리에서 가장 작은 노드(minNode)를 찾습니다.
			2. target에 Data move합니다.
			3. minNode를 삭제합니다.
		*/

		assert(target && target->Left && target->Right);

		// target의 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 찾습니다.
		auto minNode = findMin(target);

		// minNode의 왼쪽 서브트리가 존재해선 안됩니다.
		assert(!minNode->Left);

		// data를 target에 이전
		target->Data = std::move(minNode->Data);

		// 서브트리가 없을 경우
		if (!minNode->Left && !minNode->Right)
		{
			deleteNodeWithNoChildren(minNode);
		}
		else
		{
			// 서브트리가 존재할 경우
			deleteNodeWithOneChild(minNode);
		}
	}

	template <typename T>
	std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::findMin(nodePointer& start) const
	{
		// start노드 하위 트리에서 최소값을 가진 노드를 찾아 반환합니다.

		// start노드가 두개의 자식 노드를 가져야 함.
		assert(start->Left && start->Right);

		auto minNode = start->Right;
		while (minNode->Left)
		{
			minNode = minNode->Left;
		}

		return minNode;
	}

} // namespace

