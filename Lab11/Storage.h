#pragma once

#include <memory>
#include <cassert>
#include <cstring>

namespace lab11
{
	template <typename T>
	class Storage final
	{
	public:
		Storage(size_t length);
		Storage(size_t length, const T& initialValue);
		Storage(const Storage& other);
		Storage(Storage&& other);
		~Storage() = default;

		Storage<T>& operator=(const Storage& rhs);
		Storage<T>& operator=(Storage&& rhs);

		bool Update(size_t index, const T& data);
		const std::unique_ptr<T[]>& GetData() const;
		inline size_t GetSize() const;

	private:
		using arrayType = std::unique_ptr<T[]>;
		using pointerType = T*;

		arrayType mArray;
		size_t mCapacity;
	};


	// public method

	template <typename T>
	Storage<T>::Storage(size_t length)
		: mArray(std::make_unique<T[]>(length))
		, mCapacity(length)
	{
	}

	template <typename T>
	Storage<T>::Storage(size_t length, const T& initialValue)
		: mArray(std::make_unique<T[]>(length))
		, mCapacity(length)
	{
		// ���� �ӵ��� ���� ���� �����͸� ���� �ʱ�ȭ(�Ҵ�)�մϴ�.

		auto rawArray = mArray.get();

		for (size_t i = 0; i < mCapacity; ++i)
		{
			rawArray[i] = initialValue;
		}
	}

	template <typename T>
	Storage<T>::Storage(const Storage& other)
		: mArray(std::make_unique<T[]>(other.mCapacity))
		, mCapacity(other.mCapacity)
	{
		pointerType dest = mArray.get();
		pointerType source = other.mArray.get();
		std::memcpy(dest, source, sizeof(T) * mCapacity);
	}

	template <typename T>
	Storage<T>::Storage(Storage&& other)
		: mArray(std::move(other.mArray))
		, mCapacity(other.mCapacity)
	{
		other.mArray = nullptr;
		other.mCapacity = 0;
	}

	template <typename T>
	Storage<T>& Storage<T>::operator=(const Storage& rhs)
	{
		if (this != &rhs)
		{
			// mArray�� ���ε��� ���� �����͸� �����մϴ�.
			mCapacity = rhs.mCapacity;
			mArray = nullptr;
			mArray = std::make_unique<T[]>(mCapacity);

			pointerType dest = mArray.get();
			pointerType source = rhs.mArray.get();

			// mArray�� rhs.mArray�� ��ī��
			std::memcpy(dest, source, sizeof(T) * mCapacity);
		}

		return *this;
	}

	template <typename T>
	Storage<T>& Storage<T>::operator=(Storage&& rhs)
	{
		if (this != &rhs)
		{
			mCapacity = rhs.mCapacity;
			mArray = nullptr;
			mArray = std::move(rhs.mArray);

			rhs.mArray = nullptr;
			rhs.mCapacity = 0;
		}

		return *this;
	}

	template <typename T>
	bool Storage<T>::Update(size_t index, const T& data)
	{
		// �迭�� index ��ġ�� ��Ҹ� data�� �����մϴ�.
		// ���濡 ���������� true, �׷��� ������ false�� ��ȯ�մϴ�.

		if (index >= mCapacity)
		{
			return false;
		}

		mArray[index] = data;

		return true;
	}

	template <typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return mArray;
	}

	template <typename T>
	inline size_t Storage<T>::GetSize() const
	{
		return mCapacity;
	}
}