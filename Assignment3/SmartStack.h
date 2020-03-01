#pragma once

#include <cassert>
#include <cmath>
#include <limits>
#include <stack>

namespace assignment3
{
	/*
		===========================================
					enum eRounding Ŭ����
		===========================================

		�Ҽ��� �Ʒ� 4��° �ڸ����� �ݿø��ϱ� ���� �ʿ��� ������Դϴ�.
		roundHalfUp �Լ��� ���ø� ���ڷ� ���˴ϴ�.
		ex) 3��° �ڸ� 100, 2��° �ڸ� 10, ...
	*/
	enum class eRounding : int16_t
	{
		Four = 1000
	};


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
		T Peek() const;

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

		// value�� ���� �Ҽ� ��° �ڸ� �ݿø� default
		inline double roundHalfUp(double value, eRounding n = eRounding::Four) const;


		std::stack<T> mStack;
		std::stack<T> mStoredMax; // �ִ밪 ��� ����
		std::stack<T> mStoredMin; // �ּҰ� ��� ����
		T mSum;
		T mExpSum;
	};



	/*
		===========================================
					  public ��� �Լ�
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
		// ������ ������� �ʴٸ� number�� ���Ͽ� Max/Min ���ÿ� �����մϴ�.
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
		// ������ ������� ���� ���� �׽�Ʈ�ϹǷ� ����ó������ �ʽ��ϴ�.
		assert(!mStack.empty());

		const T top = mStack.top();
		mStack.pop();
		mSum -= top;
		mExpSum -= (top * top);

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
		// ������� ���� ��쿡�� �׽�Ʈ�մϴ�.
		assert(!mStack.empty());

		// �Ҽ� ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.
		double tmp = mSum / (mStack.size() + 0.0);
		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartStack<T>::GetVariance() const
	{
		assert(!mStack.empty());

		// �л�: �� ����� ������ ���� �Ѱ����� ������ ����� ������ ��
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.

		// �ݿø��� ����� ����ϸ� ��������
		double avg = mSum / (mStack.size() + 0.0);
		double tmp = (mExpSum / (mStack.size() + 0.0)) - (avg * avg);

		return roundHalfUp(tmp);
	}

	template <typename T>
	double SmartStack<T>::GetStandardDeviation() const
	{
		// ǥ�� ����: �л��� ������
		// ��° �ڸ����� �ݿø��Ͽ� ��ȯ�մϴ�.

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
					private ��� �Լ�
		===========================================
	*/

	// value�� N��° �ڸ����� �ݿø� �� ��ȯ�մϴ�.
	template <typename T>
	double SmartStack<T>::roundHalfUp(double value, eRounding n) const
	{
		return std::round(value * static_cast<int>(n)) / static_cast<int>(n);
	}

} // namespace
