#include "pch.h"
#include "Checkpoint.h"

Checkpoint::Checkpoint(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:m_IsHit{false}
	,m_Pos{pos}
	,m_pSoundEffect{sound}
	,m_pTexture{tex}
{
	m_SrcRect = Rectf(0, 32, 32, 32);

}

void Checkpoint::Draw() const
{
	m_pTexture->Draw(m_Bounds, m_SrcRect);
}

void Checkpoint::CheckIsHit(Mario* mario)
{
	if (m_IsHit == false)
	{
		if (utils::IsOverlapping(mario->GetBounds(), m_Bounds))
		{
			m_IsHit = true;
			mario->SetCheckpointHit();
			m_pSoundEffect->Play(0);
		}
	}
}

void Checkpoint::Update()
{
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);

	if (m_IsHit)
	{
		m_SrcRect = Rectf(0, 0, 32, 32);
	}
	else
	{
		m_SrcRect = Rectf(33, 0, 32, 32);

	}
}
