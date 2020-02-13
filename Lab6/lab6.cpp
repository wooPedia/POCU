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
		// unique한 value와 빈도수 
		int mValue;
		size_t mFrequency;
	};

	class Frequency
	{
	public:

		// value가 존재하면 빈도수를 증가시키고,
		// 존재하지 않는다면 value, 1(frequency)을 쌍으로 추가합니다.
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

		// 빈도수가 가장 높은 값을 반환합니다.
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

			2번째 원소부터 비교

			1. 3이 1보다 크다면 3을 1 위치에 삽입
			2. 3 위치에 마지막 원소(7)로 덮어씌움
			3. 마지막 원소를 삭제
			5. 5와 1비교
			...
		*/

		for (vec_size i = 1; i != size; ++i)
		{
			for (vec_size j = 0; j != i; ++j)
			{
				if (v[i] > v[j])
				{
					v.insert(v.begin() + j, v[i]); // j 위치에 v[i]를 삽입합니다.
					v[i+1] = v.back();
					v.pop_back();
					break;
				}
			}
		}
	}
}