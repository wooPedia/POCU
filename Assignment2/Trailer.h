#pragma once

namespace assignment2
{
	// ķ��ī Ʈ���Ϸ��μ� Sedan�� �����ؾ� �̵��� �����մϴ�.
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