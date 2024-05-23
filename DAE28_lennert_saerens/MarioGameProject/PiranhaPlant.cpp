#include "pch.h"
#include "PiranhaPlant.h"
#include "Mario.h"

PiranhaPlant::PiranhaPlant(const Point2f& pos, const Texture* tex, const SoundEffect* sound, const SoundEffect* spinsound)
	:Enemy::Enemy(pos, tex, sound)
	, m_pSpinSound{ spinsound }
	,m_AnimSec{0}
{
	m_FrameTime = 0.2f;
	m_HP = 1;
	m_SrcRect = Rectf(5, 56, 16, 21);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
	m_Velocity = Vector2f(0.f, 0.f);
}

void PiranhaPlant::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario)
{
	if (m_Pos.x - mario->GetPos().x <= 500.f && mario->GetPos().x - m_Pos.x >= -500.f)
	{
		const float gravity{ -0.5f };
		m_Pos.x += m_Velocity.x * elapsedSec;
		m_Pos.y += m_Velocity.y * elapsedSec;

		m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);

		if (m_HP <= 0)
		{
			m_DeathAnimation = true;
		}
		if (m_DeathAnimation == true)
		{
			m_Velocity = Vector2f(-30.f, -200.f);
		}
		if (m_DeathAnimation == false)
		{
			if (m_Bounds.bottom <= m_OriginalPos.y)
			{
				m_Bounds.bottom = m_OriginalPos.y;
				m_Velocity.y = 0;
				m_ElapsedSec += elapsedSec;
			}
			if (m_ElapsedSec >= 3)
			{
				m_Bounds.bottom = m_OriginalPos.y + 1;
				m_Velocity.y = 350.f;
				m_ElapsedSec = 0;
			}
			if (m_Pos.y >= (m_OriginalPos.y + 200.f) && m_Velocity.y > 0)
			{
				m_Velocity.y = -75;
			}
		}
	}
	Animate(elapsedSec);
}

void PiranhaPlant::CheckHit(Mario* mario)
{
	if (m_DeathAnimation == false)
	{
		Rectf marioRect{ mario->GetBounds() };
		Rectf marioBodyRect{ marioRect.left,marioRect.bottom ,marioRect.width, ((marioRect.height / 4) * 2) };

		Rectf enemyHeadRect{ m_Bounds.left,m_Bounds.bottom + ((m_Bounds.height / 4) * 3),m_Bounds.width, m_Bounds.height / 4 };
		Rectf enemyBodyRect{ m_Bounds.left,m_Bounds.bottom ,m_Bounds.width, ((m_Bounds.height / 4) * 3) };

		if (utils::IsOverlapping(marioBodyRect, enemyHeadRect) && (mario->GetVel().y < 1))
		{
			if (mario->GetState() == Mario::LookingState::leftSpin || mario->GetState() == Mario::LookingState::rightSpin)
			{
				m_pSpinSound->Play(0);
				mario->Bounce(m_Pos.y + m_Bounds.height);
			}
			
		}
		else if (utils::IsOverlapping(marioBodyRect, enemyBodyRect))
		{
			mario->TakeDamage();

		}
		std::vector<FireBall*> fireBalls{ mario->GetFireBalls() };
		for (int idx{}; idx < fireBalls.size(); ++idx)
		{
			if (fireBalls[idx] != nullptr)
			{
				if (utils::IsOverlapping(fireBalls[idx]->GetBounds(), m_Bounds))
				{
					m_HP -= 2;
					m_StompSound->Play(0);
					fireBalls[idx]->SetDead();
				}
			}
		}
	}
}

void PiranhaPlant::Reset()
{
	m_IsAlive = true;
	m_Pos = m_OriginalPos;
	m_DeathAnimation = false;
	m_Deathtimer = 0;
	m_FrameNr = 0;
	m_ElapsedSec = 0;
	m_HP = 2;
	m_LookingRight = false;
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
	m_Velocity = Vector2f(0, 0);

}


void PiranhaPlant::Animate(float elapsedSec)
{
	m_AnimSec+= elapsedSec;
	if (m_Bounds.bottom <= m_OriginalPos.y)
	{
		m_SrcRect = Rectf(5, 57	, 16, 21);
	}
	else if (m_Velocity.y >= 30)
	{
		m_SrcRect = Rectf(24, 55, 16, 20);
	}
	else if (m_Pos.y >= m_OriginalPos.y +180.f)
	{
		m_SrcRect = Rectf(5, 57, 16, 21);
	}
	else if (m_Velocity.y <= -30)
	{
		if (m_AnimSec >= m_FrameTime)
		{
			m_AnimSec = 0;
			++m_FrameNr;
		}
		if (m_FrameNr > 1)
		{
			m_FrameNr = 0;
		}
		if (m_FrameNr == 0)
		{
			m_SrcRect = Rectf(44, 57, 16, 21);
		}
		else if (m_FrameNr == 1)
		{
			m_SrcRect = Rectf(64, 57, 16, 20);

		}
	}
}


