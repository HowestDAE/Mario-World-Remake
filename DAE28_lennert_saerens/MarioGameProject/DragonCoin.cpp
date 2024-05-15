#include "pch.h"
#include "DragonCoin.h"

DragonCoin::DragonCoin(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:Coin(pos, tex, sound)
{
}



void DragonCoin::Animate()
{
	if (m_IsCollected == false)
	{
		if (m_CurrFrame%6 == 0) m_SrcRect = Rectf(0, 60, 16, 25);
		else if (m_CurrFrame%6 == 1) m_SrcRect = Rectf(16, 60, 16, 25);
		else if (m_CurrFrame%6 == 2) m_SrcRect = Rectf(32, 60, 16, 25);
		else if (m_CurrFrame%6 == 3) m_SrcRect = Rectf(48, 60, 16, 25);
		else if (m_CurrFrame%6 == 4) m_SrcRect = Rectf(64, 60, 16, 25);
		else if (m_CurrFrame%6 == 5) m_SrcRect = Rectf(80, 60, 16, 25);
	}
}
