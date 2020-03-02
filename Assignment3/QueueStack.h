#pragma once

#include <cassert>
#include <queue>

#include "SmartStack.h"

namespace assignment3
{
	/*
		===========================================
					QueueStack<T> Ŭ����
		===========================================
	*/


	template <typename T>
	class QueueStack
	{
	public:
		using queueStack = std::queue<SmartStack<T> >;

		QueueStack() = delete;
		QueueStack(size_t maxStackSize);
		QueueStack(const QueueStack& other) = default;
		~QueueStack() = default;
		QueueStack& operator=(const QueueStack& rhs) = default;

		void Enqueue(T number);
		T Peek() const;
		T Dequeue();
		
		T GetMax() const;
		T GetMin() const;
		inline T GetSum() const;
		double GetAverage() const;
		inline size_t GetCount() const;
		size_t GetStackCount() const; 

	private:

		// QueueStack���� �ִ�/�ּҰ��� ã�� ��ȯ�մϴ�.
		T findMax(queueStack qs) const;
		T findMin(queueStack qs) const;

		queueStack mQueueStack;
		std::queue<T> mStoredMax;
		std::queue<T> mStoredMin;

		size_t mMaxStackSize;
		T mTotalSum;
	};


	/*
		===========================================
					  public ��� �Լ�
		===========================================
	*/

	template <typename T>
	QueueStack<T>::QueueStack(size_t maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mTotalSum(0)
	{
		mQueueStack.push(SmartStack<T>());
	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{

		assert(mQueueStack.back().GetCount() <= mMaxStackSize);

		// ������� ������ �ִ� ũ���� �� ������ �߰��մϴ�.
		if (mQueueStack.back().GetCount() == mMaxStackSize)
		{
			mQueueStack.push(SmartStack<T>());
		}

		//if (!mQueueStack.front().Empty())
		//{

		//}
		//else
		//{
		//}

		// ���尡���� ���ÿ� ���� �߰��մϴ�.
		mQueueStack.back().Push(number);
		mTotalSum += number;
	}

	// ù ���(����)�� top�� ��ȯ�մϴ�. 
	template <typename T>
	T QueueStack<T>::Peek() const
	{
		assert(!mQueueStack.front().Empty());

		return mQueueStack.front().Peek();
	}

	template <typename T>
	T QueueStack<T>::Dequeue()
	{
		assert(!mQueueStack.front().Empty());

		T front = mQueueStack.front().Pop();
		mTotalSum -= front;
		
		// ù ������ ����ٸ� �����մϴ�.
		if (mQueueStack.front().Empty())
		{
			mQueueStack.pop();
		}

		return front;
	}

	template <typename T>
	T QueueStack<T>::GetMax() const
	{
		if (mQueueStack.front().Empty())
		{
			return std::numeric_limits<T>::min();
		}
		
		return findMax(mQueueStack);
	}

	template <typename T>
	T QueueStack<T>::GetMin() const
	{
		if (mQueueStack.front().Empty())
		{
			return std::numeric_limits<T>::max();
		}

		return findMin(mQueueStack);
	}


	//	======== float, double Ÿ�Կ� ���� �Լ� ���ø� Ư��ȭ ========

	template <>
	float QueueStack<float>::GetMin() const;

	template <>
	double QueueStack<double>::GetMin() const;

	// =============================================================

	template <typename T>
	T QueueStack<T>::GetSum() const
	{
		return mTotalSum;
	}

	template <typename T>
	double QueueStack<T>::GetAverage() const
	{
		assert(!mQueueStack.front().Empty());

		double tmp = mTotalSum / (GetCount() + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	size_t QueueStack<T>::GetCount() const
	{
		assert(!mQueueStack.empty());

		return (mQueueStack.size() - 1) * mMaxStackSize + mQueueStack.back().GetCount();
	}

	template <typename T>
	size_t QueueStack<T>::GetStackCount() const
	{
		return mQueueStack.size();
	}


	/*
		===========================================
					  private ��� �Լ�
		===========================================
	*/

	template <typename T>
	T QueueStack<T>::findMax(queueStack qs) const
	{
		T max = qs.front().GetMax();
		qs.pop();

		while (!qs.empty())
		{
			if (qs.front().GetMax() > max)
			{
				max = qs.front().GetMax();
			}
			qs.pop();
		}

		return max;
	}

	template <typename T>
	T QueueStack<T>::findMin(queueStack qs) const
	{
		T min = qs.front().GetMin();
		qs.pop();

		while (!qs.empty())
		{
			if (qs.front().GetMin() < min)
			{
				min = qs.front().GetMin();
			}
			qs.pop();
		}

		return min;
	}


} // namespace
