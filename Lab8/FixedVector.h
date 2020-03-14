#pragma once

#include <cassert>
#include <type_traits>

namespace lab8
{
	// FixedVector class

	template <typename T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		~FixedVector() = default;
		FixedVector(const FixedVector& other);
		FixedVector<T, N>& operator=(const FixedVector& rhs);

		bool Add(const T& t);
		bool Remove(const T& t);
		const T& Get(size_t index) const;

		T& operator[](size_t index);

		int GetIndex(const T& t) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		size_t mSize;
		T mFixedVector[N];
	};


	// Public method

	template <typename T, size_t N>
	FixedVector<T, N>::FixedVector()
		: mSize(0)
		, mFixedVector{ 0, }
	{
	}


	template <typename T, size_t N>
	FixedVector<T, N>::FixedVector(const FixedVector& other)
		: mSize(other.mSize)
	{
		if (std::is_pointer_v<T>)
		{
			for (size_t i = 0; i != mSize; ++i)
			{
				mFixedVector[i] = new auto(*(other.mFixedVector[i]));
			}
		}
		else
		{
			for (size_t i = 0; i != mSize; ++i)
			{
				mFixedVector[i] = other.mFixedVector[i];
			}
		}
	}

	template <typename T, size_t N>
	FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		if (std::is_pointer_v<T>)
		{
			for (auto& element : mFixedVector)
			{
				element = nullptr;
			}

			mSize = rhs.mSize;
			for (size_t i = 0; i != mSize; ++i)
			{
				mFixedVector[i] = new auto(*(rhs.mFixedVector[i]));
			}
		}
		else
		{
			for (auto& element : mFixedVector)
			{
				element = NULL;
			}

			mSize = rhs.mSize;
			for (size_t i = 0; i != mSize; ++i)
			{
				mFixedVector[i] = rhs.mFixedVector[i];
			}
		}

		return *this;
	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Add(const T& t)
	{
		// Add�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.

		if (mSize >= N)
		{
			return false;
		}

		mFixedVector[mSize++] = t;
		assert(mSize <= N);

		return true;
	}

	template <typename T, size_t N>
	bool FixedVector<T, N>::Remove(const T& t)
	{
		// Remove�� �����ϸ� true, �����ϸ� false�� ��ȯ�մϴ�.

		if (mSize == 0)
		{
			return false;
		}

		// 0 1 2 3 4
		// �迭���� t�� ��ġ�ϴ� ��Ҹ� Ž���մϴ�.
		for (size_t i = 0; i != mSize; ++i)
		{
			// ��ġ�ϴ� ��Ҹ� �߰��ߴٸ� �� ��ҵ��� ��ĭ�� ��� �������մϴ�. 
			if (mFixedVector[i] == t)
			{
				while (i != mSize)
				{
					mFixedVector[i] = mFixedVector[i + 1];
					++i;
				}
				mFixedVector[mSize - 1] = NULL;
				--mSize;
				return true;
			}
		}

		return false;
	}

	template <typename T, size_t N>
	const T& FixedVector<T, N>::Get(size_t index) const
	{
		assert(index < mSize);

		return mFixedVector[index];
	}

	template <typename T, size_t N>
	T& FixedVector<T, N>::operator[](size_t index)
	{
		assert(index >= 0);

		return mFixedVector[index];
	}

	template <typename T, size_t N>
	int FixedVector<T, N>::GetIndex(const T& t) const
	{
		if (mSize == 0)
		{
			return -1;
		}

		// �迭���� t�� ��ġ�ϴ� ��Ҹ� Ž���մϴ�.
		for (size_t i = 0; i != mSize; ++i)
		{
			// t�� ��ġ�ϴ� ��Ҹ� �߰��ߴٸ� �ش� �ε����� ��ȯ�մϴ�.
			if (mFixedVector[i] == t)
			{
				return i;
			}
		}

		return -1;
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetSize() const
	{
		return mSize;
	}

	template <typename T, size_t N>
	size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}

}