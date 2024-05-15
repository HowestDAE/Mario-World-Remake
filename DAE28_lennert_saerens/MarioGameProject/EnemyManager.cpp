#include "pch.h"
#include "EnemyManager.h"
#include "SoundEffect.h"
#include <cassert>

EnemyManager::EnemyManager(Texture* tex)
	:m_pTexture{tex}
{
}

EnemyManager::EnemyManager(EnemyManager&& other)
	:m_pTexture{ std::move(other.m_pTexture) }
	,m_pEnemies{std::move(other.m_pEnemies)}
{
	other.m_pTexture = nullptr;

}

EnemyManager::~EnemyManager()
{
	for (int idx{}; idx < m_pEnemies.size(); ++idx)
	{
		delete m_pEnemies[idx];
		m_pEnemies[idx] = nullptr;
	}
}

void EnemyManager::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, Mario* mario)
{
	for (int idx{}; idx < m_pEnemies.size(); ++idx)
	{
		m_pEnemies[idx]->Update(elapsedSec,landscape,platforms,mario);
		m_pEnemies[idx]->CheckHit(mario);
	}
}

void EnemyManager::Draw() const
{
	for (int idx{}; idx < m_pEnemies.size();++idx)
	{
		m_pEnemies[idx]->Draw();
	}
}

void EnemyManager::PushBackEnemy(const Point2f& pos, const EnemyType& enemy, const SoundEffect* sound) 
{
	assert(enemy != EnemyManager::EnemyType::PianhaPlant);
	if (enemy == EnemyType::Enemy)
	{
		m_pEnemies.push_back(new Enemy(pos, m_pTexture, sound));
	}
	if (enemy == EnemyType::BulletBill)
	{
		m_pEnemies.push_back(new BulletBill(pos, m_pTexture, sound));
	}
	
}

void EnemyManager::PushBackPiranhaPlant(const Point2f& pos, const SoundEffect* sound, const SoundEffect* spinSound)
{
	m_pEnemies.push_back(new PiranhaPlant(pos, m_pTexture, sound,spinSound ));
}

EnemyManager& EnemyManager::operator=(EnemyManager&& other)
{
	m_pTexture = std::move(other.m_pTexture);
	m_pEnemies = std::move(other.m_pEnemies);

	other.m_pTexture = nullptr;
	return other;
}
