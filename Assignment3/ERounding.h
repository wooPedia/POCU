#pragma once

#include <cmath>
//#include <cstdint>
#include <limits>

/*
	===========================================
			  �ݿø� ���� ��� �� �Լ�
	===========================================

	�Ҽ��� �Ʒ� n��° �ڸ����� �ݿø��ϱ� ���� �ʿ��� ����� eRounding Ŭ�������� �����մϴ�.
	����� roundHalfUp �Լ��� ���ڷ� ���˴ϴ�.

	��� ���� 10^(n-1)�Դϴ�.
	ex) 3��° �ڸ� 100, 2��° �ڸ� 10, ...
*/

namespace assignment3
{
	enum class eRounding
	{
		Four = 1000
	};


	// value�� ���� n��° �ڸ����� �ݿø��մϴ�.
	// default: 4
	inline double roundHalfUp(double value, eRounding n = eRounding::Four)
	{
		return std::round(value * static_cast<int>(n)) / static_cast<int>(n);
	}
}
