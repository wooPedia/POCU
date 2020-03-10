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
		using queueStack = std::queue<std::stack<T>>;

		QueueStack() = delete;
		QueueStack(size_t maxStackSize);
		QueueStack(const QueueStack& other);
		~QueueStack();
		QueueStack<T>& operator=(const QueueStack& rhs);

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

		struct Statistic
		{
			T Sum;
			double TmpSum;
		};


		queueStack mQueueStack;
		size_t mMaxStackSize;
		Statistic* mStatistics;
	};

	/*
		===========================================
					  public 멤버 함수
		===========================================
	*/

	template <typename T>
	QueueStack<T>::QueueStack(size_t maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mStatistics(new Statistic())
	{
	}

	template <typename T>
	QueueStack<T>::QueueStack(const QueueStack& other)
		: mQueueStack(other.mQueueStack)
		, mMaxStackSize(other.mMaxStackSize)
	{
		mStatistics = new Statistic();
		mStatistics->Sum = other.mStatistics->Sum;
		mStatistics->TmpSum = other.mStatistics->TmpSum;
	}

	template <typename T>
	QueueStack<T>::~QueueStack()
	{
		delete mStatistics;
	}

	template <typename T>
	QueueStack<T>& QueueStack<T>::operator=(const QueueStack& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		delete mStatistics;
		mStatistics = new Statistic();

		mQueueStack = rhs.mQueueStack;
		mStatistics->Sum = rhs.mStatistics->Sum;
		mStatistics->TmpSum = rhs.mStatistics->TmpSum;

		return *this;
	}


	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		// 각 스택의 최대 크기가 0일 경우 요소를 추가하지 않습니다.
		if (mMaxStackSize == 0)
		{
			return;
		}

		// 큐가 비었거나 첫 스택과 마지막 스택이 모두 꽉 찼을 경우 새 스택을 추가합니다.
		if (mQueueStack.empty() ||
			(mQueueStack.front().size() == mMaxStackSize && mQueueStack.back().size() == mMaxStackSize))
		{
			mQueueStack.emplace(std::stack<T>());
		}

		// 첫 스택이 비었다면 첫 스택에, 꽉 찼다면 마지막 스택에 저장합니다.
		if (mQueueStack.front().size() == mMaxStackSize)
		{
			mQueueStack.back().push(number);
		}
		else
		{
			mQueueStack.front().push(number);
		}

		mStatistics->Sum += number;
		mStatistics->TmpSum += number;
	}

	template <typename T>
	inline T QueueStack<T>::Peek() const
	{
		assert(!mQueueStack.empty() && !mQueueStack.front().empty());

		// 제일 첫 번째 스택의 top을 반환합니다.
		return mQueueStack.front().top();
	}

	template <typename T>
	T QueueStack<T>::Dequeue()
	{
		assert(!mQueueStack.empty() && !mQueueStack.front().empty());

		T front = mQueueStack.front().top();
		mQueueStack.front().pop();
		mStatistics->Sum -= front;
		mStatistics->TmpSum -= front;

		// 첫 스택이 비었다면 pop합니다.
		if (mQueueStack.front().empty())
		{
			mQueueStack.pop();
		}

		return front;
	}

	template <typename T>
	T QueueStack<T>::GetMax()
	{
		return T();
	}

	template <typename T>
	T QueueStack<T>::GetMin()
	{
		return T();
	}

	template <typename T>
	inline T QueueStack<T>::GetSum() const
	{
		return T();
	}

	template <typename T>
	inline double QueueStack<T>::GetAverage() const
	{
		return double();
	}

	template <typename T>
	inline size_t QueueStack<T>::GetCount() const
	{
		// 스택이 2개 이상일 경우
		if (mQueueStack.size() >= 2)
		{
			return mQueueStack.front().size() + mQueueStack.back().size() + (mMaxStackSize * (mQueueStack.size() - 2));
		}
		else
		{
			return !mQueueStack.empty() ? mQueueStack.front().size() : 0;
		}
	}

	template <typename T>
	inline size_t QueueStack<T>::GetStackCount() const
	{
		return mQueueStack.size();
	}

	// 추가한 함수
	template <typename T>
	inline bool QueueStack<T>::Empty() const
	{
		return true;
	}


	/*
		===========================================
					  private 멤버 함수
		===========================================
	*/

} // namespace
