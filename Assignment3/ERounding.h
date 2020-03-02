#pragma once

#include <cmath>
#include <stdint.h>
#include <limits>

/*
	===========================================
			  반올림 관련 상수 및 함수
	===========================================

	소수점 아래 n번째 자리에서 반올림하기 위해 필요한 상수를 eRounding 클래스에서 정의합니다.
	상수는 roundHalfUp 함수의 인자로 사용됩니다.

	상수 값은 10^(n-1)입니다.
	ex) 3번째 자리 100, 2번째 자리 10, ...
*/

namespace assignment3
{
	enum class eRounding : int16_t
	{
		Four = 1000
	};


	// value에 대해 n번째 자리에서 반올림합니다.
	// default: 4
	double roundHalfUp(double value, eRounding n = eRounding::Four);
}
