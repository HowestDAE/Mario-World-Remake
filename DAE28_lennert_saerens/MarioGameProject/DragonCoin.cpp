#include "pch.h"
#include "DragonCoin.h"

DragonCoin::DragonCoin(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:Coin(pos, tex, sound)
{
}



void DragonCoin::Update(float elapsedSec)
{
	if (m_IsCollected == false)
	{
		m_ElapsedSec += elapsedSec;
		if (m_ElapsedSec >= m_FrameTime)
		{
			m_ElapsedSec = 0;
			++m_CurrFrame;
			if (m_CurrFrame > 6) m_CurrFrame = 0;
		}
		if (m_CurrFrame == 0) m_SrcRect = Rectf(0, 60, 16, 25);
		else if (m_CurrFrame == 1) m_SrcRect = Rectf(16, 60, 16, 25);
		else if (m_CurrFrame == 2) m_SrcRect = Rectf(32, 60, 16, 25);
		else if (m_CurrFrame == 3) m_SrcRect = Rectf(48, 60, 16, 25);
		else if (m_CurrFrame == 4) m_SrcRect = Rectf(64, 60, 16, 25);
		else if (m_CurrFrame == 5) m_SrcRect = Rectf(80, 60, 16, 25);
	}
}
