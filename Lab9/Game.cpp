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
		// Pool���� IceCube ��ü�� ������ �ʱ�ȭ �� ActiveGameObjects�� �߰��մϴ�.
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

			// ������ �ʴ� ��ü�� mActiveGameObjects�κ��� 
			// �����ϰ� pool�� ��ȯ�մϴ�.
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