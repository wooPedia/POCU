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
		int mValue;
		size_t mFrequency;
	};

	class Frequency
	{
	public:
		void CheckAndAddFrequency(int value)
		{
			for (auto& pair : mPairList)
			{
				if (pair.mValue == value)
				{
					++pair.mFrequency;
					return;
				}
			}
			mPairList.emplace_back(Pair(value));
		}

		int GetTheHighestFrequency() const
		{
			assert(!mPairList.empty());

			Pair result = mPairList[0];
			for (const auto& pair : mPairList)
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
		for (const auto& data : v)
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
		for (const auto& data : v)
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
		for (const auto& data : v)
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
		if (v.empty() || size == 1)
		{
			return;
		}

		for (vec_size i = 1; i < size; ++i)
		{
			for (vec_size j = 0; j != i; ++j)
			{
				if (v[i] > v[j])
				{
					v.insert(v.begin() + j, v[i]);
					v.erase(v.begin() + i + 1);
				}
			}
		}
	}
}