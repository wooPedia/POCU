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
		inline T Peek();
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
		void findMaxAndMin(std::queue<T> q);
		void findMax(std::queue<T> q);
		void findMin(std::queue<T> q);

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
		if (!mQueue.empty())
		{
			if (number > mMax)
			{
				mMax = number;
			}
			else if (number < mMin)
			{
				mMin = number;
			}
		}
		else
		{
			mMax = number;
			mMin = number;
		}

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

		T front = mQueue.front();
		mSum -= front;
		mExpSum -= (front * front);
		mQueue.pop();

		if (!mQueue.empty() && (front == mMax || front == mMin))
		{
			findMaxAndMin(mQueue);
			//rearrangeMaxHeap(mQueue);
		}
		//if (!mQueue.empty())
		//{
		//	if (front == mMax)
		//	{
		//		findMax(mQueue);
		//	}
		//	if (front == mMin)
		//	{
		//		findMin(mQueue);
		//	}
		//}

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

		return mMax;
	}

	template <typename T>
	T SmartQueue<T>::GetMin()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mMin;
	}

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
	void SmartQueue<T>::findMaxAndMin(std::queue<T> q)
	{
		mMax = q.front();
		mMin = q.front();
		q.pop();
		T tmp;

		while (!q.empty())
		{
			tmp = q.front();
			if (tmp > mMax)
			{
				mMax = tmp;
			}
			else if (tmp < mMin)
			{
				mMin = tmp;
			}
			q.pop();
		}
	}


	template <typename T>
	void SmartQueue<T>::findMax(std::queue<T> q)
	{
		mMax = q.front();
		q.pop();
		T tmp;

		while (!q.empty())
		{
			tmp = q.front();
			if (tmp > mMax)
			{
				mMax = tmp;
			}
			q.pop();
		}
	}

	template <typename T>
	void SmartQueue<T>::findMin(std::queue<T> q)
	{
		mMin = q.front();
		q.pop();
		T tmp;

		while (!q.empty())
		{
			tmp = q.front();
			if (tmp < mMin)
			{
				mMin = tmp;
			}
			q.pop();
		}
	}

} // namespace
