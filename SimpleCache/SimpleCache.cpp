#include "SimpleCache.h"

using namespace std;

namespace samples
{
	void SimpleCache::Add(string key, weak_ptr<MyVector2D> ptr)
	{
		// map에 <key, ptr> pair를 추가합니다.

		auto it = mMap.find(key);

		// key가 존재하지 않는다면 추가합니다.
		if (it == mMap.end())
		{
			mMap.insert(pair<string, weak_ptr<MyVector2D>>(key, ptr));
			return;
		}

		// key가 이미 존재한다면 데이터를 덮어씁니다.
		mMap[key] = ptr;
	}

	shared_ptr<MyVector2D> SimpleCache::Get(string key)
	{
		// key가 존재한다면 weak_ptr를 shared_ptr로 변환하여 반환합니다.
		auto it = mMap.find(key);

		// 존재하지 않으면 빈 shared_ptr을 반환합니다.
		if (it == mMap.end())
		{
			return shared_ptr<MyVector2D>();
		}

		// weak_ptr이 expired 상태라면 맵에서 삭제하고 빈 객체를 반환합니다.
		if (it->second.expired())
		{
			mMap.erase(it);
			return shared_ptr<MyVector2D>();
		}

		// shared_ptr을 추가로 생성하여 반환합니다.
		return it->second.lock();
	}
}