#pragma once

#include "Vehicle.h"
#include "IDrivable.h"

namespace assignment2
{
	class Trailer;

	class Sedan : public Vehicle, public IDrivable
	{
	public:
		Sedan();
		~Sedan();

		virtual unsigned int GetMaxSpeed() const;
		virtual unsigned int GetDriveSpeed() const;
		virtual void Move();

		bool AddTrailer(const Trailer* trailer);
		bool RemoveTrailer();

	private:
		unsigned int mMovedCount;
		const Trailer* mTrailer;
	};
}