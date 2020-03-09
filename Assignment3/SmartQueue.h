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
			double TmpSum;
			double TmpExpSum;
			T Max;
			T Min;
		};

		void copyToThis(const Statistic& source);

		// Max�� Min�� �����մϴ�.
		void updateMax(std::queue<T> q);
		void updateMin(std::queue<T> q);

		std::queue<T> mQueue;
		Statistic* mStatistics;
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
		, mbMaxChanged(true)
		, mbMinChanged(true)
	{
	}

	template <typename T>
	SmartQueue<T>::~SmartQueue()
	{
		delete mStatistics;
	}

	template <typename T>
	SmartQueue<T>::SmartQueue(const SmartQueue& other)
		: mQueue(other.mQueue)
		, mStatistics(new Statistic())
		, mbMaxChanged(other.mbMaxChanged)
		, mbMinChanged(other.mbMinChanged)
	{
		copyToThis(*(other.mStatistics));
	}

	template <typename T>
	SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		if (this->mStatistics)
		{
			delete mStatistics;
		}

		mStatistics = new Statistic();

		mQueue = rhs.mQueue;
		mbMaxChanged = rhs.mbMaxChanged;
		mbMinChanged = rhs.mbMinChanged;
		copyToThis(*(rhs.mStatistics));

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
		mStatistics->TmpSum += number;
		mStatistics->ExpSum += (number * number);
		mStatistics->TmpExpSum += (number * number);
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
		mStatistics->Sum -= front;
		mStatistics->TmpSum -= front;
		mStatistics->ExpSum -= (front * front);
		mStatistics->TmpExpSum -= (front * front);
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
		double avg = mStatistics->TmpSum / (mQueue.size() + 0.0);
		double tmp = (mStatistics->TmpExpSum / (mQueue.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		assert(!mQueue.empty());

		// ǥ�� ����: �л��� ������
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double avg = mStatistics->TmpSum / (mQueue.size() + 0.0);
		double variance = (mStatistics->TmpExpSum / (mQueue.size() + 0.0)) - (avg * avg);
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
	void SmartQueue<T>::copyToThis(const Statistic& source)
	{
		// source�� this ��ü�� �� ����ü ����� �����մϴ�,.  
		mStatistics->Sum = source.Sum;
		mStatistics->ExpSum = source.ExpSum;
		mStatistics->TmpSum = source.TmpSum;
		mStatistics->TmpExpSum = source.TmpExpSum;
		mStatistics->Max = source.Max;
		mStatistics->Min = source.Min;
	}

} // namespace
