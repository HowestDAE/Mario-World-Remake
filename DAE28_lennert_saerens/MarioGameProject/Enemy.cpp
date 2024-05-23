#include "pch.h"
#include "Enemy.h"
#include "Mario.h"
#include "FireBall.h"

Enemy::Enemy(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:m_IsAlive{true}
	,m_Velocity{-30.f,0}
	,m_Pos{pos}
	,m_DeathAnimation{false}
	,m_Deathtimer{0}
	,m_FrameNr{0}
	,m_FrameTime{0.3f}
	,m_ElapsedSec{0}
	,m_StompSound{ sound }
	,m_HP{ 2 }
	,m_LookingRight{ false }
	,m_OriginalPos{pos}
{
	m_pTexture = tex;
	m_SrcRect = Rectf(4, 94, 19, 32);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width*2, m_SrcRect.height*2);
}

void Enemy::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario)
{
	if (m_Pos.x - mario->GetPos().x <= 500.f && m_Pos.x - mario->GetPos().x>= -500.f)
	{
		if (m_HP <= 0)
		{
			m_DeathAnimation = true;
		}

		if (m_DeathAnimation == false)
		{
			m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);

			const float gravity{ -21.f };

			const Point2f leftTop{ m_Pos.x + 1, m_Pos.y + m_Bounds.height };
			const Point2f leftBottom{ m_Pos.x + 1, m_Pos.y };
			const Point2f leftMiddle{ m_Pos.x + 1, m_Pos.y + m_Bounds.height / 2 };
			const Point2f rightTop{ m_Pos.x + m_Bounds.width - 1, m_Pos.y + m_Bounds.height };
			const Point2f rightBottom{ m_Pos.x + m_Bounds.width - 1, m_Pos.y };
			const Point2f rightMiddle{ m_Pos.x + m_Bounds.width - 1, m_Pos.y + m_Bounds.height / 2 };


			const Point2f lowerLeft{ m_Pos.x, m_Pos.y + m_Bounds.height / 4 };
			const Point2f lowerMiddle{ m_Pos.x + m_Bounds.width / 2, m_Pos.y + m_Bounds.height / 4 };
			const Point2f lowerRight{ m_Pos.x + m_Bounds.width, m_Pos.y + m_Bounds.height / 4 };

			utils::HitInfo hitInfo{};

			m_Pos.x += m_Velocity.x * elapsedSec;
			m_Pos.y += m_Velocity.y * elapsedSec;

			m_Velocity.y += gravity;
			for (int idx{ 0 }; idx < landscape.size(); ++idx)
			{

				const std::vector <Point2f>& collissionShape{ landscape[idx] };
				if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
				{
					m_Velocity.y = 0;
					m_Pos.y = hitInfo.intersectPoint.y;
				}
				if ((utils::Raycast(collissionShape, lowerLeft, lowerMiddle, hitInfo)))
				{
					if (hitInfo.normal.Normalized().x >= 0.1)
					{
						if (m_Velocity.x <= 0)
						{
							m_Velocity.x = -m_Velocity.x;
							m_Pos.x = hitInfo.intersectPoint.x;
							m_LookingRight = true;
						}

					}
				}
				if ((utils::Raycast(collissionShape, lowerRight, lowerMiddle, hitInfo)))
				{
					if (hitInfo.normal.Normalized().x <= -0.1)
					{
						if (m_Velocity.x >= 0)
						{
							m_Velocity.x = -m_Velocity.x;
							m_Pos.x = hitInfo.intersectPoint.x - m_Bounds.width;
							m_LookingRight = false;
						}
					}
				}



			}
			for (int idx{ 0 }; idx < platforms.size(); ++idx)
			{
				const std::vector <Point2f>& collissionShape{ platforms[idx] };
				if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
				{
					m_Velocity.y = 0;
					m_Pos.y = hitInfo.intersectPoint.y;
				}
			}
			m_Pos.x += m_Velocity.x * elapsedSec;


		}
	}
	
	Animate(elapsedSec);
}

void Enemy::Draw() const
{
	if (m_IsAlive == true)
	{
		Point2f centerPos{ m_Pos.x + m_Bounds.width / 2, m_Pos.y + m_Bounds.height / 2 };
		glPushMatrix();
		if (m_LookingRight)
		{
			glTranslatef(centerPos.x, centerPos.y, 0);
			glRotatef(180.f, 0.f, 1.f, 0.f);
			glTranslatef(-centerPos.x, -centerPos.y, 0);
		}
		m_pTexture->Draw(m_Bounds, m_SrcRect);
		/*utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
		utils::DrawRect(m_Bounds);*/
		glPopMatrix();
	}
}

void Enemy::Animate(float elapsedSec)
{
	if (m_DeathAnimation == false)
	{
		m_ElapsedSec += elapsedSec;
		if (m_ElapsedSec >= m_FrameTime)
		{
			m_ElapsedSec = 0;
			++m_FrameNr;
			if (m_FrameNr >= 2)
			{
				m_FrameNr = 0;
			}
		}

		if (m_HP == 2)
		{
			if (m_FrameNr == 0)
			{
				m_SrcRect = Rectf(4, 94, 19, 32);
			}
			else if (m_FrameNr == 1)
			{
				m_SrcRect = Rectf(26, 94, 20, 31);
			}
		}
		else if (m_HP = 1)
		{
			if (m_FrameNr == 0)
			{
				m_SrcRect = Rectf(50, 94, 16, 16);
			}
			else if (m_FrameNr == 1)
			{
				m_SrcRect = Rectf(69, 94, 16, 15);
			}
		}
	}
	else if (m_DeathAnimation == true)
	{
		m_SrcRect = Rectf(90, 94, 16, 8);
		m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
		m_Deathtimer += elapsedSec;
		if (m_Deathtimer >= 3.f)
		{
			m_IsAlive = false;
		}
	}
}

void Enemy::CheckHit(Mario* mario)
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
					m_HP -= 2;
					m_StompSound->Play(0);
					fireBalls[idx]->SetDead();
				}
			}
		}

	}
}

void Enemy::Reset()
{
	m_IsAlive = true;
	m_Velocity = Vector2f( - 30.f, 0);
	m_Pos = m_OriginalPos;
	m_DeathAnimation = false ;
	m_Deathtimer = 0 ;
	m_FrameNr= 0;
	m_FrameTime= 0.3f ;
	m_ElapsedSec= 0 ;
	m_HP= 2 ;
	m_LookingRight= false;
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
}

Rectf Enemy::GetBounds() const
{
	return m_Bounds;
}
