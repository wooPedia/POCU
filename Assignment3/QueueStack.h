#pragma once

#include <queue>
#include <stack>
#include <cassert>
#include <type_traits>

#include "ERounding.h"

namespace assignment3
{
	/*
		===========================================
					QueueStack<T> 클래스
		===========================================
	*/

	//template <typename T>
	//class TestQueue : public std::priority_queue<T>
	//{
	//public:

	//	void Push(T number)
	//	{
	//		this->push(number);
	//	}

	//	T Top() const
	//	{
	//		return this->c.front();
	//	}

	//	void Print() const
	//	{
	//		auto iter = this->c.begin();

	//		//for (size_t i = 0; i != this->c.size(); ++i)
	//		//{
	//		//	std::cout << iter[i] << " ";
	//		//}
	//	}

	//	T At(size_t i) const
	//	{
	//		return this->c.at(i);
	//	}

	//	T RBegin() const
	//	{
	//		//return *this->c.rbegin();
	//		auto iter = this->c.rbegin();
	//		//return iter[0];
	//		return *iter;
	//	}

	//	size_t GetLowCount() const
	//	{
	//		size_t height = static_cast<size_t>(log2(this->c.size()));
	//		return static_cast<size_t>(pow(2, height));
	//	}

	//	T GetMin() const
	//	{
	//		assert(!this->c.empty());

	//		auto iter = this->c.rbegin();
	//		T tmp = *iter;

	//		for (size_t i = 0; i != GetLowCount() - 1; ++i)
	//		{
	//			tmp = tmp <= iter[i + 1] ? tmp : iter[i + 1];
	//		}

	//		return tmp;
	//	}

	//};


	template <typename T>
	class QueueStack
	{
	public:
		using queueStack = std::queue<std::stack<T> >;

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
		//void rearrangeMaxHeap(queueStack qs);
		//void rearrangeMinHeap(queueStack qs);
		void findMaxAndMin(queueStack qs);

		queueStack mQueueStack;
		size_t mMaxStackSize;
		T mTotalSum;
		T mMax;
		T mMin;
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
		, mMax(0)
		, mMin(0)
	{
		mQueueStack.push(std::stack<T>());
	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		if (mQueueStack.empty() || mQueueStack.back().size() == mMaxStackSize)
		{
			mQueueStack.push(std::stack<T>());
		}

		if (!mQueueStack.front().empty())
		{
			if (number > mMax)
			{
				mMax = number;
			}
			else if (number < mMin)
			{
				mMin = number;
			}
		}
		else
		{
			mMax = number;
			mMin = number;
		}

		if (mQueueStack.front().size() == mMaxStackSize)
		{
			mQueueStack.back().push(number);
		}
		else
		{
			mQueueStack.front().push(number);
		}

		mTotalSum += number;
	}

	// 첫 요소(스택)의 top을 반환합니다. 
	template <typename T>
	T QueueStack<T>::Peek() const
	{
		assert(!mQueueStack.front().empty());

		return mQueueStack.front().top();
	}

	template <typename T>
	T QueueStack<T>::Dequeue()
	{
		assert(!mQueueStack.empty() && !mQueueStack.front().empty());

		T front = mQueueStack.front().top();
		mQueueStack.front().pop();
		mTotalSum -= front;

		if (mQueueStack.front().empty())
		{
			mQueueStack.pop();
		}

		if (!mQueueStack.empty() && (mQueueStack.front().top() == mMax || mQueueStack.front().top() == mMin))
		{
			findMaxAndMin(mQueueStack);
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

		return mMax;
	}

	template <typename T>
	T QueueStack<T>::GetMin() const
	{
		if (mQueueStack.empty() || mQueueStack.front().empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mMin;
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
			return mQueueStack.front().size() + mQueueStack.back().size() + (mQueueStack.size() - 2) * mMaxStackSize;
		}
		else
		{
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

	//template <typename T>
	//void QueueStack<T>::rearrangeMaxHeap(queueStack qs)
	//{
	//	mMaxHeap = maxHeap();
	//	T tmp;
	//	while (!qs.empty())
	//	{
	//		while (!qs.front().empty())
	//		{
	//			tmp = qs.front().top();
	//			qs.front().pop();
	//			mMaxHeap.push(tmp);
	//		}
	//		qs.pop();
	//	}
	//}

	//template <typename T>
	//void QueueStack<T>::rearrangeMinHeap(queueStack qs)
	//{
	//	mMinHeap = minHeap();
	//	T tmp;
	//	while (!qs.empty())
	//	{
	//		while (!qs.front().empty())
	//		{
	//			tmp = qs.front().top();
	//			qs.front().pop();
	//			mMinHeap.push(tmp);
	//		}
	//		qs.pop();
	//	}
	//}

	template <typename T>
	void QueueStack<T>::findMaxAndMin(queueStack qs)
	{
		mMax = qs.front().top();
		mMin = qs.front().top();
		qs.front().pop();
		T tmp;

		while (!qs.empty())
		{
			while (!qs.front().empty())
			{
				tmp = qs.front().top();
				qs.front().pop();
				if (tmp > mMax)
				{
					mMax = tmp;
				}
				else if (tmp < mMin)
				{
					mMin = tmp;
				}
			}
			qs.pop();
		}
	}

} // namespace
