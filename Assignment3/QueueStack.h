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

		// �߰��� �Լ�
		inline bool Empty() const;

	private:

		struct Statistic
		{
			T Sum{};
			T Max{};
			T Min{};

			// true��� GetMax/GetMin �Լ� ȣ�� �� Max/Min ���� �����մϴ�.
			// false��� �������� �ʰ� ��ȯ�մϴ�.
			bool bMaxChanged = true;
			bool bMinChanged = true;
		};

		// Max�� Min�� �����մϴ�.
		// ���ڴ� ����� �����մϴ�.
		void updateMax(queueStack qs);
		void updateMin(queueStack qs);

		queueStack mQueueStack;
		size_t mMaxStackSize;
		Statistic* mStatistics;
	};

	/*
		===========================================
					  public ��� �Լ�
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
		// �� ������ �ִ� ũ�Ⱑ 0�� ��� �� ���ø� �߰� �� ��Ҹ� �߰����� �ʽ��ϴ�.
		if (mMaxStackSize == 0)
		{
			return;
		}

		// ť�� ����ų� ������ ������ ��� �� á�� ��� �� ������ �߰��մϴ�.
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

		// ���� ù ��° ������ top�� ��ȯ�մϴ�.
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

		// ������ ���� Max �Ǵ� Min�̶�� GetMax �Ǵ� GetMin ȣ�� �� 
		// Max/Min�� �����ϰ� ��ȯ�ϵ��� �մϴ�.
		if (front == mStatistics->Max)
		{
			mStatistics->bMaxChanged = true;
		}
		if (front == mStatistics->Min)
		{
			mStatistics->bMinChanged = true;
		}

		// ù ������ ����ٸ� pop�մϴ�.
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

		// Max�� ����Ǿ��� ��� Max ���� �����մϴ�.
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

		// Min�� ����Ǿ��� ��� Min ���� �����մϴ�.
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
		// ������ 2�� �̻��� ���
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

	// �߰��� �Լ�
	template <typename T>
	inline bool QueueStack<T>::Empty() const
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

		// ���������Ƿ� false�� �����մϴ�.
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

		// ���������Ƿ� false�� �����մϴ�.
		mStatistics->bMinChanged = false;
	}

} // namespace
