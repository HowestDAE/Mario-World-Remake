#include "pch.h"
#include "SoundEffectManager.h"

SoundEffectManager::SoundEffectManager() noexcept
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
	m_pCannonSound = new SoundEffect("Sounds/smw_thud.wav");
	
}

SoundEffectManager::~SoundEffectManager() noexcept
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
	delete m_pCannonSound;
	m_pCannonSound = nullptr;
}

SoundEffectManager::SoundEffectManager(SoundEffectManager&& other) noexcept
	:m_pCoinSound{ std::move(other.m_pCoinSound) }
	, m_pDragonCoinSound{ std::move(other.m_pDragonCoinSound) }
	, m_pPowerUpSound{ std::move(other.m_pPowerUpSound) }
	, m_pStompSound{std::move(other.m_pStompSound)}
	, m_pSpinStompSound{std::move(other.m_pSpinStompSound)}
	, m_pPipeHitSound{std::move(other.m_pPipeHitSound)}
	, m_pClapSound{std::move(other.m_pClapSound)}
	, m_pCheckpointSound{std::move(other.m_pCheckpointSound)}
	, m_pBreakSound{std::move(other.m_pBreakSound)}
	, m_pPauseSound{std::move(other.m_pPauseSound)}
	, m_pCannonSound{std::move(other.m_pCannonSound)}
//SoundEffect* m_pCoinSound;
//SoundEffect* m_pDragonCoinSound;
//SoundEffect* m_pPowerUpSound;
//SoundEffect* m_pStompSound;
//SoundEffect* m_pSpinStompSound;
//SoundEffect* m_pPipeHitSound;
//SoundEffect* m_pClapSound;
//SoundEffect* m_pCheckpointSound;
//SoundEffect* m_pBreakSound;
//SoundEffect* m_pPauseSound;
//SoundEffect* m_pCannonSound;
{
	other.m_pCoinSound = nullptr;
	other.m_pDragonCoinSound = nullptr;
	other.m_pPowerUpSound = nullptr;
	other.m_pStompSound = nullptr;
	other.m_pSpinStompSound = nullptr;
	other.m_pPipeHitSound = nullptr;
	other.m_pClapSound = nullptr;
	other.m_pCheckpointSound = nullptr;
	other.m_pBreakSound = nullptr;
	other.m_pPauseSound = nullptr;
	other.m_pCannonSound = nullptr;
}

SoundEffect* SoundEffectManager::GiveSound(const Sounds& sound) const noexcept
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
	else if (sound == Sounds::cannon) return m_pCannonSound;
}

SoundEffectManager& SoundEffectManager::operator=(SoundEffectManager&& other) noexcept
{
	if (&other != this)
	{
		m_pCoinSound = std::move(other.m_pCoinSound);
		m_pDragonCoinSound = std::move(other.m_pDragonCoinSound);
		m_pPowerUpSound = std::move(other.m_pPowerUpSound);
		m_pStompSound = std::move(other.m_pStompSound);
		m_pSpinStompSound = std::move(other.m_pSpinStompSound);
		m_pPipeHitSound = std::move(other.m_pPipeHitSound);
		m_pClapSound = std::move(other.m_pClapSound);
		m_pCheckpointSound = std::move(other.m_pCheckpointSound);
		m_pBreakSound = std::move(other.m_pBreakSound);
		m_pPauseSound = std::move(other.m_pPauseSound);
		m_pCannonSound = std::move(other.m_pCannonSound);

		other.m_pCoinSound = nullptr;
		other.m_pDragonCoinSound = nullptr;
		other.m_pPowerUpSound = nullptr;
		other.m_pStompSound = nullptr;
		other.m_pSpinStompSound = nullptr;
		other.m_pPipeHitSound = nullptr;
		other.m_pClapSound = nullptr;
		other.m_pCheckpointSound = nullptr;
		other.m_pBreakSound = nullptr;
		other.m_pPauseSound = nullptr;
		other.m_pCannonSound = nullptr;
	}

	return *this;
}
