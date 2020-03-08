#pragma once

#include <queue>
#include <cassert>
#include <type_traits>

#include "ERounding.h"

namespace assignment3
{
	/*
		===========================================
					SmartQueue<T> Ŭ����
		===========================================
	*/



	template <typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		SmartQueue(const SmartQueue& other) = default;
		~SmartQueue() = default;
		SmartQueue& operator=(const SmartQueue& rhs) = default;

		void Enqueue(T number);
		inline T Peek() const;
		T Dequeue();

		T GetMax();
		T GetMin();
		inline T GetSum() const;
		inline double GetAverage() const;
		inline double GetVariance() const;
		inline double GetStandardDeviation() const;
		inline size_t GetCount() const;

		// �߰��� �Լ�
		inline bool Empty() const;

	private:

		// ��� ��ġ ���� ����ü
		struct Statistic
		{
			T Sum;
			T ExpSum;
			T Max;
			T Min;
			bool BMaxChanged = true;
			bool BMinChanged = true;
		};

		// Max�� Min�� �����մϴ�.
		void updateMax(std::queue<T> q);
		void updateMin(std::queue<T> q);

		std::queue<T> mQueue;
		Statistic mStatistics;
	};


	/*
		===========================================
					  public ��� �Լ�
		===========================================
	*/

	template <typename T>
	SmartQueue<T>::SmartQueue()
		: mStatistics({})
	{
	}

	template <typename T>
	void SmartQueue<T>::Enqueue(T number)
	{
		mQueue.push(number);
		mStatistics.Sum += number;
		mStatistics.ExpSum += (number * number);
	}


	template <typename T>
	T SmartQueue<T>::Peek() const
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		return mQueue.front();
	}


	template <typename T>
	T SmartQueue<T>::Dequeue()
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		T front = mQueue.front();
		mStatistics.Sum -= front;
		mStatistics.ExpSum -= (front * front);
		mQueue.pop();

		// Dequeue�� ���� max �Ǵ� min�̿��ٸ� boolean ������ �̿��Ͽ� 
		// GetMax �Ǵ� GetMin ȣ�� �� Max �� Min�� ���� �� ��ȯ�� �� �ֵ��� �մϴ�.
		if (front == mStatistics.Max)
		{
			mStatistics.BMaxChanged = true;
		}
		if (front == mStatistics.Min)
		{
			mStatistics.BMinChanged = true;
		}

		return front;
	}

	template <typename T>
	T SmartQueue<T>::GetMax()
	{
		if (mQueue.empty())
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
		if (mStatistics.BMaxChanged)
		{
			updateMax(mQueue);
		}

		return mStatistics.Max;
	}

	template <typename T>
	T SmartQueue<T>::GetMin()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		// Min�� ����Ǿ��� ��� Min ���� ���� �� ��ȯ�մϴ�.
		if (mStatistics.BMinChanged)
		{
			updateMin(mQueue);
		}

		return mStatistics.Min;
	}

	template <typename T>
	T SmartQueue<T>::GetSum() const
	{
		return mStatistics.Sum;
	}

	template <typename T>
	double SmartQueue<T>::GetAverage() const
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		// �Ҽ� ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double tmp = mStatistics.Sum / (mQueue.size() + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetVariance() const
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		// �л�: �� ����� ������ ���� �Ѱ����� ������ ����� ������ ��
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.

		// �ݿø��� ����� ����ϸ� ��������
		double avg = mStatistics.Sum / (mQueue.size() + 0.0);
		double tmp = (mStatistics.ExpSum / (mQueue.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		assert(!mQueue.empty());

		// ǥ�� ����: �л��� ������
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double avg = mStatistics.Sum / (mQueue.size() + 0.0);
		double variance = (mStatistics.ExpSum / (mQueue.size() + 0.0)) - (avg * avg);
		double stdDev = sqrt(variance);

		return roundHalfUp(stdDev);
	}

	template <typename T>
	size_t SmartQueue<T>::GetCount() const
	{
		return mQueue.size();
	}


	template <typename T>
	bool SmartQueue<T>::Empty() const
	{
		return mQueue.empty();
	}

	/*
		===========================================
					private ��� �Լ�
		===========================================
	*/


	template <typename T>
	void SmartQueue<T>::updateMax(std::queue<T> q)
	{
		assert(!q.empty());

		mStatistics.Max = q.front();
		q.pop();
		T tmp;

		while (!q.empty())
		{
			tmp = q.front();
			if (tmp > mStatistics.Max)
			{
				mStatistics.Max = tmp;
			}
			q.pop();
		}
		mStatistics.BMaxChanged = false;
	}

	template <typename T>
	void SmartQueue<T>::updateMin(std::queue<T> q)
	{
		assert(!q.empty());

		mStatistics.Min = q.front();
		q.pop();
		T tmp;

		while (!q.empty())
		{
			tmp = q.front();
			if (tmp < mStatistics.Min)
			{
				mStatistics.Min = tmp;
			}
			q.pop();
		}
		mStatistics.BMinChanged = false;
	}

} // namespace
