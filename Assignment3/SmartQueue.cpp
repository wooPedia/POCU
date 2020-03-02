#include "SmartQueue.h"

namespace assignment3
{
	template <>
	float SmartQueue<float>::GetMin() const
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<float>::lowest();
		}

		if (!mStoredMin.empty())
		{
			return mStoredMin.back();
		}

		return findMin(mQueue);
	}

	template <>
	double SmartQueue<double>::GetMin() const
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<double>::lowest();
		}

		if (!mStoredMin.empty())
		{
			return mStoredMin.back();
		}

		return findMin(mQueue);
	}
}