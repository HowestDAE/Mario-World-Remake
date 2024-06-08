#include "pch.h"
#include "EnemyManager.h"
#include "SoundEffect.h"
#include <cassert>

EnemyManager::EnemyManager(Texture* tex) noexcept
	:m_pTexture{tex}
{
}

EnemyManager::EnemyManager(EnemyManager&& other) noexcept
	:m_pTexture{ std::move(other.m_pTexture) }
	,m_pEnemies{std::move(other.m_pEnemies)}
{
	other.m_pTexture = nullptr;
	for (int idx{}; idx < m_pEnemies.size(); ++idx)
	{
		m_pEnemies[idx] = nullptr;
	}
}

EnemyManager::~EnemyManager() noexcept
{
	for (int idx{}; idx < m_pEnemies.size(); ++idx) 
	{
		delete m_pEnemies[idx];
		m_pEnemies[idx] = nullptr;
	}
}

void EnemyManager::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, Mario* mario) noexcept
{
	for (int idx{}; idx < m_pEnemies.size(); ++idx)
	{
		m_pEnemies[idx]->Update(elapsedSec,landscape,platforms,mario);
		m_pEnemies[idx]->CheckHit(mario);
	}
}

void EnemyManager::Draw() const noexcept
{
	for (int idx{}; idx < m_pEnemies.size();++idx)
	{
		m_pEnemies[idx]->Draw();
	}
}

void EnemyManager::PushBackEnemy(const Point2f& pos, const EnemyType& enemy, const SoundEffect* sound)
{
	assert(enemy != EnemyManager::EnemyType::PianhaPlant);
	assert(enemy != EnemyManager::EnemyType::Chuck);
	if (enemy == EnemyType::Enemy)
	{
		m_pEnemies.push_back(new Enemy(pos, m_pTexture, sound));
	}
	if (enemy == EnemyType::BulletBill)
	{
		m_pEnemies.push_back(new BulletBill(pos, m_pTexture, sound));
	}
	if (enemy == EnemyType::Koopa)
	{
		m_pEnemies.push_back(new Koopa(pos, m_pTexture, sound));
	}
	
	
}

void EnemyManager::PushBackEnemy(const Point2f& pos, const EnemyType& enemy, const SoundEffect* sound, const SoundEffect* spinSound)
{
	assert(enemy != EnemyManager::EnemyType::Enemy);
	assert(enemy != EnemyManager::EnemyType::BulletBill);
	assert(enemy != EnemyManager::EnemyType::Koopa);
	if (enemy == EnemyType::PianhaPlant)
	{
		m_pEnemies.push_back(new PiranhaPlant(pos, m_pTexture, sound, spinSound));
	}
	if (enemy == EnemyType::Chuck)
	{
		m_pEnemies.push_back(new Chuck(pos, m_pTexture, sound, spinSound));
	}
}

void EnemyManager::Reset() noexcept
{
	for (int idx{}; idx < m_pEnemies.size(); ++idx)
	{
		m_pEnemies[idx]->Reset();
	}
}

EnemyManager& EnemyManager::operator=(EnemyManager&& other) noexcept
{
	m_pTexture = std::move(other.m_pTexture);
	m_pEnemies = std::move(other.m_pEnemies);

	other.m_pTexture = nullptr;
	other.m_pTexture = nullptr;
	for (int idx{}; idx < m_pEnemies.size(); ++idx)
	{
		m_pEnemies[idx] = nullptr;
	}
	return *this;
}
