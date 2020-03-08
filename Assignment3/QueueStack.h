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

		T GetMax();
		T GetMin();
		inline T GetSum() const;
		inline double GetAverage() const;
		inline size_t GetCount() const;
		inline size_t GetStackCount() const;

		// 추가한 함수
		inline bool Empty() const;

	private:
		// 통계 수치 관련 구조체
		struct Statistic
		{
			T Sum;
			T Max;
			T Min;
			bool bMaxChanged = true;
			bool bMinChanged = true;
		};

		void updateMax(queueStack qs);
		void updateMin(queueStack qs);

		queueStack mQueueStack;
		size_t mMaxStackSize;
		size_t mCount;
		Statistic mStatistics;
	};


	/*
		===========================================
					  public 멤버 함수
		===========================================
	*/

	// 큐스택에 들어있는 각 스택의 최대 높이를 인자로 설정합니다.
	template <typename T>
	QueueStack<T>::QueueStack(size_t maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mCount(0)
		, mStatistics({})
	{
		// 빈 스택을 push합니다.
		mQueueStack.push(std::stack<T>());
	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		// 큐스택이 비었거나 첫 스택 및 마지막 스택의 크기가 최대 크기일 경우 스택을 새로 추가합니다. 
		if (mQueueStack.empty() || 
			(mQueueStack.front().size() == mMaxStackSize && mQueueStack.back().size() == mMaxStackSize))
		{
			mQueueStack.push(std::stack<T>());
		}

		if (GetCount() != 0)
		{
			if (number > mStatistics.Max)
			{
				mStatistics.Max = number;
				mStatistics.bMaxChanged = false;
			}
			if (number < mStatistics.Min)
			{
				mStatistics.Min = number;
				mStatistics.bMinChanged = false;
			}
		}
		else
		{
			mStatistics.Max = number;
			mStatistics.Min = number;
			mStatistics.bMaxChanged = false;
			mStatistics.bMinChanged = false;
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
		++mCount;
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
		--mCount;

		// 첫 스택의 요소를 pop 후 스택이 비었다면 스택을 pop 합니다.
		if (mQueueStack.front().empty())
		{
			mQueueStack.pop();
		}

		// Dequeue한 값이 max 또는 min이였다면 boolean 변수를 이용하여 
		// GetMax 또는 GetMin 호출 시 Max 및 Min을 갱신 후 반환할 수 있도록 합니다.
		if (front == mStatistics.Max)
		{
			mStatistics.bMaxChanged = true;
		}
		if (front == mStatistics.Min)
		{
			mStatistics.bMinChanged = true;
		}

		return front;
	}

	template <typename T>
	T QueueStack<T>::GetMax()
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

		// Max가 변경되었을 경우 Max 값을 갱신 후 반환합니다.
		if (mStatistics.bMaxChanged)
		{
			updateMax(mQueueStack);
		}

		return mStatistics.Max;
	}

	template <typename T>
	T QueueStack<T>::GetMin()
	{
		if (mQueueStack.empty() || mQueueStack.front().empty())
		{
			return std::numeric_limits<T>::max();
		}

		// Min이 변경되었을 경우 Min 값을 갱신 후 반환합니다.
		if (mStatistics.bMinChanged)
		{
			updateMin(mQueueStack);
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

		double tmp = mStatistics.Sum / (mCount + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	size_t QueueStack<T>::GetCount() const
	{
		return mCount;
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
	void QueueStack<T>::updateMax(queueStack qs)
	{
		assert(!qs.empty() && !qs.front().empty());

		mStatistics.Max = qs.front().top();
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
			}
			qs.pop();
		}

		// 갱신했으므로 false로 변경합니다.
		mStatistics.bMaxChanged = false;
	}

	template <typename T>
	void QueueStack<T>::updateMin(queueStack qs)
	{
		assert(!qs.empty() && !qs.front().empty());

		mStatistics.Min = qs.front().top();
		qs.front().pop();
		T tmp;

		while (!qs.empty())
		{
			while (!qs.front().empty())
			{
				tmp = qs.front().top();
				qs.front().pop();
				if (tmp < mStatistics.Min)
				{
					mStatistics.Min = tmp;
				}
			}
			qs.pop();
		}

		// 갱신했으므로 false로 변경합니다.
		mStatistics.bMinChanged = false;
	}
} // namespace
