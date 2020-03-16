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
		// pool�� ����� ��ü�� ��� ����ϴ�.
		for (auto& instance : mPool)
		{
			delete instance;
		}

		mPool.clear();
	}

	template <class T>
	T* ObjectPool<T>::Get()
	{
		// Pool���� ���� ���� ����� T* �� ��ȯ�մϴ�.
		// Pool�� ��������� ���ο� T*�� �����Ͽ� ��ȯ�մϴ�.

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
		// instance�� pool�� �����մϴ�.
		// pool�� ���� á�ٸ� instance�� ����ϴ�.

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