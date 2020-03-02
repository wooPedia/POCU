#pragma once

#include <cassert>
#include <cmath>
#include <stdint.h>
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

#ifndef ROUNDING
#define ROUNDING

namespace assignment3
{
	enum class eRounding : int16_t
	{
		Four = 1000
	};


	// value�� ���� n��° �ڸ����� �ݿø��մϴ�.
	// default: 4
	double roundHalfUp(double value, eRounding n = eRounding::Four);
}

#endif // !define ROUNDING