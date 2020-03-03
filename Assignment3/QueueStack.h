#pragma once

#include <cassert>
#include <queue>
#include <type_traits>

#include "SmartStack.h"

namespace assignment3
{
	/*
		===========================================
					QueueStack<T> 클래스
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

		// 추가한 함수
		bool Empty() const;

	private:

		// QueueStack에서 최대/최소값을 찾아 반환합니다.
		//T findMax(queueStack qs) const;
		//T findMin(queueStack qs) const;
		void reArrangeMaxHeap(queueStack qs);
		void reArrangeMinHeap(queueStack qs);

		queueStack mQueueStack;
		std::priority_queue<T> mMaxHeap;
		std::priority_queue<T, std::vector<T>, std::greater<T> > mMinHeap;

		size_t mMaxStackSize;
		T mTotalSum;
	};


	/*
		===========================================
					  public 멤버 함수
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

		// 사용중인 스택이 최대 크기라면 새 스택을 추가합니다.
		if (mQueueStack.back().GetCount() == mMaxStackSize)
		{
			mQueueStack.push(SmartStack<T>());
		}

		// 첫 Euqueue가 아닐 경우
		if (!mQueueStack.front().Empty())
		{
			if (number >= mMaxHeap.top())
			{
				mMaxHeap.push(number);
			}
			else if (number <= mMinHeap.top())
			{
				mMinHeap.push(number);
			}
		}
		else
		{
			mMaxHeap.push(number);
			mMinHeap.push(number);
		}


		// 저장가능한 스택에 값을 추가합니다.
		mQueueStack.back().Push(number);
		mTotalSum += number;
	}

	// 첫 요소(스택)의 top을 반환합니다. 
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

		// 첫 스택이 비었다면 삭제합니다.
		if (mQueueStack.front().Empty())
		{
			mQueueStack.pop();
		}

		if (front == mMaxHeap.top())
		{
			// 복사로 전달
			// 현재 최댓값이 바뀐다면 최댓값을 담고있는 큐를 재정렬하여
			// 최댓값을 갱신합니다.
			reArrangeMaxHeap(mQueueStack); 
		}
		else if (front == mMinHeap.top())
		{
			reArrangeMinHeap(mQueueStack);
		}

		return front;
	}

	template <typename T>
	T QueueStack<T>::GetMax() const
	{
		if (mQueueStack.empty() || mQueueStack.front().Empty())
		{
			if (std::is_floating_point<T>::value)
			{
				return std::numeric_limits<T>::lowest();
			}
			else
			{
				return std::numeric_limits<T>::min();
			}
		}

		return mMaxHeap.top();
		//return findMax(mQueueStack);
	}

	template <typename T>
	T QueueStack<T>::GetMin() const
	{
		if (mQueueStack.empty() || mQueueStack.front().Empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mMinHeap.top();
		//return findMin(mQueueStack);
	}

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

	template <typename T>
	bool QueueStack<T>::Empty() const
	{
		return mQueueStack.empty();
	}

	/*
		===========================================
					  private 멤버 함수
		===========================================
	*/

	//template <typename T>
	//T QueueStack<T>::findMax(queueStack qs) const
	//{
	//	//T max = qs.front().GetMax();
	//	//qs.pop();

	//	//while (!qs.empty())
	//	//{
	//	//	if (qs.front().GetMax() > max)
	//	//	{
	//	//		max = qs.front().GetMax();
	//	//	}
	//	//	qs.pop();
	//	//}

	//	//return max;
	//	
	//	// qs.front().Peek() 이 

	//	std::priority_queue<T> pq;
	//	while (!qs.empty())
	//	{
	//		pq.push(qs.front().GetMax());
	//		qs.pop();
	//	}
	//	
	//	return pq.top();
	//}

	//template <typename T>
	//T QueueStack<T>::findMin(queueStack qs) const
	//{
	//	T min = qs.front().GetMin();
	//	qs.pop();

	//	while (!qs.empty())
	//	{
	//		if (qs.front().GetMin() < min)
	//		{
	//			min = qs.front().GetMin();
	//		}
	//		qs.pop();
	//	}

	//	return min;
	//}

	template <typename T>
	void QueueStack<T>::reArrangeMaxHeap(queueStack qs)
	{
		while (!qs.empty())
		{
			mMaxHeap.push(qs.front().GetMax());
			qs.pop();
		}
	}

	template <typename T>
	void QueueStack<T>::reArrangeMinHeap(queueStack qs)
	{
		while (!qs.empty())
		{
			mMinHeap.push(qs.front().GetMin());
			qs.pop();
		}
	}

	
} // namespace
