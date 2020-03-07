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
		struct Statistic
		{
			T Sum;
			T Max;
			T Min;
		};
		//void rearrangeMaxHeap(queueStack qs);
		//void rearrangeMinHeap(queueStack qs);
		void findMaxAndMin(queueStack qs);

		queueStack mQueueStack;
		size_t mMaxStackSize;
		Statistic mStatistics;
	};


	/*
		===========================================
					  public 멤버 함수
		===========================================
	*/

	template <typename T>
	QueueStack<T>::QueueStack(size_t maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mStatistics({})
	{
		// 빈 스택을 push합니다.
		mQueueStack.push(std::stack<T>());
	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		// 큐스택이 비었거나 마지막 스택의 크기가 최대 크기일 경우 스택을 새로 추가합니다. 
		if (mQueueStack.empty() || mQueueStack.back().size() == mMaxStackSize)
		{
			mQueueStack.push(std::stack<T>());
		}

		// Max값과 Min값을 새로들어온 number와 비교하여 얻습니다.
		if (!mQueueStack.front().empty())
		{
			if (number > mStatistics.Max)
			{
				mStatistics.Max = number;
			}
			else if (number < mStatistics.Min)
			{
				mStatistics.Min = number;
			}
		}
		else
		{ // 첫 요소라면 Max, Min 모두 reset 시켜줍니다.
			mStatistics.Max = number;
			mStatistics.Min = number;
		}

		// 첫 스택이 꽉 찼다면 맨 뒤에 push하고 그렇지 않으면 첫 스택에 push합니다.
		if (mQueueStack.front().size() == mMaxStackSize)
		{
			mQueueStack.back().push(number);
		}
		else
		{
			mQueueStack.front().push(number);
		}

		mStatistics.Sum += number;
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
		mStatistics.Sum -= front;

		// 첫 스택의 요소를 pop 후 스택이 비었다면 스택을 pop 합니다.
		if (mQueueStack.front().empty())
		{
			mQueueStack.pop();
		}

		// 
		if (!mQueueStack.empty() && (front == mStatistics.Max || front == mStatistics.Min))
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

		return mStatistics.Max;
	}

	template <typename T>
	T QueueStack<T>::GetMin() const
	{
		if (mQueueStack.empty() || mQueueStack.front().empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mStatistics.Min;
	}

	template <typename T>
	T QueueStack<T>::GetSum() const
	{
		return mStatistics.Sum;
	}

	template <typename T>
	double QueueStack<T>::GetAverage() const
	{
		assert(!mQueueStack.front().empty());

		double tmp = mStatistics.Sum / (GetCount() + 0.0);
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
		mStatistics.Max = qs.front().top();
		mStatistics.Min = qs.front().top();
		qs.front().pop();
		T tmp;

		while (!qs.empty())
		{
			while (!qs.front().empty())
			{
				tmp = qs.front().top();
				qs.front().pop();
				if (tmp > mStatistics.Max)
				{
					mStatistics.Max = tmp;
				}
				else if (tmp < mStatistics.Min)
				{
					mStatistics.Min = tmp;
				}
			}
			qs.pop();
		}
	}

} // namespace
