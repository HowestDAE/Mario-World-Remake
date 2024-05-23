#include "pch.h"
#include "Koopa.h"
#include "Mario.h"

Koopa::Koopa(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:Enemy::Enemy(pos,tex,sound)
{
	m_HP = 1;
	m_SrcRect = Rectf(129, 51, 16, 15);
	m_LookingRight = true;
}

void Koopa::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario)
{
	if (m_Pos.x - mario->GetPos().x <= 500.f && mario->GetPos().x - m_Pos.x >= -500.f)
	{
		if (m_HP <= 0)
		{
			m_DeathAnimation = true;
		}

		if (m_DeathAnimation == false)
		{
			m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);

			const float gravity{ -7.f };

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


			for (int idx{ 0 }; idx < landscape.size(); ++idx)
			{

				const std::vector <Point2f>& collissionShape{ landscape[idx] };
				if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
				{
					m_Velocity.y = 0;
					m_Pos.y = hitInfo.intersectPoint.y;
					if (m_Velocity.x <= 0.f)
					{
						m_Velocity.x += 0.3f;
					}
				}
				else
				{
					m_Velocity.y += gravity;
				}



			}
			for (int idx{ 0 }; idx < platforms.size(); ++idx)
			{
				const std::vector <Point2f>& collissionShape{ platforms[idx] };
				if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
				{
					m_Velocity.y = 0;
					m_Pos.y = hitInfo.intersectPoint.y;
					m_Velocity.x -= 20.f;
				}
			}
			m_Pos.x += m_Velocity.x * elapsedSec;


		}
		else if (m_DeathAnimation == true)
		{
			m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height);
			m_Deathtimer += elapsedSec;
			if (m_Deathtimer >= 3.f)
			{
				m_IsAlive = false;
			} 
		}
	}
	

	Animate(elapsedSec);
}

void Koopa::Reset()
{
	m_IsAlive = true;
	m_Velocity = Vector2f(0, 0);
	m_Pos = m_OriginalPos;
	m_DeathAnimation = false;
	m_Deathtimer = 0;
	m_FrameNr = 0;
	m_FrameTime = 0.3f;
	m_ElapsedSec = 0;
	m_HP = 1;
	m_LookingRight = true;
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
}

void Koopa::Animate(float elapsedSec)
{
	m_SrcRect = Rectf(129, 51, 16, 15);
}
