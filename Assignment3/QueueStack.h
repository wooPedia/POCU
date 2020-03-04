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
		using queueStack2 = std::queue<SmartStack<T> >;
		using queueStack = std::queue<std::stack<T> >;
		using maxHeap = std::priority_queue<T>;
		using minHeap = std::priority_queue<T, std::vector<T>, std::greater<T> >;


		QueueStack() = delete;
		QueueStack(size_t maxStackSize);
		QueueStack(const QueueStack& other) = default;
		~QueueStack() = default;
		QueueStack& operator=(const QueueStack& rhs) = default;

		void Enqueue(T number);
		inline T Peek() const;
		T Dequeue();

		T GetMax() const;
		T GetMin() const;
		inline T GetSum() const;
		inline double GetAverage() const;
		inline size_t GetCount() const;
		inline size_t GetStackCount() const;

		// 추가한 함수
		inline bool Empty() const;

	private:

		// QueueStack에서 최대/최소값을 찾아 반환합니다.
		//void rearrangeMaxHeap(queueStack& qs);
		void rearrangeMaxHeap(queueStack qs);
		void rearrangeMinHeap(queueStack qs);

		queueStack mQueueStack;
		maxHeap mMaxHeap;
		minHeap mMinHeap;

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
		//mQueueStack.push(SmartStack<T>());
		mQueueStack.push(std::stack<T>());
	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		// 사용중인 스택이 비었거나 최대 크기라면 새 스택을 추가합니다.
		//if (mQueueStack.empty() || mQueueStack.back().GetCount() == mMaxStackSize)
		//{
		//	mQueueStack.push(SmartStack<T>());
		//}

		//// 첫 Euqueue가 아닐 경우
		//if (!mQueueStack.front().Empty())
		//{
		//	if (number >= mMaxHeap.top())
		//	{
		//		mMaxHeap.push(number);
		//	}
		//	else if (number <= mMinHeap.top())
		//	{
		//		mMinHeap.push(number);
		//	}
		//}
		//else
		//{
		//	mMaxHeap.push(number);
		//	mMinHeap.push(number);
		//}


		//// 저장가능한 스택에 값을 추가합니다.
		//mQueueStack.back().Push(number);
		//mTotalSum += number;

		if (mQueueStack.empty() || mQueueStack.back().size() == mMaxStackSize)
		{
			mQueueStack.push(std::stack<T>());
		}

		if (mQueueStack.front().size() == mMaxStackSize)
		{
			mQueueStack.back().push(number);
		}
		else
		{
			mQueueStack.front().push(number);
		}

		mMaxHeap.push(number);
		mMinHeap.push(number);
		mTotalSum += number;
	}

	// 첫 요소(스택)의 top을 반환합니다. 
	template <typename T>
	T QueueStack<T>::Peek() const
	{
		//assert(!mQueueStack.front().Empty());
		assert(!mQueueStack.front().empty());

		//return mQueueStack.front().Peek();
		return mQueueStack.front().top();
	}

	template <typename T>
	T QueueStack<T>::Dequeue()
	{
		//assert(!mQueueStack.front().Empty());

		//T front = mQueueStack.front().popForQueueStack();
		//mTotalSum -= front;

		//// 첫 스택이 비었다면 삭제합니다.
		//if (mQueueStack.front().Empty())
		//{
		//	mQueueStack.pop();
		//}

		//if (front == mMaxHeap.top())
		//{
		//	// 복사로 전달
		//	// 현재 최댓값이 바뀐다면 최댓값을 담고있는 우선순위 큐를 재정렬하여
		//	// 최댓값을 갱신합니다.
		//	rearrangeMaxHeap(mQueueStack);
		//}
		//else if (front == mMinHeap.top())
		//{
		//	rearrangeMinHeap(mQueueStack);
		//}

		//return front;

		assert(!mQueueStack.front().empty());

		T front = mQueueStack.front().top();
		mQueueStack.front().pop();
		mTotalSum -= front;

		if (mQueueStack.front().empty())
		{
			mQueueStack.pop();
		}

		if (front == mMaxHeap.top())
		{
			rearrangeMaxHeap(mQueueStack);
		}
		if (front == mMinHeap.top())
		{
			rearrangeMinHeap(mQueueStack);
		}

		return front;
	}

	template <typename T>
	T QueueStack<T>::GetMax() const
	{
		if (mQueueStack.empty() || mQueueStack.front().empty())
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
		if (mQueueStack.empty() || mQueueStack.front().empty())
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
		assert(!mQueueStack.front().empty());

		double tmp = mTotalSum / (GetCount() + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	size_t QueueStack<T>::GetCount() const
	{
		if (mQueueStack.size() >= 2)
		{
			//return mQueueStack.front().GetCount() + mQueueStack.back().GetCount() + (mQueueStack.size() - 2) * mMaxStackSize;
			return mQueueStack.front().size() + mQueueStack.back().size() + (mQueueStack.size() - 2) * mMaxStackSize;
		}
		else
		{
			//return !mQueueStack.empty() ? mQueueStack.front().GetCount() : 0;
			return !mQueueStack.empty() ? mQueueStack.front().size() : 0;
		}
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

	template <typename T>
	void QueueStack<T>::rearrangeMaxHeap(queueStack qs)
	{
		mMaxHeap = maxHeap();
		T tmp;
		while (!qs.empty())
		{
			//mMaxHeap.push(qs.front().GetMax());
			//qs.pop();
			while(!qs.front().empty())
			{
				tmp = qs.front().top();
				qs.front().pop();
				mMaxHeap.push(tmp);
			}
			qs.pop();
		}
	}

	template <typename T>
	void QueueStack<T>::rearrangeMinHeap(queueStack qs)
	{
		mMinHeap = minHeap();
		T tmp;
		while (!qs.empty())
		{
			//mMinHeap.push(qs.front().GetMin());
			//qs.pop();
			while(!qs.front().empty())
			{
				tmp = qs.front().top();
				qs.front().pop();
				mMinHeap.push(tmp);
			}
			qs.pop();
		}
	}


} // namespace
