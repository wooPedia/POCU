#pragma once

#include <queue>
#include <stack>
#include <cassert>
#include <type_traits>

#include "ERounding.h"

namespace assignment3
{
	/*
		===========================================
					QueueStack<T> 클래스
		===========================================
	*/

	template <typename T>
	class QueueStack
	{
	public:
		using queueStack = std::queue<std::stack<T> >;

		QueueStack() = delete;
		QueueStack(size_t maxStackSize);
		//QueueStack(const QueueStack& other);
		//~QueueStack();
		//QueueStack<T>& operator=(const QueueStack& rhs);

		void Enqueue(T number);
		inline T Peek() const;
		T Dequeue();

		T GetMax();
		T GetMin();
		inline T GetSum() const;
		inline double GetAverage() const;
		inline size_t GetCount() const;
		inline size_t GetStackCount() const;

		// 추가한 함수
		inline bool Empty() const;

	private:
		queueStack mQueueStack;
	};

	/*
		===========================================
					  public 멤버 함수
		===========================================
	*/

	template <typename T>
	QueueStack<T>::QueueStack(size_t maxStackSize)
	{

	}

	template <typename T>
	void QueueStack<T>::Enqueue(T number)
	{

	}

	template <typename T>
	inline T QueueStack<T>::Peek() const
	{
		return T();
	}

	template <typename T>
	T QueueStack<T>::Dequeue()
	{
		return T();
	}

	template <typename T>
	T QueueStack<T>::GetMax()
	{
		return T();
	}

	template <typename T>
	T QueueStack<T>::GetMin()
	{
		return T();
	}

	template <typename T>
	inline T QueueStack<T>::GetSum() const
	{
		return T();
	}

	template <typename T>
	inline double QueueStack<T>::GetAverage() const
	{
		return double();
	}

	template <typename T>
	inline size_t QueueStack<T>::GetCount() const
	{
		return size_t();
	}

	template <typename T>
	inline size_t QueueStack<T>::GetStackCount() const
	{
		return size_t();
	}

	// 추가한 함수
	template <typename T>
	inline bool QueueStack<T>::Empty() const
	{
		return true;
	}


	/*
		===========================================
					  private 멤버 함수
		===========================================
	*/

} // namespace
