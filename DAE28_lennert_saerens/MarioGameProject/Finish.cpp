#include "pch.h"
#include "Finish.h"

Finish::Finish(const Point2f& pos, const Texture* tex, const SoundEffect* sound) noexcept
	:m_IsHit{false}
	,m_pTexture{tex}
	,m_Pos{pos}
	,m_pSoundEffect{sound}
	,m_BarPos{pos}
	,m_OriginalPos{pos}
	,m_Vel{0,30.f}
{
	m_SrcRectPole = Rectf(0, 64, 32, 64);
	m_SrcRectBar = Rectf(8, 73, 18, 3);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRectBar.width*4, m_SrcRectBar.height*4);
	m_PoleBounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRectPole.width *4 , m_SrcRectPole.height *4);
}

void Finish::Draw() const noexcept
{
	m_pTexture->Draw(m_PoleBounds, m_SrcRectPole);
	if (!m_IsHit)
	{
		m_pTexture->Draw(m_Bounds, m_SrcRectBar);
	}
}

void Finish::CheckIsHit(Mario* mario) noexcept
{
	if (!mario->GetFinishHit())
	{
		if (utils::IsOverlapping(mario->GetBounds(), m_Bounds))
		{
			m_IsHit = true;
			mario->SetFinishHit(true);
			mario->SetVelX(0);
			mario->AddPoints(1000);
		}
	}
}

void Finish::Update(float elapsedSec) noexcept
{
	m_Pos.y += m_Vel.y * elapsedSec;
	if (m_Pos.y >= m_OriginalPos.y + 60*4)
	{
		m_Vel.y = -30.f;
	}
	else if (m_Pos.y <= m_OriginalPos.y)
	{
		m_Vel.y = 30.f;
	}

	m_Bounds = Rectf(m_Pos.x + 6 * 4, m_Pos.y, m_SrcRectBar.width *4 , m_SrcRectBar.height*4);


}
