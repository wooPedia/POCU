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
		// Add�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.

		if (mSize >= N)
		{
			return false;
		}

		unsigned int bitOfN = 0;

		// add�� ������ ��ġ�� �迭 �ε����� ��Ʈ �ڸ� ���� ���մϴ�.
		size_t addIndex = getVectorIndexFromTarget(mSize++, bitOfN);

		assert(addIndex < N);
		assert(bitOfN < 32);

		// true�� ��� bitOfN ��° ��Ʈ�� true�� �����մϴ�.
		if (t)
		{
			mFixedVector[addIndex] |= (1 << bitOfN);
		}
		else
		{
			// false�� ��� bitOfN ��° ��Ʈ�� false�� �����մϴ�.
			mFixedVector[addIndex] &= ~(1 << bitOfN);
		}

		return true;
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(const bool t)
	{
		// Remove�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.

		if (mSize == 0)
		{
			return false;
		}

		// ������� ����� ������ ���������� Ž���� �� �ֵ��� ���� ���� ���մϴ�.

		size_t lastBitOfLastIndex = 0; // ������ ����� ������ ��Ʈ�� �ε���
		size_t currentLastIndex = getVectorIndexFromTarget(mSize, lastBitOfLastIndex);

		assert(lastBitOfLastIndex < 32);
		assert(currentLastIndex < MAX);

		// �迭���� t�� ��ġ�ϴ� ��Ҹ� Ž���մϴ�.
		++currentLastIndex;
		for (size_t i = 0; i != currentLastIndex; ++i)
		{
			// ������ ��� �������� 32bit ��� Ȯ���մϴ�.
			if (i < currentLastIndex - 1)
			{
				// �迭�� �� ���Ҹ��� 32bit�� Ȯ���մϴ�.
				for (size_t j = 0; j != 32; ++j)
				{
					if (((mFixedVector[i] >> j) & 1) == t)
					{
						shiftForRemove(i, j); // ������ ��Ʈ�� ���� ��Ʈ���� 1bit �� right shift�մϴ�.
						--mSize;

						return true;
					}
				}
			}
			else
			{
				// ������ ��Ҵ� ����� ��Ʈ ����ŭ�� Ȯ���մϴ�.
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
		// bool Ÿ���� �迭 �ε��� ������ ���� ���� ������ �� �����ϴ�.

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

		// ������� ����� ������ ���������� Ž���� �� �ֵ��� ���� ���� ���մϴ�.

		size_t lastBitOfLastIndex = 0; // ������ ����� ������ ��Ʈ�� �ε���
		size_t currentLastIndex = getVectorIndexFromTarget(mSize, lastBitOfLastIndex);

		assert(lastBitOfLastIndex < 32);
		assert(currentLastIndex < MAX);

		// �迭���� t�� ��ġ�ϴ� ��Ҹ� Ž���մϴ�.
		++currentLastIndex;
		for (size_t i = 0; i != currentLastIndex; ++i)
		{
			// ������ ��� �������� 32bit ��� Ȯ���մϴ�.
			if (i < currentLastIndex - 1)
			{
				// �迭�� �� ���Ҹ��� 32bit�� Ȯ���մϴ�.
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
				// ������ ��Ҵ� ����� ��Ʈ ����ŭ�� Ȯ���մϴ�.
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
		// targetIndex��° bool ���� ������ ����Ǿ� �ִ� �迭�� �ε����� ��ȯ�ϰ�
		// �� ��° ��Ʈ������ n�� �����մϴ�.
		// ex) targetIndex�� 34��� 1�� ��ȯ�ϰ� n�� 2�� �����մϴ�.

		n = targetIndex % 32;
		return targetIndex / 32;
	}

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
		*/

		unsigned int tmp = 0;

		// remove�ϴ� ��Ʈ�� ���� ��Ʈ���� tmp�� �����մϴ�.
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

} // namespace
