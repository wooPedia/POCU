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
		FixedVector<bool, N>& operator=(const FixedVector& rhs) = default;

		bool Add(const bool t);
		bool Remove(const bool t);
		bool Get(size_t index) const;

		bool operator[](size_t index) const;

		int GetIndex(const bool t) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		void shiftForRemove(size_t vecIndex, size_t removedBit);
		void rearrangeVector(size_t begin, size_t end);

		enum
		{
			MAX = (N % 32 != 0) ? static_cast<size_t>((N / 32) + 1) : (N / 32)
		};
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
		// Add�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.

		if (mSize >= N)
		{
			return false;
		}

		size_t addIndex = mSize / 32;
		unsigned int addBit = mSize % 32;

		assert(addIndex < MAX);
		assert(addBit < 32);

		// true�� ��� addBit ��° ��Ʈ�� true�� �����մϴ�.
		if (bValue)
		{
			mFixedVector[addIndex] |= (1 << addBit);
		}
		else
		{
			// false�� ��� addBit ��° ��Ʈ�� false�� �����մϴ�.
			mFixedVector[addIndex] &= ~(1 << addBit);
		}

		++mSize;
		assert(mSize <= N);

		return true;
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(const bool bValue)
	{
		// Remove�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.

		if (mSize == 0)
		{
			return false;
		}

		// ������� ����� ������ ���� ������ Ž���� �� �ֵ��� ���� ���� ���մϴ�.
		size_t vecSize = (mSize % 32 != 0) ? (mSize / 32) + 1 : (mSize / 32);
		size_t bitForLoof = (mSize % 32 != 0) ? (mSize % 32) : 32;

		assert(vecSize <= MAX);
		assert(bitForLoof <= 32);

		// ���� ������ ũ�⸸ŭ Ž���մϴ�. 
		for (size_t i = 0; i != vecSize; ++i)
		{
			// ������ ������ ��� �������� 32bit ��� Ȯ���մϴ�.
			if (i < vecSize - 1)
			{
				for (size_t j = 0; j != 32; ++j)
				{
					// ��ġ�ϴ� value�� ã�´ٸ� 
					if (((mFixedVector[i] >> j) & 1) == bValue)
					{
						shiftForRemove(i, j); // ��Ʈ�� �����ϱ� ���� ���� ��Ʈ���� ��ĭ�� ���ϴ�.
						rearrangeVector(i + 1, vecSize); // [i+1, vecSize) ������ ��Ҹ� �������մϴ�.
						--mSize;

						return true;
					}
				}
			}
			else
			{
				// ������ ��Ҵ� ����� ��Ʈ ����ŭ�� Ȯ���մϴ�.
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

		assert(vecIndex < MAX);
		assert(bitOfN < 32);

		return (mFixedVector[vecIndex] >> bitOfN) & 1;
	}

	template <size_t N>
	bool FixedVector<bool, N>::operator[](size_t index) const
	{
		// bool Ÿ���� �迭 �ε��� ������ ���� ���� ������ �� �����ϴ�.
		assert(index >= 0);

		size_t vecIndex = index / 32;
		size_t bitOfN = index % 32;

		assert(vecIndex < MAX);
		assert(bitOfN < 32);

		return (mFixedVector[vecIndex] >> bitOfN) & 1;
	}

	template <size_t N>
	int FixedVector<bool, N>::GetIndex(const bool bValue) const
	{
		if (mSize == 0)
		{
			return -1;
		}

		size_t vecSize = (mSize % 32 != 0) ? (mSize / 32 + 1) : (mSize / 32);
		size_t bitForLoof = (mSize % 32 != 0) ? (mSize % 32) : 32;

		assert(vecSize <= MAX);
		assert(bitForLoof <= 32);

		for (size_t i = 0; i != vecSize; ++i)
		{
			if (i < vecSize - 1)
			{
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
			vector�� index��° ��ҿ��� removedBit��° ��Ʈ�� �����ϰ� ��ĭ�� ���ϴ�. (1 right shift)

			ex) og: 1100 1010���� [4](= false)�� ��Ʈ�� ���� (result: 0110 1010)

			1. 4��° ��Ʈ ���� ��Ʈ���� tmp�� ����
			tmp == 1010

			2. og�� 1��ŭ right shift
			og: 0110 0101

			3. og�� 4��° ���� ��Ʈ���� 0���� set
			og: 0110 0000

			4. og�� tmp�� OR ����
			og: 0110 1010
		*/

		unsigned int tmp = 0;

		// remove�ϴ� ��Ʈ�� ���� ��Ʈ���� tmp�� �����մϴ�.
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

		// 2. 1��ŭ right shift
		mFixedVector[vecIndex] >>= 1;

		// 3. 0~j-1 ��Ʈ�� ��� 0���� set
		for (size_t j = 0; j != removedBit; ++j)
		{
			mFixedVector[vecIndex] &= ~(1 << j);
		}

		// 4. mFixedVector[vecIndex]�� tmp�� OR �����մϴ�.
		mFixedVector[vecIndex] |= tmp;
	}

	template <size_t N>
	void FixedVector<bool, N>::rearrangeVector(size_t begin, size_t end)
	{
		// ������ ���� ����� ������ ��Ʈ�� ���� ����� ù ��Ʈ�� set�ϰ� 
		// ���� ��Ҹ� 1��ŭ right shift �մϴ�.
		// ex) 
		// 0000 1111 [0]
		// 0000 1111 [1]
		// 0001 0001 [2]
		//     ��
		// 1000 1111 [0]
		// 1000 0111 [1]
		// 0000 1000 [2]

		// [begin, end) ������ ��� �ݺ��մϴ�.
		for (size_t i = begin; i != end; ++i)
		{
			// ���� ���� ����� ������ ��Ʈ�� ���� ���� ����� ù ��Ʈ�� set
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
	}


} // namespace
