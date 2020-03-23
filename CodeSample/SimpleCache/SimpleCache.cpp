#include "SimpleCache.h"

using namespace std;

namespace samples
{
	void SimpleCache::Add(string key, weak_ptr<MyVector2D> ptr)
	{
		// map�� <key, ptr> pair�� �߰��մϴ�.

		auto it = mMap.find(key);

		// key�� �������� �ʴ´ٸ� �߰��մϴ�.
		if (it == mMap.end())
		{
			mMap.insert(pair<string, weak_ptr<MyVector2D>>(key, ptr));
			return;
		}

		// key�� �̹� �����Ѵٸ� �����͸� ����ϴ�.
		mMap[key] = ptr;
	}

	shared_ptr<MyVector2D> SimpleCache::Get(string key)
	{
		// key�� �����Ѵٸ� weak_ptr�� shared_ptr�� ��ȯ�Ͽ� ��ȯ�մϴ�.
		auto it = mMap.find(key);

		// �������� ������ �� shared_ptr�� ��ȯ�մϴ�.
		if (it == mMap.end())
		{
			return shared_ptr<MyVector2D>();
		}

		// weak_ptr�� expired ���¶�� �ʿ��� �����ϰ� �� ��ü�� ��ȯ�մϴ�.
		if (it->second.expired())
		{
			mMap.erase(it);
			return shared_ptr<MyVector2D>();
		}

		// shared_ptr�� �߰��� �����Ͽ� ��ȯ�մϴ�.
		return it->second.lock();
	}
}