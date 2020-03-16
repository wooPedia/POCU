#include "Game.h"

namespace lab9
{
	Game::Game(unsigned int seed, unsigned int poolSize)
		: mIceCubePool(poolSize)
	{
		srand(seed);
	}

	Game::~Game()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it)
		{
			delete (*it);
		}

		mActiveGameObjects.clear();
	}

	void Game::Spawn()
	{
		// Pool에서 IceCube 개체를 가져와 초기화 후 ActiveGameObjects에 추가합니다.
		IceCube* iceCube = mIceCubePool.Get();
		iceCube->Initialize(rand() % MAX_FRAME_COUNT_TO_LIVE + 1);
		mActiveGameObjects.push_back(iceCube);
	}

	void Game::Update()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end();)
		{
			IceCube* iceCube = *it;
			iceCube->Animate();

			// 사용되지 않는 개체를 mActiveGameObjects로부터 
			// 삭제하고 pool에 반환합니다.
			if (!iceCube->IsActive())
			{
				it = mActiveGameObjects.erase(it);
				mIceCubePool.Return(iceCube);
				continue;
			}

			++it;
		}
	}

	const std::vector<IceCube*>& Game::GetActiveGameObjects() const
	{
		return mActiveGameObjects;
	}

	ObjectPool<IceCube>& Game::GetObjectPool()
	{
		return mIceCubePool;
	}

} // namespace