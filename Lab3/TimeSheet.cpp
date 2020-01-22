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
		// 복사 생성자
		// 왼쪽 객체에 other을 복사
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
		// 자가 할당이라면 자기 자신 반환
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
		// 근무 일수를 초과한다면 종료
		if (mWorkedDay >= mMaxEntries)
		{
			return;
		}

		// 알맞은 시간일 경우 기록
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
		// 편차: 관측값에서 평균을 뺌
		// 분산: 편차를 제곱하여 모두 더하고 개수로 나눔
		// 표준 편차: 분산의 제곱근

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
		private 함수
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