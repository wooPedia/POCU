#pragma once

#include <queue>
#include <cassert>
#include <type_traits>

#include "ERounding.h"

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
		inline T Peek() const;
		T Dequeue();

		T GetMax();
		T GetMin();
		inline T GetSum() const;
		inline double GetAverage() const;
		inline double GetVariance() const;
		inline double GetStandardDeviation() const;
		inline size_t GetCount() const;

		// 추가한 함수
		inline bool Empty() const;

	private:

		// 통계 수치 관련 구조체
		struct Statistic
		{
			T Sum;
			T ExpSum;
			T Max;
			T Min;
			bool BMaxChanged = true;
			bool BMinChanged = true;
		};

		// Max와 Min을 갱신합니다.
		void updateMax(std::queue<T> q);
		void updateMin(std::queue<T> q);

		std::queue<T> mQueue;
		Statistic mStatistics;
	};


	/*
		===========================================
					  public 멤버 함수
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
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		return mQueue.front();
	}


	template <typename T>
	T SmartQueue<T>::Dequeue()
	{
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		T front = mQueue.front();
		mStatistics.Sum -= front;
		mStatistics.ExpSum -= (front * front);
		mQueue.pop();

		// Dequeue한 값이 max 또는 min이였다면 boolean 변수를 이용하여 
		// GetMax 또는 GetMin 호출 시 Max 및 Min을 갱신 후 반환할 수 있도록 합니다.
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

		// Max가 변경되었을 경우 Max 값을 갱신 후 반환합니다.
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

		// Min이 변경되었을 경우 Min 값을 갱신 후 반환합니다.
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
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		// 소수 넷째 자리에서 반올림하여 반환합니다.
		double tmp = mStatistics.Sum / (mQueue.size() + 0.0);
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
		double avg = mStatistics.Sum / (mQueue.size() + 0.0);
		double tmp = (mStatistics.ExpSum / (mQueue.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		assert(!mQueue.empty());

		// 표준 편차: 분산의 제곱근
		// 넷째 자리에서 반올림하여 반환합니다.
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
					private 멤버 함수
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
