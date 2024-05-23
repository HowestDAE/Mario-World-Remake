#include "pch.h"
#include "BulletBill.h"
#include "Mario.h"

BulletBill::BulletBill(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:Enemy::Enemy(pos, tex, sound)
{
	m_HP = 1;
	m_SrcRect = Rectf(129, 163, 64, 64);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width*2, m_SrcRect.height*2);
	m_Velocity = Vector2f(-100.f, 0.f);
	m_LookingRight = true;
}

void BulletBill::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario)
{
	
	if (m_Pos.x - mario->GetPos().x <= 500.f && mario->GetPos().x - m_Pos.x >= -500.f)
	{
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
	}
}


void BulletBill::CheckHit(Mario* mario)
{
	if (m_DeathAnimation == false)
	{
		Rectf marioRect{ mario->GetBounds() };
		Rectf marioFeetRect{ marioRect.left,marioRect.bottom ,marioRect.width, ((marioRect.height / 4)) };

		Rectf enemyHeadRect{ m_Bounds.left,m_Bounds.bottom + ((m_Bounds.height / 4) * 3),m_Bounds.width, m_Bounds.height / 4 };
		Rectf enemyBodyRect{ m_Bounds.left,m_Bounds.bottom ,m_Bounds.width, ((m_Bounds.height / 4) * 3) };

		if (utils::IsOverlapping(marioFeetRect, enemyHeadRect) && (mario->GetVel().y < 1))
		{
			if (mario->GetState() == Mario::LookingState::leftSpin || mario->GetState() == Mario::LookingState::rightSpin)
			{
				m_HP -= 2;
				m_StompSound->Play(0);
				mario->Bounce(m_Pos.y + m_Bounds.height);
			}
			else
			{
				m_HP -= 1;
				m_StompSound->Play(0);
				mario->Bounce(m_Pos.y + m_Bounds.height);
			}
		}
		else if (utils::IsOverlapping(marioRect, enemyBodyRect))
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
					fireBalls[idx]->SetDead();
				}
			}
		}
	}
}

void BulletBill::Reset()
{
	
		m_Pos = m_OriginalPos;
		m_DeathAnimation = false;
		m_HP = 1;
		m_Velocity = Vector2f(-100.f, 0.f);
}
