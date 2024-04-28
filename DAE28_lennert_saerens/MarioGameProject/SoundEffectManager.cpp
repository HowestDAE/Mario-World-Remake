#include "pch.h"
#include "SoundEffectManager.h"

SoundEffectManager::SoundEffectManager()
{
	m_pCoinSound = new SoundEffect("Sounds/smw_coin.wav");
	m_pDragonCoinSound = new SoundEffect("Sounds/smw_dragon_coin.wav");
	m_pPowerUpSound = new SoundEffect("Sounds/smw_power-up.wav");
}

SoundEffectManager::~SoundEffectManager()
{
	delete m_pCoinSound;
	m_pCoinSound = nullptr;
	delete m_pDragonCoinSound;
	m_pDragonCoinSound = nullptr;
	delete m_pPowerUpSound;
	m_pPowerUpSound = nullptr;
}

SoundEffectManager::SoundEffectManager(SoundEffectManager&& other)
	:m_pCoinSound{ std::move(other.m_pCoinSound) }
	, m_pDragonCoinSound{ std::move(other.m_pDragonCoinSound) }
	, m_pPowerUpSound{ std::move(other.m_pPowerUpSound) }
{
	other.m_pCoinSound = nullptr;
	other.m_pDragonCoinSound = nullptr;
	other.m_pPowerUpSound = nullptr;
}

SoundEffect* SoundEffectManager::GiveSound(const Sounds& sound)
{
	if (sound == Sounds::coins) return m_pCoinSound;
	if (sound == Sounds::dragonCoins) return m_pDragonCoinSound;
	else if (sound == Sounds::PowerUp) return m_pPowerUpSound;
}

SoundEffectManager& SoundEffectManager::operator=(SoundEffectManager&& other)
{
	if (&other != this)
	{
		m_pCoinSound = std::move(other.m_pCoinSound);
		m_pDragonCoinSound = std::move(other.m_pDragonCoinSound);
		m_pPowerUpSound = std::move(other.m_pPowerUpSound);

		other.m_pCoinSound = nullptr;
		other.m_pDragonCoinSound = nullptr;
		other.m_pPowerUpSound = nullptr;
	}

	return *this;
}
