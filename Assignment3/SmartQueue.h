#pragma once

#include <queue>

//#include "ERounding.h"

namespace assignment3
{
	/*
		===========================================
					SmartQueue<T> 클래스
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

		// 추가한 함수
		bool Empty() const;

	private:
		// 큐에서 최대/최소값을 찾아 반환합니다.
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
					  public 멤버 함수
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
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		return mQueue.front();
	}

	template <typename T>
	T SmartQueue<T>::Dequeue()
	{
		// 비어있지 않을 경우에만 테스트합니다.
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
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		// 소수 넷째 자리에서 반올림하여 반환합니다.
		double tmp = mSum / (mQueue.size() + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetVariance() const
	{
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		// 분산: 각 요소의 제곱의 합을 총개수로 나누고 평균의 제곱을 뺌
		// 넷째 자리에서 반올림하여 반환합니다.

		// 반올림된 평균을 사용하면 오차생김
		double avg = mSum / (mQueue.size() + 0.0);
		double tmp = (mExpSum / (mQueue.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		// 표준 편차: 분산의 제곱근
		// 넷째 자리에서 반올림하여 반환합니다.
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
					private 멤버 함수
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
		// 첫 요소로 min을 초기화 후 두 번째 요소부터 비교합니다.
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
