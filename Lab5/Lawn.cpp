#include "Lawn.h"

namespace lab5
{
	Lawn::Lawn() {}
	Lawn::~Lawn() {}

	unsigned int Lawn::GetGrassPrice(eGrassType grassType) const
	{
		// ����, ���簢��, ���簢��, ���ﰢ��
		double val = GetArea() * static_cast<double>(grassType) / 100;
		if (static_cast<size_t>(val + 1) != val + 1)
		{
			return static_cast<size_t>(val + 1);
		}
		else
		{
			return static_cast<size_t>(val);
		}
	}

	unsigned int Lawn::GetMinimumSodRollsCount() const
	{
		double area = (static_cast<double>(GetArea()) / 0.3);

		// ������ �ø�
		if (static_cast<size_t>(area) != area)
		{
			return static_cast<size_t>(area + 1);
		}
		else
		{
			return static_cast<size_t>(area);
		}
	}

}