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
	};

	SoundEffectManager();
	~SoundEffectManager();
	SoundEffectManager(const SoundEffectManager& other) = delete; //Copy constructor afzetten (rule of three)
	SoundEffectManager(SoundEffectManager&& other);

	SoundEffect* GiveSound(const Sounds& sound);

	SoundEffectManager& operator=(const SoundEffectManager& rhs) = delete; // asignment= operator afzetten
	SoundEffectManager& operator=(SoundEffectManager&& other);
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
};

