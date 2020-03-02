#pragma once

#include <queue>

//#include "ERounding.h"

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
		T Peek();
		T Dequeue();

		T GetMax() const;
		T GetMin() const;
		inline T GetSum() const;
		double GetAverage() const;
		double GetVariance() const;
		double GetStandardDeviation() const;
		inline size_t GetCount() const;

		// �߰��� �Լ�
		bool Empty() const;

	private:
		// ť���� �ִ�/�ּҰ��� ã�� ��ȯ�մϴ�.
		T findMax(std::queue<T> q) const;
		T findMin(std::queue<T> q) const;
		
		std::queue<T> mQueue;
		T mMax;
		T mMin;
		T mSum;
		T mExpSum;
	};


	/*
		===========================================
					  public ��� �Լ�
		===========================================
	*/

	template <typename T>
	SmartQueue<T>::SmartQueue()
		: mSum(0)
		, mExpSum(0)
		, mMax(0)
		, mMin(0)
	{
	}

	template <typename T>
	void SmartQueue<T>::Enqueue(T number)
	{
		mQueue.push(number);
		mSum += number;
		mExpSum += (number * number);
	}

	template <typename T>
	T SmartQueue<T>::Peek()
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

		const T front = mQueue.front();
		mQueue.pop();
		mSum -= front;
		mExpSum -= (front * front);

		return front;
	}

	template <typename T>
	T SmartQueue<T>::GetMax() const
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::min();
		}

		return findMax(mQueue);
	}

	template <typename T>
	T SmartQueue<T>::GetMin() const
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		return findMin(mQueue);
	}

	template <>
	float SmartQueue<float>::GetMin() const;
	
	template <>
	double SmartQueue<double>::GetMin() const;

	template <typename T>
	T SmartQueue<T>::GetSum() const
	{
		return mSum;
	}

	template <typename T>
	double SmartQueue<T>::GetAverage() const
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mQueue.empty());

		// �Ҽ� ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double tmp = mSum / (mQueue.size() + 0.0);
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
		double avg = mSum / (mQueue.size() + 0.0);
		double tmp = (mExpSum / (mQueue.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		// ǥ�� ����: �л��� ������
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double tmpStdDev = sqrt(GetVariance());
		return roundHalfUp(tmpStdDev);
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
	T SmartQueue<T>::findMax(std::queue<T> q) const
	{
		T max = q.front();
		q.pop();

		while (!q.empty())
		{
			if (q.front() > max)
			{
				max = q.front();
			}
			q.pop();
		}

		return max;
	}

	template <typename T>
	T SmartQueue<T>::findMin(std::queue<T> q) const
	{
		// ù ��ҷ� min�� �ʱ�ȭ �� �� ��° ��Һ��� ���մϴ�.
		T min = q.front();
		q.pop();

		while (!q.empty())
		{
			if (q.front() < min)
			{
				min = q.front();
			}
			q.pop();
		}

		return min;
	}

} // namespace
