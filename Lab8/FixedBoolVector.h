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
		// Add�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.

		if (mSize >= N)
		{
			return false;
		}

		// add�� ������ ��ġ�� �迭 �ε����� ��Ʈ �ڸ� ���� ���մϴ�.
		// addIndex�� bValue�� �߰��� ��ġ�� vector index.
		// addBit�� bValue�� �߰��� ��ġ�� �ε����̿��� �� 
		// (ex: ���� size�� 35�� ��� ��Ұ� 35�� �̹Ƿ� vec[1]�� 4��° ��Ʈ[index: 3] ��ġ�� add�ؾ� ��)
		// �ǵ帱 �ʿ� X
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

		// ���� vector�� size��ŭ Ž���մϴ�. 
		for (size_t i = 0; i != vecSize; ++i)
		{
			// ������ ��� �������� 32bit ��� Ȯ���մϴ�.
			// ������ ��Ʈ�� ���� ��Ʈ���� 1bit �� right shift�մϴ�.
			if (i < vecSize - 1)
			{
				for (size_t j = 0; j != 32; ++j)
				{
					// ��ġ�ϴ� value�� ã�´ٸ� 
					if (((mFixedVector[i] >> j) & 1) == bValue)
					{
						// remove(false)
						// 0101 1010 [0] -> 1010 010 
						// 0101 1111 [1]
						shiftForRemove(i, j);
						rearrangeVector(i + 1, vecSize); // [i+1, vecSize) ������ �������մϴ�.
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

		return (mFixedVector[vecIndex] >> bitOfN) & 1;
	}

	template <size_t N>
	bool FixedVector<bool, N>::operator[](size_t index)
	{
		// bool Ÿ���� �迭 �ε��� ������ ���� ���� ������ �� �����ϴ�.

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

		// ������� ����� ������ ���������� Ž���� �� �ֵ��� ���� ���� ���մϴ�.
		size_t vecSize = (mSize / 32) + 1;
		size_t bitForLoof = (mSize % 32);

		assert(vecSize <= MAX);
		assert(bitForLoof < 32);

		// �迭���� t�� ��ġ�ϴ� ��Ҹ� Ž���մϴ�.
		++bitForLoof;
		for (size_t i = 0; i != vecSize; ++i)
		{
			// ������ ��� �������� 32bit ��� Ȯ���մϴ�.
			if (i < vecSize - 1)
			{
				// �迭�� �� ���Ҹ��� 32bit�� Ȯ���մϴ�.
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
				// ������ ��Ҵ� ����� ��Ʈ ����ŭ�� Ȯ���մϴ�.
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
			0110 1010
			^

			5. 4������ ���� ���� ������ ��Ʈ�� ���� ����� ù ��Ʈ�� set

			6. �׸��� 1bit�� right shift

			7. 5�� 6�� �ݺ�

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
		// begin���� end-1���� ���� ����� ������ ��Ʈ�� ���� ��Ʈ�� ù ��Ʈ�� set�ϰ� 
		// ���� ��Ҵ� 1��ŭ right shift

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

		//	6. �׸��� 1bit�� right shift

		//	7. 5�� 6�� �ݺ�

		// ���� �����ϴ� ������ �ε����� ��Ʈ �ڸ����� ����.
		//size_t currentLastIndex = mSize % 32;
		//unsigned int lastBitOfLastIndex = mSize / 32;

		//for(size_t i = 0; i != currentLastIndex; )
	}


} // namespace
