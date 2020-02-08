#pragma once

namespace assignment2
{
	// 캠핑카 트레일러로서 Sedan에 연결해야 이동이 가능합니다.
	class Trailer
	{
	public:
		Trailer(unsigned int weight);
		~Trailer();

		unsigned int GetWeight() const;

	private:
		unsigned int mWeight;
	};
}