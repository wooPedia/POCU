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
		void shiftForRemove(size_t vecIndex, size_t removedBit);
		void rearrangeVector(size_t begin, size_t end);

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
	bool FixedVector<bool, N>::Add(const bool bValue)
	{
		// Add가 성공하면 true, 실패하면 false를 반환합니다.

		if (mSize >= N)
		{
			return false;
		}

		// add를 수행할 위치의 배열 인덱스와 비트 자리 수를 구합니다.
		// addIndex는 bValue가 추가될 위치의 vector index.
		// addBit는 bValue가 추가될 위치의 인덱스이여야 함 
		// (ex: 현재 size가 35일 경우 요소가 35개 이므로 vec[1]의 4번째 비트[index: 3] 위치에 add해야 함)
		// 건드릴 필요 X
		size_t addIndex = mSize / 32;
		unsigned int addBit = mSize % 32;

		assert(addIndex < MAX);
		assert(addBit < 32);

		// true일 경우 addBit 번째 비트를 true로 설정합니다.
		if (bValue)
		{
			mFixedVector[addIndex] |= (1 << addBit);
		}
		else
		{
			// false일 경우 addBit 번째 비트를 false로 설정합니다.
			mFixedVector[addIndex] &= ~(1 << addBit);
		}

		++mSize;

		return true;
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(const bool bValue)
	{
		// Remove가 성공하면 true, 실패하면 false를 반환합니다.

		if (mSize == 0)
		{
			return false;
		}

		// 현재까지 저장된 데이터 범위 내에서 탐색할 수 있도록 범위 값을 구합니다.
		size_t vecSize = (mSize % 32 != 0) ? (mSize / 32 + 1) : (mSize / 32);
		size_t bitForLoof = (mSize % 32);

		assert(vecSize <= MAX);
		assert(bitForLoof < 32);

		// 0011 1100 [0]
		// 1100 0011 [1]
		// 10		 [2]
		// remove(false)
		// 1001 1110 [0]
		// 1110 0001 [1]
		// 0000 0000 [2]

		// 현재 vector의 size만큼 탐색합니다. 
		for (size_t i = 0; i != vecSize; ++i)
		{
			// 마지막 요소 전까지는 32bit 모두 확인합니다.
			// 삭제될 비트의 다음 비트부터 1bit 씩 right shift합니다.
			if (i < vecSize - 1)
			{
				for (size_t j = 0; j != 32; ++j)
				{
					// 일치하는 value를 찾는다면 
					if (((mFixedVector[i] >> j) & 1) == bValue)
					{
						// remove(false)
						// 0101 1010 [0] -> 1010 010 
						// 0101 1111 [1]
						shiftForRemove(i, j);
						rearrangeVector(i + 1, vecSize); // [i+1, vecSize) 범위를 재정렬합니다.
						--mSize;

						return true;
					}
				}
			}
			else
			{
				// 마지막 요소는 저장된 비트 수만큼만 확인합니다.
				for (size_t j = 0; j != bitForLoof; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == bValue)
					{
						shiftForRemove(i, j);
						rearrangeVector(i + 1, vecSize);
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

		size_t vecIndex = index / 32;
		size_t bitOfN = index % 32;

		return (mFixedVector[vecIndex] >> bitOfN) & 1;
	}

	template <size_t N>
	bool FixedVector<bool, N>::operator[](size_t index)
	{
		// bool 타입은 배열 인덱스 접근을 통해 값을 변경할 수 없습니다.

		assert(index < mSize);

		size_t vecIndex = index / 32;
		size_t bitOfN = index % 32;

		return (mFixedVector[vecIndex] >> bitOfN) & 1;
	}

	template <size_t N>
	int FixedVector<bool, N>::GetIndex(const bool bValue) const
	{
		if (mSize == 0)
		{
			return -1;
		}

		// 현재까지 저장된 데이터 범위내에서 탐색할 수 있도록 범위 값을 구합니다.
		size_t vecSize = (mSize / 32) + 1;
		size_t bitForLoof = (mSize % 32);

		assert(vecSize <= MAX);
		assert(bitForLoof < 32);

		// 배열에서 t와 일치하는 요소를 탐색합니다.
		++bitForLoof;
		for (size_t i = 0; i != vecSize; ++i)
		{
			// 마지막 요소 전까지는 32bit 모두 확인합니다.
			if (i < vecSize - 1)
			{
				// 배열의 각 원소마다 32bit를 확인합니다.
				for (size_t j = 0; j != 32; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == bValue)
					{
						return 32 * i + j;
					}
				}
			}
			else
			{
				// 마지막 요소는 저장된 비트 수만큼만 확인합니다.
				for (size_t j = 0; j != bitForLoof; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == bValue)
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
			^

			5. 4번에서 구한 값의 마지막 비트를 다음 요소의 첫 비트로 set

			6. 그리고 1bit씩 right shift

			7. 5번 6번 반복

		*/

		unsigned int tmp = 0;

		// remove하는 비트의 이전 비트들을 tmp에 저장합니다.
		for (size_t i = 0; i != removedBit; ++i)
		{
			bool bBitValue = (mFixedVector[vecIndex] >> i) & 1;
			if (bBitValue)
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

	template <size_t N>
	void FixedVector<bool, N>::rearrangeVector(size_t begin, size_t end)
	{
		// begin부터 end-1까지 이전 요소의 마지막 비트를 현재 비트의 첫 비트로 set하고 
		// 현재 요소는 1만큼 right shift

		for (size_t i = begin; i != end; ++i)
		{
			// 이전 벡터 요소의 마지막 비트를 현재 벡터 요소의 첫 비트로 set
			if (mFixedVector[i] & 1)
			{
				mFixedVector[i - 1] |= (1 << 31);
			}
			else
			{
				mFixedVector[i - 1] &= ~(1 << 31);
			}
			mFixedVector[i] >>= 1;
		}

		//	6. 그리고 1bit씩 right shift

		//	7. 5번 6번 반복

		// 현재 존재하는 마지막 인덱스와 비트 자리수를 구함.
		//size_t currentLastIndex = mSize % 32;
		//unsigned int lastBitOfLastIndex = mSize / 32;

		//for(size_t i = 0; i != currentLastIndex; )
	}


} // namespace
