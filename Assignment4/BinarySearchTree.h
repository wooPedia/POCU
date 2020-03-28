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
			�� ��带 �߰��մϴ�.
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
		// Ʈ������ data�� ã���� true�� ��ȯ�ϰ� 
		// �׷��� �ʴٸ� false�� ��ȯ�մϴ�.

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
			Ʈ������ data�� ��ġ�ϴ� �����͸� ���� ù ��带 ã�� ���� �� true�� ��ȯ�մϴ�.
			ã�� ���ߴٸ� false�� ��ȯ�մϴ�.

			1. �ڽ� ��尡 ���� ��� �׳� �����Ѵ�.
			2. �ڽ� ��尡 �ϳ��� ��� �ش� ��带 �ڽ� ���� ��ü�Ѵ�.
			3. �ڽ� ��尡 2���� ���
		*/

		// data�� ��ġ�ϴ� ��带 ã�� target�� �����մϴ�.
		nodePointer target = mRoot;
		if (!searchNode(target, data))
		{
			return false;
		}

		// �ڽ� ��尡 ���� ���
		if (!target->Left && !target->Right)
		{
			deleteNodeWithNoChildren(target);
			return true;
		}
		else if (!target->Left || !target->Right)
		{
			// �ڽ� ��尡 �ϳ��� ���
			deleteNodeWithOneChild(target);
			return true;
		}
		else
		{
			// �ڽ� ��尡 �ΰ��� ���
			deleteNodeWithTwoChildren(target);
			return true;
		}

		return false;
	}

	template <typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		// Ʈ���� ���� ��ȸ�� ����� ���Ϳ� �����Ͽ� ��ȯ�մϴ�.

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
		// startNode���� �����Ͽ� �˸´� ��ġ�� �� ��带 �����մϴ�.

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
		// data�� ��ġ�ϴ� ��带 startNode���� ���ʷ� Ž���մϴ�.

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
		// data�� ��ġ�ϴ� ���� ���� ���(target)�� �����մϴ�.
		// ��, �ڽ��� ���� ��常 �ش�˴ϴ�.

		assert(target && !target->Left && !target->Right);

		// target�� root�� ���
		if (target == mRoot)
		{
			mRoot = nullptr;
			return;
		}

		// target��带 parent�κ��� �����մϴ�.
		(target->Parent.lock()->Left == target) ? (target->Parent.lock()->Left = nullptr) : (target->Parent.lock()->Right = nullptr);
	}

	template <typename T>
	void BinarySearchTree<T>::deleteNodeWithOneChild(nodePointer& target)
	{
		// data�� ��ġ�ϴ� ���� ���� ���(target)�� �����մϴ�.
		// ��, �ڽ��� �ϳ��� ��常 �ش�˴ϴ�.

		assert(target && (!target->Left || !target->Right));

		// target�� root�� ���
		if (target == mRoot)
		{
			mRoot = (mRoot->Left ? mRoot->Left : mRoot->Right);
			mRoot->Parent.reset();
			return;
		}

		// target�� ����Ʈ���� ������ ���
		if (target->Left)
		{
			// target�� parent�� target�� ����Ʈ���� �����մϴ�.
			target->Left->Parent = target->Parent;
			(target->Parent.lock()->Left == target) ? (target->Parent.lock()->Left = target->Left) : (target->Parent.lock()->Right = target->Left);
		}
		else
		{
			// target�� ����Ʈ���� �������� ���
			target->Right->Parent = target->Parent;
			(target->Parent.lock()->Left == target) ? (target->Parent.lock()->Left = target->Right) : (target->Parent.lock()->Right = target->Right);
		}
	}

	template <typename T>
	void BinarySearchTree<T>::deleteNodeWithTwoChildren(nodePointer& target)
	{
		/*
			data�� ��ġ�ϴ� ���� ���� ���(target)�� �����մϴ�.
			��, �ڽ��� �ΰ��� ��常 �ش�˴ϴ�.

			1. target�� ������ ���� Ʈ������ ���� ���� ���(minNode)�� ã���ϴ�.
			2. target�� Data move�մϴ�.
			3. minNode�� �����մϴ�.
		*/

		assert(target && target->Left && target->Right);

		// target�� ������ ����Ʈ������ ���� ���� ���� ���� ��带 ã���ϴ�.
		auto minNode = findMin(target);

		// minNode�� ���� ����Ʈ���� �����ؼ� �ȵ˴ϴ�.
		assert(!minNode->Left);

		// data�� target�� ����
		target->Data = std::move(minNode->Data);

		// ����Ʈ���� ���� ���
		if (!minNode->Left && !minNode->Right)
		{
			deleteNodeWithNoChildren(minNode);
		}
		else
		{
			// ����Ʈ���� ������ ���
			deleteNodeWithOneChild(minNode);
		}
	}

	template <typename T>
	std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::findMin(nodePointer& start) const
	{
		// start��� ���� Ʈ������ �ּҰ��� ���� ��带 ã�� ��ȯ�մϴ�.

		// start��尡 �ΰ��� �ڽ� ��带 ������ ��.
		assert(start->Left && start->Right);

		auto minNode = start->Right;
		while (minNode->Left)
		{
			minNode = minNode->Left;
		}

		return minNode;
	}

} // namespace

