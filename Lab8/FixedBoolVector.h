#pragma once

#include <cassert>

#include "FixedVector.h"

namespace lab8
{
	// FixedVector class specialized for bool type

	template<typename T, size_t N>
	class FixedVector;

	template <size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		~FixedVector() = default;
		FixedVector(const FixedVector& other) = default;
		FixedVector& operator=(const FixedVector& rhs) = default;

		bool Add(const bool t);
		bool Remove(const bool t);
		bool Get(size_t index) const;

		bool operator[](size_t index);

		int GetIndex(const bool t) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		size_t getVectorIndexFromTarget(size_t targetIndex, unsigned int& n) const;
		void shiftForRemove(size_t vecIndex, size_t removedBit);

		enum { MAX = (N % 32 != 0) ? static_cast<size_t>((N / 32) + 1) : N / 32 };
		unsigned int mFixedVector[MAX];
		size_t mSize;
	};


	// Public method

	template <size_t N>
	FixedVector<bool, N>::FixedVector()
		: mSize(0)
		, mFixedVector{ 0, }
	{
	}

	template <size_t N>
	bool FixedVector<bool, N>::Add(const bool t)
	{
		// Add가 성공하면 true, 실패하면 false를 반환합니다.

		if (mSize >= N)
		{
			return false;
		}

		unsigned int bitOfN = 0;

		// add를 수행할 위치의 배열 인덱스와 비트 자리 수를 구합니다.
		size_t addIndex = getVectorIndexFromTarget(mSize++, bitOfN);

		assert(addIndex < N);
		assert(bitOfN < 32);

		// true일 경우 bitOfN 번째 비트를 true로 설정합니다.
		if (t)
		{
			mFixedVector[addIndex] |= (1 << bitOfN);
		}
		else
		{
			// false일 경우 bitOfN 번째 비트를 false로 설정합니다.
			mFixedVector[addIndex] &= ~(1 << bitOfN);
		}

		return true;
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(const bool t)
	{
		// Remove가 성공하면 true, 실패하면 false를 반환합니다.

		if (mSize == 0)
		{
			return false;
		}

		// 현재까지 저장된 데이터 범위내에서 탐색할 수 있도록 범위 값을 구합니다.

		size_t lastBitOfLastIndex = 0; // 마지막 요소의 마지막 비트의 인덱스
		size_t currentLastIndex = getVectorIndexFromTarget(mSize, lastBitOfLastIndex);

		assert(lastBitOfLastIndex < 32);
		assert(currentLastIndex < MAX);

		// 배열에서 t와 일치하는 요소를 탐색합니다.
		++currentLastIndex;
		for (size_t i = 0; i != currentLastIndex; ++i)
		{
			// 마지막 요소 전까지는 32bit 모두 확인합니다.
			if (i < currentLastIndex - 1)
			{
				// 배열의 각 원소마다 32bit를 확인합니다.
				for (size_t j = 0; j != 32; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == t)
					{
						shiftForRemove(i, j); // 삭제될 비트의 다음 비트부터 1bit 씩 right shift합니다.
						--mSize;

						return true;
					}
				}
			}
			else
			{
				// 마지막 요소는 저장된 비트 수만큼만 확인합니다.
				for (size_t j = 0; j != lastBitOfLastIndex; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == t)
					{
						shiftForRemove(i, j);
						--mSize;

						return true;
					}
				}
			}
		}

		return false;
	}

	template <size_t N>
	bool FixedVector<bool, N>::Get(size_t index) const
	{
		assert(index < mSize);

		size_t bitOfN = 0;
		size_t vecIndex = getVectorIndexFromTarget(index, bitOfN);

		return (mFixedVector[vecIndex] >> bitOfN) & 1;
	}

	template <size_t N>
	bool FixedVector<bool, N>::operator[](size_t index)
	{
		// bool 타입은 배열 인덱스 접근을 통해 값을 변경할 수 없습니다.

		assert(index < mSize);

		size_t bitOfN = 0;
		size_t vecIndex = getVectorIndexFromTarget(index, bitOfN);

		return (mFixedVector[vecIndex] >> bitOfN) & 1;
	}

	template <size_t N>
	int FixedVector<bool, N>::GetIndex(const bool t) const
	{
		if (mSize == 0)
		{
			return -1;
		}

		// 현재까지 저장된 데이터 범위내에서 탐색할 수 있도록 범위 값을 구합니다.

		size_t lastBitOfLastIndex = 0; // 마지막 요소의 마지막 비트의 인덱스
		size_t currentLastIndex = getVectorIndexFromTarget(mSize, lastBitOfLastIndex);

		assert(lastBitOfLastIndex < 32);
		assert(currentLastIndex < MAX);

		// 배열에서 t와 일치하는 요소를 탐색합니다.
		++currentLastIndex;
		for (size_t i = 0; i != currentLastIndex; ++i)
		{
			// 마지막 요소 전까지는 32bit 모두 확인합니다.
			if (i < currentLastIndex - 1)
			{
				// 배열의 각 원소마다 32bit를 확인합니다.
				for (size_t j = 0; j != 32; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == t)
					{
						return 32 * i + j;
					}
				}
			}
			else
			{
				// 마지막 요소는 저장된 비트 수만큼만 확인합니다.
				for (size_t j = 0; j != lastBitOfLastIndex; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == t)
					{
						return 32 * i + j;
					}
				}
			}
		}

		return -1;
	}

	template <size_t N>
	size_t FixedVector<bool, N>::GetSize() const
	{
		return mSize;
	}

	template <size_t N>
	size_t FixedVector<bool, N>::GetCapacity() const
	{
		return N;
	}


	// private method

	template <size_t N>
	size_t FixedVector<bool, N>::getVectorIndexFromTarget(size_t targetIndex, unsigned int& n) const
	{
		// targetIndex번째 bool 값이 실제로 저장되어 있는 배열의 인덱스를 반환하고
		// 몇 번째 비트인지를 n에 저장합니다.
		// ex) targetIndex가 34라면 1을 반환하고 n에 2를 저장합니다.

		n = targetIndex % 32;
		return targetIndex / 32;
	}

	template <size_t N>
	void FixedVector<bool, N>::shiftForRemove(size_t vecIndex, size_t removedBit)
	{
		/*
			vector의 index번째 요소에서 removedBit번째 비트를 삭제하고 한칸씩 당깁니다. (1 right shift)

			ex) og: 1100 1010에서 [4](= false)의 비트를 제거 (result: 0110 1010)

			1. 4번째 비트 이전 비트들을 tmp에 저장
			tmp == 1010

			2. og를 1만큼 right shift
			og: 0110 0101

			3. og의 4번째 이전 비트들을 0으로 set
			og: 0110 0000

			4. og와 tmp를 OR 연산
			0110 1010
		*/

		unsigned int tmp = 0;

		// remove하는 비트의 이전 비트들을 tmp에 저장합니다.
		for (size_t i = 0; i != removedBit; ++i)
		{
			bool bitValue = (mFixedVector[vecIndex] >> i) & 1;
			if (bitValue)
			{
				tmp |= (1 << i);
			}
			else
			{
				tmp &= ~(1 << i);
			}
		}

		// 2. 1만큼 right shift
		mFixedVector[vecIndex] >>= 1;

		// 3. 0~j-1 비트를 모두 0으로 set
		for (size_t j = 0; j != removedBit; ++j)
		{
			mFixedVector[vecIndex] &= ~(1 << j);
		}

		// 4. mFixedVector[vecIndex]와 tmp를 OR 연산합니다.
		mFixedVector[vecIndex] |= tmp;
	}

} // namespace
