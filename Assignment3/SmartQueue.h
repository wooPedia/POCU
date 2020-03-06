#pragma once

#include <cassert>
#include <queue>
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
		using maxHeap = std::priority_queue<T>;
		using minHeap = std::priority_queue<T, std::vector<T>, std::greater<T> >;

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
		void rearrangeMaxHeap(std::queue<T> q);
		void rearrangeMinHeap(std::queue<T> q);

		std::queue<T> mQueue;
		maxHeap mMaxHeap;
		minHeap mMinHeap;
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
	{
	}

	template <typename T>
	void SmartQueue<T>::Enqueue(T number)
	{
		if (!mQueue.empty())
		{
			if (number >= mMaxHeap.top())
			{
				mMaxHeap.push(number);
			}
			else if (number <= mMinHeap.top())
			{
				mMinHeap.push(number);
			}
		}
		else
		{
			mMaxHeap.push(number);
			mMinHeap.push(number);
		}

		mQueue.push(number);
		mSum += number;
		mExpSum += (number * number);
	}

	//template <typename T>
	//void SmartQueue<T>::Enqueue(T number)
	//{
	//	mQueue.push(number);
	//	mSum += number;
	//	mExpSum += (number * number);
	//}


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
		mSum -= front;
		mExpSum -= (front * front);
		mQueue.pop();

		if (front == mMaxHeap.top())
		{
			rearrangeMaxHeap(mQueue);
		}
		if (front == mMinHeap.top())
		{
			rearrangeMinHeap(mQueue);
		}

		return front;
	}

	//template <typename T>
	//T SmartQueue<T>::Dequeue()
	//{
	//	// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
	//	assert(!mQueue.empty());

	//	const T front = mQueue.front();
	//	mSum -= front;
	//	mExpSum -= (front * front);
	//	mQueue.pop();

	//	return front;
	//}

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

		//rearrangeMaxHeap(mQueue);
		return mMaxHeap.top();
	}

	template <typename T>
	T SmartQueue<T>::GetMin()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		//rearrangeMinHeap(mQueue);
		return mMinHeap.top();
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
	void SmartQueue<T>::rearrangeMaxHeap(std::queue<T> q)
	{
		// ���� queue�� �켱���� ť�� �־� �ִ��� �����մϴ�.

		mMaxHeap = maxHeap();
		while (!q.empty())
		{
			mMaxHeap.push(q.front());
			q.pop();
		}
	}

	template <typename T>
	void SmartQueue<T>::rearrangeMinHeap(std::queue<T> q)
	{
		mMinHeap = minHeap();
		while (!q.empty())
		{
			mMinHeap.push(q.front());
			q.pop();
		}
	}

} // namespace
