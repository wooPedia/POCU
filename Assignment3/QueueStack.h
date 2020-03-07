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
					QueueStack<T> Ŭ����
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

		// �߰��� �Լ�
		inline bool Empty() const;

	private:
		// ��� ��ġ ���� ����ü
		struct Statistic
		{
			T Sum;
			T Max;
			T Min;
		};
		void updateMaxAndMin(queueStack qs);

		queueStack mQueueStack;
		size_t mMaxStackSize;
		Statistic mStatistics;
		bool mMaxChanged;
		bool mMinChanged;
	};


	/*
		===========================================
					  public ��� �Լ�
		===========================================
	*/

	// ť���ÿ� ����ִ� �� ������ �ִ� ���̸� ���ڷ� �����մϴ�.
	template <typename T>
	QueueStack<T>::QueueStack(size_t maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mStatistics({})
		, mMaxChanged(true)
		, mMinChanged(true)
	{
		// �� ������ push�մϴ�.
		mQueueStack.push(std::stack<T>());
	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		// ť������ ����ų� ������ ������ ũ�Ⱑ �ִ� ũ���� ��� ������ ���� �߰��մϴ�. 
		if (mQueueStack.empty() || mQueueStack.back().size() == mMaxStackSize)
		{
			mQueueStack.push(std::stack<T>());
		}

		// Max���� Min���� ���ε��� number�� ���Ͽ� ����ϴ�.
		//if (!mQueueStack.front().empty())
		//{
		//	if (number > mStatistics.Max)
		//	{
		//		mStatistics.Max = number;
		//	}
		//	else if (number < mStatistics.Min)
		//	{
		//		mStatistics.Min = number;
		//	}
		//}
		//else 
		//{ 
		//	// ù ��Ҷ�� Max, Min ��� reset �����ݴϴ�.
		//	mStatistics.Max = number;
		//	mStatistics.Min = number;
		//}

		// ù ������ �� á�ٸ� �� �ڿ� push�ϰ� �׷��� ������ ù ���ÿ� push�մϴ�.
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

	// ù ���(����)�� top�� ��ȯ�մϴ�. 
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

		// ù ������ ��Ҹ� pop �� ������ ����ٸ� ������ pop �մϴ�.
		if (mQueueStack.front().empty())
		{
			mQueueStack.pop();
		}

		// ť������ ������� �ʰ� Dequeue�� ���� max �Ǵ� min�̶�� max�� min�� �����մϴ�.
		if (!mQueueStack.empty() && (front == mStatistics.Max || front == mStatistics.Min))
		{
			//updateMaxAndMin(mQueueStack);
			mMaxChanged = true;
			mMinChanged = true;
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

		//if (mMaxChanged || mMinChanged)
		if (mMaxChanged)
		{
			updateMaxAndMin(mQueueStack);
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

		//if (mMaxChanged || mMinChanged)
		if (mMinChanged)
		{
			updateMaxAndMin(mQueueStack);
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
					  private ��� �Լ�
		===========================================
	*/

	template <typename T>
	void QueueStack<T>::updateMaxAndMin(queueStack qs)
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

		mMaxChanged = false;
		mMinChanged = false;
	}

} // namespace
