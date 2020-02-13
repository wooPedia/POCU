#include <climits>

#include "lab6.h"

using std::vector;

namespace lab6
{
	class Pair
	{
		friend class Frequency;
	public:
		Pair(int value) 
			: mValue(value)
			, mFrequency(1) {}

	private:
		// unique�� value�� �󵵼� 
		int mValue;
		size_t mFrequency;
	};

	class Frequency
	{
	public:

		// value�� �����ϸ� �󵵼��� ������Ű��,
		// �������� �ʴ´ٸ� value, 1(frequency)�� ������ �߰��մϴ�.
		void CheckAndAddFrequency(int value)
		{
			for (Pair& pair : mPairList)
			{
				if (pair.mValue == value)
				{
					++pair.mFrequency;
					return;
				}
			}
			mPairList.emplace_back(Pair(value));
		}

		// �󵵼��� ���� ���� ���� ��ȯ�մϴ�.
		int GetTheHighestFrequency() const
		{
			assert(!mPairList.empty());

			Pair result = mPairList[0];
			for (const Pair& pair : mPairList)
			{
				result = (result.mFrequency > pair.mFrequency) ? result : pair;
			}

			return result.mValue;
		}

	private:
		vector<Pair> mPairList;
	};

	int Sum(const std::vector<int>& v)
	{
		if (v.empty())
		{
			return 0;
		}

		int sum = 0;
		for (const int& data : v)
		{
			sum += data;
		}

		return sum;
	}

	int Min(const std::vector<int>& v)
	{
		if (v.empty())
		{
			return INT_MAX;
		}

		int min = v[0];
		for (const int& data : v)
		{
			min = (min < data) ? min : data;
		}

		return min;
	}

	int Max(const std::vector<int>& v)
	{
		if (v.empty())
		{
			return INT_MIN;
		}

		int max = v[0];
		for (const int& data : v)
		{
			max = (max > data) ? max : data;
		}

		return max;
	}

	float Average(const std::vector<int>& v)
	{
		if (v.empty())
		{
			return 0.0f;
		}

		int sum = Sum(v);
		return sum / static_cast<float>(v.size());
	}

	int NumberWithMaxOccurrence(const std::vector<int>& v)
	{
		if (v.empty())
		{
			return 0;
		}

		Frequency f;
		for (const auto& data : v)
		{
			f.CheckAndAddFrequency(data);
		}

		return f.GetTheHighestFrequency();
	}

	void SortDescending(std::vector<int>& v)
	{
		using vec_size = vector<int>::size_type;
		using iter = vector<int>::iterator;

		vec_size size = v.size();

		if (size <= 1)
		{
			return;
		}

		/*
		   ex) 1 3 5 7

			-> 3 1 3 5 7
			-> 3 1 7 5 7    
			-> 3 1 7 5

			-> 7 3 1 7 5
			-> 7 3 1 5 5
			-> 7 3 1 5

			-> 7 5 3 1 5
			-> 7 5 3 1 5
			-> 7 5 3 1

			2��° ���Һ��� ��

			1. 3�� 1���� ũ�ٸ� 3�� 1 ��ġ�� ����
			2. 3 ��ġ�� ������ ����(7)�� �����
			3. ������ ���Ҹ� ����
			5. 5�� 1��
			...
		*/

		for (vec_size i = 1; i != size; ++i)
		{
			for (vec_size j = 0; j != i; ++j)
			{
				if (v[i] > v[j])
				{
					v.insert(v.begin() + j, v[i]); // j ��ġ�� v[i]�� �����մϴ�.
					v[i+1] = v.back();
					v.pop_back();
					break;
				}
			}
		}
	}
}