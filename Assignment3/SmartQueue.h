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
		};

		struct TempStatistic
		{
			double TmpSum;
			double TmpExpSum;
		};

		void copyToThis(const Statistic& source1, const TempStatistic& source2);

		// Max와 Min을 갱신합니다.
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
					  public 멤버 함수
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
			// 첫 요소가 아닐 경우 추가되는 값과 Max 및 Min을 비교하여 변경 여부를 설정합니다.
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
			// 첫 요소일 경우 Max와 Min을 number로 할당합니다.
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
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		return mQueue.front();
	}


	template <typename T>
	T& SmartQueue<T>::Dequeue()
	{
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		T& front = mQueue.front();
		mStatistics->Sum -= front;
		mStatistics->ExpSum -= (front * front);
		mTempStatistics->TmpSum -= front;
		mTempStatistics->TmpExpSum -= (front * front);
		mQueue.pop();


		// Dequeue한 값이 max 또는 min이였다면 boolean 변수를 이용하여 
		// GetMax 또는 GetMin 호출 시 Max 및 Min을 갱신 후 반환할 수 있도록 합니다.
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

		// Max가 변경되었을 경우 Max 값을 갱신합니다.
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

		// Min이 변경되었을 경우 Min 값을 갱신합니다.
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
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mQueue.empty());

		// 소수 넷째 자리에서 반올림하여 반환합니다.
		double tmp = mStatistics->Sum / (mQueue.size() + 0.0);
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
		double avg = mTempStatistics->TmpSum / (mQueue.size() + 0.0);
		double tmp = (mTempStatistics->TmpExpSum / (mQueue.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartQueue<T>::GetStandardDeviation() const
	{
		assert(!mQueue.empty());

		// 표준 편차: 분산의 제곱근
		// 넷째 자리에서 반올림하여 반환합니다.
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
					private 멤버 함수
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
		// source를 this 개체의 각 구조체 멤버에 복사합니다,.  
		mStatistics->Sum = source1.Sum;
		mStatistics->ExpSum = source1.ExpSum;
		mStatistics->Max = source1.Max;
		mStatistics->Min = source1.Min;

		mTempStatistics->TmpSum = source2.TmpSum;
		mTempStatistics->TmpExpSum = source2.TmpExpSum;
	}

} // namespace
