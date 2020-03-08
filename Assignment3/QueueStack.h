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
					  public ��� �Լ�
		===========================================
	*/

	// ť���ÿ� ����ִ� �� ������ �ִ� ���̸� ���ڷ� �����մϴ�.
	template <typename T>
	QueueStack<T>::QueueStack(size_t maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mCount(0)
		, mStatistics({})
	{
		// �� ������ push�մϴ�.
		mQueueStack.push(std::stack<T>());
	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		// ť������ ����ų� ù ���� �� ������ ������ ũ�Ⱑ �ִ� ũ���� ��� ������ ���� �߰��մϴ�. 
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
		++mCount;
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
		--mCount;

		// ù ������ ��Ҹ� pop �� ������ ����ٸ� ������ pop �մϴ�.
		if (mQueueStack.front().empty())
		{
			mQueueStack.pop();
		}

		// Dequeue�� ���� max �Ǵ� min�̿��ٸ� boolean ������ �̿��Ͽ� 
		// GetMax �Ǵ� GetMin ȣ�� �� Max �� Min�� ���� �� ��ȯ�� �� �ֵ��� �մϴ�.
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

		// Max�� ����Ǿ��� ��� Max ���� ���� �� ��ȯ�մϴ�.
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

		// Min�� ����Ǿ��� ��� Min ���� ���� �� ��ȯ�մϴ�.
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
					  private ��� �Լ�
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

		// ���������Ƿ� false�� �����մϴ�.
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

		// ���������Ƿ� false�� �����մϴ�.
		mStatistics.bMinChanged = false;
	}
} // namespace
