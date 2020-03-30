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
		// 빠른 속도를 위해 원시 포인터를 통해 초기화(할당)합니다.

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
			// mArray에 바인딩된 원시 포인터를 해제합니다.
			mCapacity = rhs.mCapacity;
			mArray = nullptr;
			mArray = std::make_unique<T[]>(mCapacity);

			pointerType dest = mArray.get();
			pointerType source = rhs.mArray.get();

			// mArray에 rhs.mArray를 딥카피
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
		// 배열의 index 위치의 요소를 data로 변경합니다.
		// 변경에 성공했으면 true, 그렇지 않으면 false를 반환합니다.

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