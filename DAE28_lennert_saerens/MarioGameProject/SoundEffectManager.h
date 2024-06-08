#pragma once
#include "SoundEffect.h"

class SoundEffectManager final
{
public:
	enum class Sounds
	{
		coins,
		dragonCoins,
		PowerUp,
		Stomp,
		spinStomp,
		pipeHit,
		Clap,
		CheckPoint,
		block,
		pause,
		cannon,
	};

	explicit SoundEffectManager() noexcept;
	~SoundEffectManager() noexcept;
	SoundEffectManager(const SoundEffectManager& other) = delete; //Copy constructor afzetten (rule of three)
	SoundEffectManager(SoundEffectManager&& other) noexcept;

	SoundEffect* GiveSound(const Sounds& sound) const noexcept;

	SoundEffectManager& operator=(const SoundEffectManager& rhs) = delete; // asignment= operator afzetten
	SoundEffectManager& operator=(SoundEffectManager&& other) noexcept;
protected:
	SoundEffect* m_pCoinSound;
	SoundEffect* m_pDragonCoinSound;
	SoundEffect* m_pPowerUpSound;
	SoundEffect* m_pStompSound;
	SoundEffect* m_pSpinStompSound;
	SoundEffect* m_pPipeHitSound;
	SoundEffect* m_pClapSound;
	SoundEffect* m_pCheckpointSound;
	SoundEffect* m_pBreakSound;
	SoundEffect* m_pPauseSound;
	SoundEffect* m_pCannonSound;
};

