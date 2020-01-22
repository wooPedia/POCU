#include <cmath>

#include "TimeSheet.h"

namespace lab3
{
	TimeSheet::TimeSheet(const char* name, unsigned int maxEntries)
		: mName(name), mMaxEntries(maxEntries), mWorkedDay(0)
	{
		mTimeLog = createTimeLog(maxEntries);
	}

	TimeSheet::TimeSheet(const TimeSheet& other)
		: mName(other.mName), mMaxEntries(other.mMaxEntries), mWorkedDay(other.mWorkedDay)
	{
		// ���� ������
		// ���� ��ü�� other�� ����
		// other.mName, other.mMaxEntries, other.mTimeLog

		mTimeLog = createTimeLog(other.mMaxEntries);
		myUnSignedIntegerCpy(mTimeLog, other.mTimeLog, mWorkedDay);
	}

	TimeSheet::~TimeSheet()
	{
		deleteTimeLogMemory();
	}

	TimeSheet& TimeSheet::operator=(const TimeSheet& rhs)
	{
		// �ڰ� �Ҵ��̶�� �ڱ� �ڽ� ��ȯ
		if (this == &rhs)
		{
			return *this;
		}

		deleteTimeLogMemory();

		mName = rhs.mName;
		mMaxEntries = rhs.mMaxEntries;
		mWorkedDay = rhs.mWorkedDay;

		mTimeLog = createTimeLog(mMaxEntries);
		myUnSignedIntegerCpy(mTimeLog, rhs.mTimeLog, mWorkedDay);

		return *this;
	}


	void TimeSheet::AddTime(int timeInHours)
	{
		// �ٹ� �ϼ��� �ʰ��Ѵٸ� ����
		if (mWorkedDay >= mMaxEntries)
		{
			return;
		}

		// �˸��� �ð��� ��� ���
		if (timeInHours >= 1 && timeInHours <= 10)
		{
			mTimeLog[mWorkedDay] = timeInHours;
			++mWorkedDay;
		}
	}

	int TimeSheet::GetTimeEntry(unsigned int index) const
	{
		if (index >= 0 && index <= mWorkedDay - 1)
		{
			return mTimeLog[index];
		}

		return -1;
	}

	int TimeSheet::GetTotalTime() const
	{
		unsigned int totalTime = 0;
		for (int i = 0; i != mWorkedDay; ++i)
		{
			totalTime += mTimeLog[i];
		}

		return totalTime;
	}

	float TimeSheet::GetAverageTime() const
	{
		if (mWorkedDay == 0)
		{
			return 0.0f;
		}

		float totalTime = static_cast<float>(GetTotalTime());

		return (totalTime / mWorkedDay);
	}

	float TimeSheet::GetStandardDeviation() const
	{
		// ����: ���������� ����� ��
		// �л�: ������ �����Ͽ� ��� ���ϰ� ������ ����
		// ǥ�� ����: �л��� ������

		if (mWorkedDay == 0)
		{
			return 0.0f;
		}

		float avgTime = GetAverageTime();

		float variance = 0.0f;
		for (int i = 0; i != mWorkedDay; ++i)
		{
			variance += (mTimeLog[i] - avgTime) * (mTimeLog[i] - avgTime);
		}
		variance /= mWorkedDay;

		return sqrt(variance);
	}

	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}


	/*
		private �Լ�
	*/

	unsigned int* TimeSheet::createTimeLog(unsigned int maxEntries) const
	{
		return new unsigned int[maxEntries];
	}

	void TimeSheet::deleteTimeLogMemory()
	{
		if (mTimeLog != nullptr)
		{
			delete[] mTimeLog;
		}
	}

	void TimeSheet::myUnSignedIntegerCpy(unsigned int* destination, const unsigned int* source, size_t num)
	{
		for (int i = 0; i != num; ++i)
		{
			destination[i] = source[i];
		}
	}
}