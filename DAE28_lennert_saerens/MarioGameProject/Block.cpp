#include "pch.h"
#include "Block.h"

Block::Block(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:m_IsBroken{false}
	,m_IsHit{false}
	,m_Pos{pos}
	,m_pSoundEffect{sound}
	,m_pTexture{tex}
	,m_HitSec{0}
	,m_FrameSec{0}
	,m_FrameNr{0}
{
	m_SrcRect = Rectf(0, 96, 16, 16);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);


}

void Block::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, std::vector<Block*> blocks)
{
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);

	if (!m_IsBroken)
	{
		if (m_HitSec > 0)
		{
			m_HitSec -= elapsedSec;
			m_IsHit = true;
		}
		else
		{
			m_IsHit = false;
		}
	}
	Animate(elapsedSec);
}

void Block::Draw() const
{
	if (!m_IsBroken)
	{
		m_pTexture->Draw(m_Bounds, m_SrcRect);
	}
}

void Block::CheckHit(Mario* mario)
{
	if (!m_IsBroken && !m_IsHit)
	{
		Rectf marioRect{ mario->GetBounds() };
		Rectf marioHeadRect{ marioRect.left,marioRect.bottom + (marioRect.height / 4)*3 ,marioRect.width, marioRect.height / 4 };

		Rectf topRect{ m_Bounds.left + 5,m_Bounds.bottom + ((m_Bounds.height / 8) * 7),m_Bounds.width - 10, m_Bounds.height / 8 };
		Rectf bottomRect{ m_Bounds.left + 5 ,m_Bounds.bottom ,m_Bounds.width - 5, m_Bounds.height / 8 };
		Rectf leftRect{ m_Bounds.left,m_Bounds.bottom +5,(m_Bounds.width/8) *7 , m_Bounds.height - 10 };
		Rectf rightRect{ m_Bounds.left + (m_Bounds.width / 8) * 7  ,m_Bounds.bottom + 5 ,(m_Bounds.width / 8) * 7, m_Bounds.height - 10 };

		if (utils::IsOverlapping(marioHeadRect, bottomRect) && mario->GetVel().y >10.f)
		{
			m_HitSec = 5.f;
			mario->SetVelY(0);
			mario->SetCanJump(false);
		}
		else  if (utils::IsOverlapping(marioRect, topRect))
		{
			if (mario->GetState() == Mario::LookingState::leftSpin || mario->GetState() == Mario::LookingState::rightSpin)
			{
				mario->Bounce(m_Pos.y + m_Bounds.height);
				m_pSoundEffect->Play(0);
				m_IsBroken = true;
			}
			else
			{
				mario->SetPosY(m_Pos.y + m_Bounds.height);
				mario->SetIsOnGround();
			}
		}
		else  if (utils::IsOverlapping(marioRect, leftRect) && mario->GetVel().x >0)
		{
			mario->SetVelX(0);
			mario->SetPosX(m_Pos.x - mario->GetBounds().width - 1);
		}
		else  if (utils::IsOverlapping(marioRect, rightRect) && mario->GetVel().x < 0)
		{
			mario->SetVelX(0);
			mario->SetPosX(m_Pos.x + m_Bounds.width+ 1);
		}
	}
}

void Block::Reset()
{
	m_IsBroken = false;
	m_IsHit = false;
	m_HitSec = 0;
	m_FrameSec = 0;
	m_FrameNr = 0;
	m_SrcRect = Rectf(0, 96, 16, 16);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
}

bool Block::GetIsHit()
{
	return m_IsHit;
}

bool Block::GetIsBroken()
{
	return m_IsBroken;
}

Rectf Block::GetBounds()
{
	return m_Bounds;
}

void Block::Animate(float elapsedSec)
{
	if (m_HitSec > 0)
	{
		m_FrameSec += elapsedSec;
		if (m_FrameSec > 0.25f)
		{
			m_FrameSec = 0;
			++m_FrameNr;
			if (m_FrameNr == 4)
			{
				m_FrameNr = 0;
			}
			if (m_FrameNr == 0)
			{
				m_SrcRect = Rectf(16, 96, 16, 16);
			}
			else if (m_FrameNr == 1)
			{
				m_SrcRect = Rectf(32, 96, 16, 16);
			}
			else if (m_FrameNr == 2)
			{
				m_SrcRect = Rectf(48, 96, 16, 16);
			}
			else if (m_FrameNr == 3)
			{
				m_SrcRect = Rectf(0, 96, 16, 16);
			}
		}
	}
	else
	{
		m_SrcRect = Rectf(0, 96, 16, 16);
	}
}
