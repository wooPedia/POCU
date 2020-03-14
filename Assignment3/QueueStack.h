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
		inline const T& Peek() const;
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
			T Sum{};
			T Max{};
			T Min{};

			// true라면 GetMax/GetMin 함수 호출 시 Max/Min 값을 갱신합니다.
			// false라면 갱신하지 않고 반환합니다.
			bool bMaxChanged = true;
			bool bMinChanged = true;
		};

		// Max와 Min을 갱신합니다.
		// 인자는 복사로 전달합니다.
		void updateMax(queueStack qs);
		void updateMin(queueStack qs);

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

		return *this;
	}


	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		// 각 스택의 최대 크기가 0일 경우 빈 스택만 추가 후 요소를 추가하지 않습니다.
		if (mMaxStackSize == 0)
		{
			return;
		}

		// 큐가 비었거나 마지막 스택이 모두 꽉 찼을 경우 새 스택을 추가합니다.
		if (mQueueStack.empty() || mQueueStack.back().size() == mMaxStackSize)
		{
			mQueueStack.emplace(std::stack<T>());
		}

		if (!mQueueStack.front().empty())
		{
			if (number > mStatistics->Max)
			{
				mStatistics->Max = number;
				mStatistics->bMaxChanged = false;
			}
			if (number < mStatistics->Min)
			{
				mStatistics->Min = number;
				mStatistics->bMinChanged = false;
			}
		}
		else
		{
			mStatistics->Max = number;
			mStatistics->Min = number;
			mStatistics->bMaxChanged = false;
			mStatistics->bMinChanged = false;
		}


		mQueueStack.back().push(number);
		mStatistics->Sum += number;
	}

	template <typename T>
	inline const T& QueueStack<T>::Peek() const
	{
		assert(!mQueueStack.empty() && !mQueueStack.front().empty());

		// 제일 첫 번째 스택의 top을 반환합니다.
		return mQueueStack.front().top();
	}

	template <typename T>
	T QueueStack<T>::Dequeue()
	{
		assert(!mQueueStack.empty() && !mQueueStack.front().empty());

		if (mMaxStackSize == 0 && !mQueueStack.empty())
		{
			return NULL;
		}

		T front = mQueueStack.front().top();
		mQueueStack.front().pop();
		mStatistics->Sum -= front;

		// 삭제된 값이 Max 또는 Min이라면 GetMax 또는 GetMin 호출 시 
		// Max/Min을 갱신하고 반환하도록 합니다.
		if (front == mStatistics->Max)
		{
			mStatistics->bMaxChanged = true;
		}
		if (front == mStatistics->Min)
		{
			mStatistics->bMinChanged = true;
		}

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

		// Max가 변경되었을 경우 Max 값을 갱신합니다.
		if (mStatistics->bMaxChanged)
		{
			updateMax(mQueueStack);
		}

		return mStatistics->Max;
	}

	template <typename T>
	T QueueStack<T>::GetMin()
	{
		if (mQueueStack.empty() || mQueueStack.front().empty())
		{
			return std::numeric_limits<T>::max();
		}

		// Min이 변경되었을 경우 Min 값을 갱신합니다.
		if (mStatistics->bMinChanged)
		{
			updateMin(mQueueStack);
		}

		return mStatistics->Min;
	}

	template <typename T>
	inline T QueueStack<T>::GetSum() const
	{
		return mStatistics->Sum;
	}

	template <typename T>
	inline double QueueStack<T>::GetAverage() const
	{
		double avg = (mStatistics->Sum + 0.0) / GetCount();
		return roundHalfUp(avg);
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

		mStatistics->Max = qs.front().top();
		qs.front().pop();
		T tmp;

		while (!qs.empty())
		{
			while (!qs.front().empty())
			{
				tmp = qs.front().top();
				qs.front().pop();
				if (tmp > mStatistics->Max)
				{
					mStatistics->Max = tmp;
				}
			}
			qs.pop();
		}

		// 갱신했으므로 false로 변경합니다.
		mStatistics->bMaxChanged = false;
	}

	template <typename T>
	void QueueStack<T>::updateMin(queueStack qs)
	{
		assert(!qs.empty() && !qs.front().empty());

		mStatistics->Min = qs.front().top();
		qs.front().pop();
		T tmp;

		while (!qs.empty())
		{
			while (!qs.front().empty())
			{
				tmp = qs.front().top();
				qs.front().pop();
				if (tmp < mStatistics->Min)
				{
					mStatistics->Min = tmp;
				}
			}
			qs.pop();
		}

		// 갱신했으므로 false로 변경합니다.
		mStatistics->bMinChanged = false;
	}

} // namespace
