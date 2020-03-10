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
		SmartQueue(const SmartQueue& other);
		~SmartQueue();
		SmartQueue<T>& operator=(const SmartQueue& rhs);

		void Enqueue(T number);
		inline const T& Peek() const;
		T& Dequeue();

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
		};

		struct TempStatistic
		{
			double TmpSum;
			double TmpExpSum;
		};

		void copyToThis(const Statistic& source1, const TempStatistic& source2);

		// Max�� Min�� �����մϴ�.
		void updateMax(std::queue<T> q);
		void updateMin(std::queue<T> q);

		std::queue<T> mQueue;
		Statistic* mStatistics;
		TempStatistic* mTempStatistics;
		bool mbMaxChanged;
		bool mbMinChanged;
	};


	/*
		===========================================
					  public ��� �Լ�
		===========================================
	*/

	template <typename T>
	SmartQueue<T>::SmartQueue()
		: mStatistics(new Statistic())
		, mTempStatistics(new TempStatistic())
		, mbMaxChanged(true)
		, mbMinChanged(true)
	{
	}

	template <typename T>
	SmartQueue<T>::~SmartQueue()
	{
		delete mStatistics;
		delete mTempStatistics;
	}

	template <typename T>
	SmartQueue<T>::SmartQueue(const SmartQueue& other)
		: mQueue(other.mQueue)
		, mStatistics(new Statistic())
		, mTempStatistics(new TempStatistic())
		, mbMaxChanged(other.mbMaxChanged)
		, mbMinChanged(other.mbMinChanged)
	{
		copyToThis(*(other.mStatistics), *(other.mTempStatistics));
	}

	template <typename T>
	SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		if (mStatistics)
		{
			delete mStatistics;
		}
		if (mTempStatistics)
		{
			delete mTempStatistics;
		}

		mStatistics = new Statistic();
		mTempStatistics = new TempStatistic();

		mQueue = rhs.mQueue;
		mbMaxChanged = rhs.mbMaxChanged;
		mbMinChanged = rhs.mbMinChanged;
		copyToThis(*(rhs.mStatistics), *(rhs.mTempStatistics));

		return *this;
	}


	template <typename T>
	void SmartQueue<T>::Enqueue(T number)
	{
		if (!mQueue.empty())
		{
			// ù ��Ұ� �ƴ� ��� �߰��Ǵ� ���� Max �� Min�� ���Ͽ� ���� ���θ� �����մϴ�.
			if (number > mStatistics->Max)
			{
				mStatistics->Max = number;
				mbMaxChanged = false;
			}
			if (number < mStatistics->Min)
			{
				mStatistics->Min = number;
				mbMinChanged = false;
			}
		}
		else
		{
			// ù ����� ��� Max�� Min�� number�� �Ҵ��մϴ�.
			mStatistics->Max = number;
			mStatistics->Min = number;
			mbMaxChanged = false;
			mbMinChanged = false;
		}

		mQueue.push(number);
		mStatistics->Sum += number;
		mStatistics->ExpSum += (number * number);
		mTempStatistics->TmpSum += number;
		mTempStatistics->TmpExpSum += (number * number);
	}


	template <typename T>
	const T& SmartQueue<T>::Peek() const
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		return mQueue.front();
	}


	template <typename T>
	T& SmartQueue<T>::Dequeue()
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		T& front = mQueue.front();
		mStatistics->Sum -= front;
		mStatistics->ExpSum -= (front * front);
		mTempStatistics->TmpSum -= front;
		mTempStatistics->TmpExpSum -= (front * front);
		mQueue.pop();


		// Dequeue�� ���� max �Ǵ� min�̿��ٸ� boolean ������ �̿��Ͽ� 
		// GetMax �Ǵ� GetMin ȣ�� �� Max �� Min�� ���� �� ��ȯ�� �� �ֵ��� �մϴ�.
		if (front == mStatistics->Max)
		{
			mbMaxChanged = true;
		}
		if (front == mStatistics->Min)
		{
			mbMinChanged = true;
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

		// Max�� ����Ǿ��� ��� Max ���� �����մϴ�.
		if (mbMaxChanged)
		{
			updateMax(mQueue);
		}

		return mStatistics->Max;
	}

	template <typename T>
	T SmartQueue<T>::GetMin()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		// Min�� ����Ǿ��� ��� Min ���� �����մϴ�.
		if (mbMinChanged)
		{
			updateMin(mQueue);
		}

		return mStatistics->Min;
	}

	template <typename T>
	T SmartQueue<T>::GetSum() const
	{
		return mStatistics->Sum;
	}

	template <typename T>
	double SmartQueue<T>::GetAverage() const
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		// �Ҽ� ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double tmp = mStatistics->Sum / (mQueue.size() + 0.0);
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
		double avg = mTempStatistics->TmpSum / (mQueue.size() + 0.0);
		double tmp = (mTempStatistics->TmpExpSum / (mQueue.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		assert(!mQueue.empty());

		// ǥ�� ����: �л��� ������
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double avg = mTempStatistics->TmpSum / (mQueue.size() + 0.0);
		double variance = (mTempStatistics->TmpExpSum / (mQueue.size() + 0.0)) - (avg * avg);
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

		mStatistics->Max = q.front();
		q.pop();
		T tmp;

		while (!q.empty())
		{
			tmp = q.front();
			if (tmp > mStatistics->Max)
			{
				mStatistics->Max = tmp;
			}
			q.pop();
		}
		mbMaxChanged = false;
	}

	template <typename T>
	void SmartQueue<T>::updateMin(std::queue<T> q)
	{
		assert(!q.empty());

		mStatistics->Min = q.front();
		q.pop();
		T tmp;

		while (!q.empty())
		{
			tmp = q.front();
			if (tmp < mStatistics->Min)
			{
				mStatistics->Min = tmp;
			}
			q.pop();
		}
		mbMinChanged = false;
	}

	template <typename T>
	void SmartQueue<T>::copyToThis(const Statistic& source1, const TempStatistic& source2)
	{
		// source�� this ��ü�� �� ����ü ����� �����մϴ�,.  
		mStatistics->Sum = source1.Sum;
		mStatistics->ExpSum = source1.ExpSum;
		mStatistics->Max = source1.Max;
		mStatistics->Min = source1.Min;

		mTempStatistics->TmpSum = source2.TmpSum;
		mTempStatistics->TmpExpSum = source2.TmpExpSum;
	}

} // namespace
