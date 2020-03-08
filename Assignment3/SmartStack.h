#pragma once

#include <stack>
#include <cassert>
#include <type_traits>

#include "ERounding.h"

namespace assignment3
{
	/*
		===========================================
					SmartStack<T> Ŭ����
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
		inline T Peek() const;

		T GetMax() const;
		T GetMin() const;
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
		};

		std::stack<T> mStack;
		std::stack<T> mStoredMax; // �ִ밪 ��� ����
		std::stack<T> mStoredMin; // �ּҰ� ��� ����
		Statistic mStatistics;
	};



	/*
		===========================================
					  public ��� �Լ�
		===========================================
	*/

	template <typename T>
	SmartStack<T>::SmartStack()
		: mStatistics({})
	{
	}


	template<typename T>
	void SmartStack<T>::Push(T number)
	{
		// ������ ������� �ʴٸ� number�� ���Ͽ� Max/Min ���ÿ� �����մϴ�.
		if (!mStack.empty())
		{
			if (number >= mStoredMax.top())
			{
				mStoredMax.push(number);
			}
			if (number <= mStoredMin.top())
			{
				mStoredMin.push(number);
			}
		}
		else
		{
			mStoredMax.push(number);
			mStoredMin.push(number);
		}

		mStack.push(number);
		mStatistics.Sum += number;
		mStatistics.ExpSum += (number * number);

		mStatistics.TmpSum += number;
		mStatistics.TmpExpSum += (number * number);
	}

	template<typename T>
	T SmartStack<T>::Pop()
	{
		// ������ ������� ���� ���� �׽�Ʈ�ϹǷ� ����ó������ �ʽ��ϴ�.
		assert(!mStack.empty());

		T top = mStack.top();
		mStack.pop();
		mStatistics.Sum -= top;
		mStatistics.ExpSum -= (top * top);

		mStatistics.TmpSum -= top;
		mStatistics.TmpExpSum -= (top * top);

		assert(!mStoredMax.empty() && !mStoredMin.empty());

		// pop�� ���� �ִ� �Ǵ� �ּڰ��̸� Max, Min ���ÿ��� pop�Ͽ� 
		// 2��°�� ū(����)���� top���� �����մϴ�.
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
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mStack.empty());

		return mStack.top();
	}

	template <typename T>
	T SmartStack<T>::GetMax() const
	{
		if (mStack.empty())
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

		assert(!mStoredMax.empty());
		return mStoredMax.top();
	}


	template <typename T>
	T SmartStack<T>::GetMin() const
	{
		if (mStack.empty())
		{
			return std::numeric_limits<T>::max();
		}

		assert(!mStoredMin.empty());
		return mStoredMin.top();
	}


	template <typename T>
	T SmartStack<T>::GetSum() const
	{
		return mStatistics.Sum;
	}

	template <typename T>
	double SmartStack<T>::GetAverage() const
	{
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mStack.empty());

		// �Ҽ� ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double tmp = mStatistics.Sum / (mStack.size() + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartStack<T>::GetVariance() const
	{
		assert(!mStack.empty());

		// �л�: �� ����� ������ ���� �Ѱ����� ������ ����� ������ ��
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.

		// �ݿø��� ����� ����ϸ� ��������
		double avg = mStatistics.TmpSum / (mStack.size() + 0.0);
		double variance = (mStatistics.TmpExpSum / (mStack.size() + 0.0)) - (avg * avg);

		return roundHalfUp(variance);
	}

	template <typename T>
	double SmartStack<T>::GetStandardDeviation() const
	{
		assert(!mStack.empty());

		// ǥ�� ����: �л��� ������
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.

		double avg = mStatistics.TmpSum / (mStack.size() + 0.0);
		double variance = (mStatistics.TmpExpSum / (mStack.size() + 0.0)) - (avg * avg);
		double stdDev = sqrt(variance);

		return roundHalfUp(stdDev);
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
					  private ��� �Լ�
		===========================================
	*/


} // namespace
