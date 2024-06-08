#include "pch.h"
#include "QBlock.h"

QBlock::QBlock(const Point2f& pos, const Texture* tex, const SoundEffect* sound, PowerUp* content) noexcept
	:Block::Block(pos,tex,sound)
{
	m_pContent = content;
	m_SrcRect = Rectf(48, 80, 16, 16);
	m_CollectablePowerUp = false;
}

void QBlock::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks) noexcept
{
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
	Animate(elapsedSec);
	if (m_CollectablePowerUp)
	{
		m_pContent->Update(elapsedSec,landscape,platforms, blocks);
	}
}

void QBlock::CheckHit(Mario* mario) noexcept
{
		Rectf marioRect{ mario->GetBounds() };
		Rectf marioHeadRect{ marioRect.left,marioRect.bottom + (marioRect.height / 4) * 3 ,marioRect.width, marioRect.height / 4 };

		Rectf topRect{ m_Bounds.left + 5,m_Bounds.bottom + ((m_Bounds.height / 8) * 7),m_Bounds.width - 10, m_Bounds.height / 8 };
		Rectf bottomRect{ m_Bounds.left + 5 ,m_Bounds.bottom ,m_Bounds.width - 5, m_Bounds.height / 8 };
		Rectf leftRect{ m_Bounds.left,m_Bounds.bottom + 5,(m_Bounds.width / 8) * 7 , m_Bounds.height - 10 };
		Rectf rightRect{ m_Bounds.left + (m_Bounds.width / 8) * 7  ,m_Bounds.bottom + 5 ,(m_Bounds.width / 8) * 7, m_Bounds.height - 10 };

		if (utils::IsOverlapping(marioHeadRect, bottomRect) && mario->GetVel().y > 10.f)
		{
			m_IsHit = true;
			mario->SetVelY(0);
			mario->SetCanJump(false);
			if (mario->GetPowerUpState() == Mario::PowerUpState::small)
			{
				m_pContent->SetPowerUpType(PowerUp::PowerUpType::Mushroom);
			}
			else if (mario->GetPowerUpState() == Mario::PowerUpState::big || (mario->GetPowerUpState() == Mario::PowerUpState::fireflower))
			{
				m_pContent->SetPowerUpType(PowerUp::PowerUpType::Flower);
			}
			m_CollectablePowerUp = true;
			m_pContent->SetPosY(m_Bounds.bottom + m_Bounds.height);
			m_pContent->SetIsCollectable(true);
		}
		else  if (utils::IsOverlapping(marioRect, topRect))
		{
				mario->SetPosY(m_Pos.y + m_Bounds.height);
				mario->SetIsOnGround();
		}
		else  if (utils::IsOverlapping(marioRect, leftRect) && mario->GetVel().x > 0)
		{
			mario->SetVelX(0);
			mario->SetPosX(m_Pos.x - mario->GetBounds().width - 1);
		}
		else  if (utils::IsOverlapping(marioRect, rightRect) && mario->GetVel().x < 0)
		{
			mario->SetVelX(0);
			mario->SetPosX(m_Pos.x + m_Bounds.width + 1);
		}
}

void QBlock::Draw() const noexcept
{
	if (m_CollectablePowerUp)
	{
		m_pContent->Draw();
	}
	if (!m_IsBroken)
	{
		m_pTexture->Draw(m_Bounds, m_SrcRect);
	}
}

void QBlock::Reset() noexcept
{
	m_IsBroken = false;
	m_IsHit = false;
	m_HitSec = 0;
	m_FrameSec = 0;
	m_FrameNr = 0;
	m_SrcRect = Rectf(48, 80, 16, 16);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
	m_CollectablePowerUp = false;
}

void QBlock::Animate(float elapsedSec) noexcept
{
	m_FrameSec += elapsedSec;
	if (!m_IsHit)
	{
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
				m_SrcRect = Rectf(48, 80, 16, 16);
			}
			else if (m_FrameNr == 1)
			{
				m_SrcRect = Rectf(32, 80, 16, 16);
			}
			else if (m_FrameNr == 2)
			{
				m_SrcRect = Rectf(16, 80, 16, 16);
			}
			else if (m_FrameNr == 3)
			{
				m_SrcRect = Rectf(0, 80, 16, 16);
			}
		}
	}
	else
	{
		m_SrcRect = Rectf(64, 80, 16, 16);

	}

}
