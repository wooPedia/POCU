#pragma once

#include <string>

namespace lab3
{
	class TimeSheet
	{
	public:
		TimeSheet(const char* name, unsigned int maxEntries);
		TimeSheet(const TimeSheet& other);
		~TimeSheet();

		TimeSheet& operator=(const TimeSheet& rhs);

		void AddTime(int timeInHours);
		int GetTimeEntry(unsigned int index) const;
		int GetTotalTime() const;
		float GetAverageTime() const;
		float GetStandardDeviation() const;
		const std::string& GetName() const;

	private:
		unsigned int* createTimeLog(unsigned int maxEntries) const;
		void deleteTimeLogMemory();
		void myUnSignedIntegerCpy(unsigned int* destination, const unsigned int* source, size_t num);

		std::string mName;
		size_t mMaxEntries;
		size_t mWorkedDay;
		unsigned int* mTimeLog;
	};
}
