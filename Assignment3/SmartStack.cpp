#include "SmartStack.h"

namespace assignment3
{
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
}