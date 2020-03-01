#pragma once

#include <cassert>
#include <cmath>
#include <limits>
#include <stack>

namespace assignment3
{
	/*
		===========================================
					enum eRounding 클래스
		===========================================

		소수점 아래 4번째 자리에서 반올림하기 위해 필요한 상수값입니다.
		roundHalfUp 함수의 템플릿 인자로 사용됩니다.
		ex) 3번째 자리 100, 2번째 자리 10, ...
	*/
	enum class eRounding : int16_t
	{
		Four = 1000
	};


	/*
		===========================================
					SmartStack<T> 클래스
		===========================================
	*/
	template <typename T>
	class SmartStack
	{
	public:
		SmartStack();
		SmartStack(const SmartStack& other) = default;
		~SmartStack() = default;
		SmartStack& operator=(const SmartStack& rhs) = default;
		

		void Push(T number);
		T Pop();
		T Peek() const;

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

		// value에 대해 소수 넷째 자리 반올림 default
		inline double roundHalfUp(double value, eRounding n = eRounding::Four) const;


		std::stack<T> mStack;
		std::stack<T> mStoredMax; // 최대값 기록 저장
		std::stack<T> mStoredMin; // 최소값 기록 저장
		T mSum;
		T mExpSum;
	};



	/*
		===========================================
					  public 멤버 함수
		===========================================
	*/

	template <typename T>
	SmartStack<T>::SmartStack()
		: mSum(0)
		, mExpSum(0)
	{
	}

	template<typename T>
	void SmartStack<T>::Push(T number)
	{
		// 스택이 비어있지 않다면 number를 비교하여 Max/Min 스택에 저장합니다.
		if (!mStack.empty())
		{
			if (number >= mStoredMax.top())
			{
				mStoredMax.push(number);
			}
			else if (number <= mStoredMin.top())
			{
				mStoredMin.push(number);
			}
		}
		else
		{
			mStoredMax.push(number);
			mStoredMin.push(number);
		}

		//mStack.push(number >= 0 ? number : number);
		mStack.push(number);
		mSum += number;
		mExpSum += (number * number);
	}

	template<typename T>
	T SmartStack<T>::Pop()
	{
		// 스택이 비어있지 않을 때만 테스트하므로 예외처리하지 않습니다.
		assert(!mStack.empty());

		const T top = mStack.top();
		mStack.pop();
		mSum -= top;
		mExpSum -= (top * top);

		// pop한 값이 최댓값 또는 최솟값이면 Max, Min 스택에서 pop하여 
		// 2번째로 큰(작은)값을 top으로 설정합니다.
		if (top == mStoredMax.top())
		{
			mStoredMax.pop();
		}
		if (top == mStoredMin.top())
		{
			mStoredMin.pop();
		}

		return top;
	}

	template <typename T>
	T SmartStack<T>::Peek() const
	{
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mStack.empty());

		return mStack.top();
	}

	template <typename T>
	T SmartStack<T>::GetMax() const
	{
		if (mStack.empty())
		{
			return std::numeric_limits<T>::min();
		}

		return mStoredMax.top();
	}

	template <typename T>
	T SmartStack<T>::GetMin() const
	{
		if (mStack.empty())
		{
			return std::numeric_limits<T>::max();
		}

		return mStoredMin.top();
	}

	template <>
	float SmartStack<float>::GetMin() const
	{
		if (mStack.empty())
		{
			return std::numeric_limits<float>::lowest();
		}

		return mStoredMin.top();
	}

	template <>
	double SmartStack<double>::GetMin() const
	{
		if (mStack.empty())
		{
			return std::numeric_limits<double>::lowest();
		}

		return mStoredMin.top();
	}



	template <typename T>
	T SmartStack<T>::GetSum() const
	{
		return mSum;
	}

	template <typename T>
	double SmartStack<T>::GetAverage() const
	{
		// 비어있지 않을 경우에만 테스트합니다.
		assert(!mStack.empty());

		// 소수 넷째 자리에서 반올림하여 반환합니다.
		double tmp = mSum / (mStack.size() + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartStack<T>::GetVariance() const
	{
		assert(!mStack.empty());

		// 분산: 각 요소의 제곱의 합을 총개수로 나누고 평균의 제곱을 뺌
		// 넷째 자리에서 반올림하여 반환합니다.

		// 반올림된 평균을 사용하면 오차생김
		double avg = mSum / (mStack.size() + 0.0);
		double tmp = (mExpSum / (mStack.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartStack<T>::GetStandardDeviation() const
	{
		// 표준 편차: 분산의 제곱근
		// 넷째 자리에서 반올림하여 반환합니다.

		double tmpStdDev = sqrt(GetVariance());
		return roundHalfUp(tmpStdDev);
	}

	template <typename T>
	size_t SmartStack<T>::GetCount() const
	{
		return mStack.size();
	}

	template <typename T>
	bool SmartStack<T>::Empty() const
	{
		return mStack.empty();
	}



	/*
		===========================================
					private 멤버 함수
		===========================================
	*/

	// value를 N번째 자리에서 반올림 후 반환합니다.
	template <typename T>
	double SmartStack<T>::roundHalfUp(double value, eRounding n) const
	{
		return std::round(value * static_cast<int>(n)) / static_cast<int>(n);
	}

} // namespace
