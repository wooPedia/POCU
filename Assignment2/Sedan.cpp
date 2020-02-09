#include "Sedan.h"
#include "Trailer.h"

namespace assignment2
{
	Sedan::Sedan()
		: Vehicle(4)
		, mMovedCount(0)
		, mTrailer(nullptr) {}

	Sedan::Sedan(const Sedan& other)
		: Vehicle(other)
		, mMovedCount(other.mMovedCount)
		, mTrailer(nullptr)
	{
		if (other.mTrailer == nullptr)
		{
			return;
		}
		else
		{
			mTrailer = new Trailer(other.mTrailer->GetWeight());
		}
	}

	Sedan::~Sedan() {}

	unsigned int Sedan::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}
	
	unsigned int Sedan::GetDriveSpeed() const
	{
		unsigned int totalWeight = (mTrailer != nullptr) ?
			mPassengersWeightSum + mTrailer->GetWeight() : mPassengersWeightSum;

		if (totalWeight <= 80)
		{
			return 480;
		}
		else if (totalWeight <= 160 && totalWeight > 80)
		{
			return 458;
		}
		else if (totalWeight <= 260 && totalWeight > 160)
		{
			return 400;
		}
		else if (totalWeight <= 350 && totalWeight > 260)
		{
			return 380;
		}
		else
		{
			return 300;
		}
	}

	void Sedan::Move()
	{
		// Sedan: 다섯 번 이동 후 한 번 쉽니다.
		const size_t POSSIBLE_MOVE_COUNT = 5;
		eVehicleBreakCount vehicleBreakCount = SEDAN;

		// 트레일러가 달려있다면 두 번 쉽니다.
		if (mTrailer != nullptr)
		{
			vehicleBreakCount = SEDAN_WITH_TRAILER;
		}

		// 충분히 쉬었다면 이동 가능합니다.
		if (mBreakCount == vehicleBreakCount)
		{
			mMovedCount = 0;
			mbMovable = true;
		}

		// 이동할 수 없다면 break 합니다.
		if (!mbMovable)
		{
			++mBreakCount;
			assert(mBreakCount <= static_cast<unsigned int>(vehicleBreakCount));
		}
		else
		{
			mMovedDistanceKM += GetMaxSpeed();
			++mMovedCount;
			mBreakCount = 0;

			assert(mMovedCount <= POSSIBLE_MOVE_COUNT);

			// 충분히 이동했으면 쉬어야 합니다.
			if (mMovedCount == POSSIBLE_MOVE_COUNT)
			{
				mbMovable = false;
			}
		}
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		if (trailer == nullptr)
		{
			return false;
		}
		if (mTrailer != nullptr)
		{
			return false;
		}
		
		mTrailer = trailer;
		return true;
	}

	bool Sedan::RemoveTrailer()
	{
		if (mTrailer == nullptr)
		{
			return false;
		}

		delete mTrailer;
		mTrailer = nullptr;

		return true;
	}

	Sedan& Sedan::operator=(const Sedan& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		if (mTrailer != nullptr)
		{
			delete mTrailer;
		}

		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			delete mPassengerList[i];
		}

		// 최대 승객수가 동일하다면 재할당하지 않습니다.
		if (mMaxPassengersCount != rhs.mMaxPassengersCount)
		{
			delete[] mPassengerList;
			mMaxPassengersCount = rhs.mMaxPassengersCount;
			mPassengerList = new const Person * [mMaxPassengersCount];
		}

		mPassengersCount = rhs.mPassengersCount;
		mPassengersWeightSum = rhs.mPassengersWeightSum;
		mBreakCount = rhs.mBreakCount;
		mMovedDistanceKM = rhs.mMovedDistanceKM;
		mbMovable = rhs.mbMovable;

		assert(mPassengersCount <= mMaxPassengersCount);
		for (size_t i = 0; i < mPassengersCount; ++i)
		{
			mPassengerList[i] = new Person(*(rhs.mPassengerList[i]));
		}

		if (rhs.mTrailer != nullptr)
		{
			mTrailer = new Trailer(rhs.mTrailer->GetWeight());
		}

		return *this;
	}
}