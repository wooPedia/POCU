#pragma once

#include <list>
#include <cassert>

namespace lab9
{
	template <class T>
	class ObjectPool final
	{
	public:
		ObjectPool(size_t maxPoolSize);
		ObjectPool(const ObjectPool& other) = delete;
		~ObjectPool();

		ObjectPool& operator=(const ObjectPool& rhs) = delete;
		T* Get();
		void Return(T* instance);
		inline size_t GetFreeObjectCount() const;
		inline size_t GetMaxFreeObjectCount() const;


	private:
		using objectPointerPool = std::list<T*>;

		size_t mMaxPoolSize;
		objectPointerPool mPool;
	};


	// public method

	template <class T>
	ObjectPool<T>::ObjectPool(size_t maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}

	template <class T>
	ObjectPool<T>::~ObjectPool()
	{
		// pool에 저장된 개체를 모두 지웁니다.
		for (auto& instance : mPool)
		{
			delete instance;
		}

		mPool.clear();
	}

	template <class T>
	T* ObjectPool<T>::Get()
	{
		// Pool에서 가장 먼저 저장된 T* 을 반환합니다.
		// Pool이 비어있으면 새로운 T*을 생성하여 반환합니다.

		if (!mPool.empty())
		{
			T* oldObj = mPool.front();
			mPool.pop_front();

			return oldObj;
		}

		return new T();
	}

	template <class T>
	void ObjectPool<T>::Return(T* instance)
	{
		// instance를 pool에 저장합니다.
		// pool이 가득 찼다면 instance를 지웁니다.

		if (mPool.size() == mMaxPoolSize)
		{
			delete instance;
			return;
		}

		//assert(mPool.size() < mMaxPoolSize);
		mPool.push_back(instance);
	}

	template <class T>
	inline size_t ObjectPool<T>::GetFreeObjectCount() const
	{
		//assert(mPool.size() <= mMaxPoolSize);
		return mPool.size();
	}

	template <class T>
	inline size_t ObjectPool<T>::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}

} // namespace 