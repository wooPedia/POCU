#include "QueueStack.h"

namespace assignment3
{
	template <>
	float QueueStack<float>::GetMin() const
	{
		if (mQueueStack.front().Empty())
		{
			return std::numeric_limits<float>::lowest();
		}

		return findMin(mQueueStack);
	}

	template <>
	double QueueStack<double>::GetMin() const
	{
		if (mQueueStack.front().Empty())
		{
			return std::numeric_limits<double>::lowest();
		}

		return findMin(mQueueStack);
	}
}