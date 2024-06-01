#include "pch.h"
#include "SoundEffectManager.h"

SoundEffectManager::SoundEffectManager()
{
	m_pCoinSound = new SoundEffect("Sounds/smw_coin.wav");
	m_pDragonCoinSound = new SoundEffect("Sounds/smw_dragon_coin.wav");
	m_pPowerUpSound = new SoundEffect("Sounds/smw_power-up.wav");
	m_pStompSound = new SoundEffect("Sounds/smw_stomp.wav");
	m_pSpinStompSound = new SoundEffect("Sounds/smw_stomp_no_damage.wav");
	m_pPipeHitSound = new SoundEffect("Sounds/smw_pipeandhit.wav");
	m_pClapSound = new SoundEffect("Sounds/smw_bubble_pop.wav");
	m_pCheckpointSound = new SoundEffect("Sounds/smw_midway_gate.wav");
	m_pBreakSound = new SoundEffect("Sounds/smw_break_block.wav");
	m_pPauseSound = new SoundEffect("Sounds/smw_pause.wav");
	
}

SoundEffectManager::~SoundEffectManager()
{
	delete m_pCoinSound;
	m_pCoinSound = nullptr;
	delete m_pDragonCoinSound;
	m_pDragonCoinSound = nullptr;
	delete m_pPowerUpSound;
	m_pPowerUpSound = nullptr;
	delete m_pStompSound;
	m_pStompSound = nullptr;
	delete m_pSpinStompSound;
	m_pSpinStompSound = nullptr;
	delete m_pPipeHitSound;
	m_pPipeHitSound = nullptr;
	delete m_pClapSound;
	m_pClapSound = nullptr;
	delete m_pCheckpointSound;
	m_pCheckpointSound = nullptr;
	delete m_pBreakSound;
	m_pBreakSound = nullptr;
	delete m_pPauseSound;
	m_pPauseSound = nullptr;
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

SoundEffect* SoundEffectManager::GiveSound(const Sounds& sound) const
{
	if (sound == Sounds::coins) return m_pCoinSound;
	else if (sound == Sounds::dragonCoins) return m_pDragonCoinSound;
	else if (sound == Sounds::PowerUp) return m_pPowerUpSound;
	else if (sound == Sounds::Stomp) return m_pStompSound;
	else if (sound == Sounds::spinStomp) return m_pStompSound;
	else if (sound == Sounds::pipeHit) return m_pPipeHitSound;
	else if (sound == Sounds::Clap) return m_pClapSound;
	else if (sound == Sounds::CheckPoint) return m_pCheckpointSound;
	else if (sound == Sounds::block) return m_pBreakSound;
	else if (sound == Sounds::pause) return m_pPauseSound;
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
