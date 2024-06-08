#include "pch.h"
#include "FireBall.h"

FireBall::FireBall(const Point2f& pos, const Vector2f& velocity, const Texture* tex) noexcept
	:m_Pos{pos}
	,m_Velocity{velocity}
	,m_pTexture{tex}
	,m_SrcRect{ 0,0,8,8 }
	,m_ElapsedSec{}
	,m_FrameTime{0.05f}
	,m_FrameNr{ 0 }
{
}

void FireBall::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks) noexcept
{
	if (m_IsAlive)
	{
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
		m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
		m_ElapsedSec += elapsedSec;

		m_Velocity.y += gravity;


		for (int idx{ 0 }; idx < landscape.size(); ++idx)
		{ 

			const std::vector <Point2f>& collissionShape{ landscape[idx] };
			if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)))
			{
				m_Velocity.y = 350.f;
				m_Pos.y = hitInfo.intersectPoint.y + 1;
			}
			if ((utils::Raycast(collissionShape, lowerLeft, lowerMiddle, hitInfo)))
			{
				if (hitInfo.normal.Normalized().x >= 0.9)
				{
					m_IsAlive = false;

				}
			}
			if ((utils::Raycast(collissionShape, lowerRight, lowerMiddle, hitInfo)))
			{
				if (hitInfo.normal.Normalized().x <= -0.9)
				{
					m_IsAlive = false;
				}
			}			
		}
		for (int idx{ 0 }; idx < platforms.size(); ++idx)
		{
			const std::vector <Point2f>& collissionShape{ platforms[idx] };
			if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
			{
				m_Velocity.y = 350.f;
				m_Pos.y = hitInfo.intersectPoint.y+1;
			}
		}
		if (m_ElapsedSec >= m_FrameTime)
		{
			++m_FrameNr;
			m_ElapsedSec = 0;
			if (m_FrameNr % 4 == 0) m_SrcRect = Rectf(0, 0, 8, 8);
			if (m_FrameNr % 4 == 1) m_SrcRect = Rectf(9, 0, 8, 8);
			if (m_FrameNr % 4 == 2) m_SrcRect = Rectf(18, 0, 8, 8);
			if (m_FrameNr % 4 == 3) m_SrcRect = Rectf(27, 0, 8, 8);
			if (m_FrameNr >= 4) m_FrameNr = 0;
		}
	}
	for (int idx{}; idx < blocks.size(); ++idx)
	{
		if (!blocks[idx]->GetIsBroken())
		{
			Rectf BlockRect{ blocks[idx]->GetBounds() };

			Rectf topRect{ BlockRect.left + 5,BlockRect.bottom + ((BlockRect.height / 8) * 7),BlockRect.width - 10, BlockRect.height / 8};
			Rectf leftRect{ BlockRect.left,BlockRect.bottom + 5,(BlockRect.width / 8) * 7 , BlockRect.height - 10 };
			Rectf rightRect{ BlockRect.left + (BlockRect.width / 8) * 7  ,BlockRect.bottom + 5 ,(BlockRect.width / 8) * 7, BlockRect.height - 10 };

			if (utils::IsOverlapping(m_Bounds, topRect))
			{
				m_Velocity.y = 350.f;
				m_Pos.y = BlockRect.bottom + BlockRect.height + 1;
			}
			else  if (utils::IsOverlapping(m_Bounds, leftRect) && m_Velocity.x > 0)
			{
				m_IsAlive = false;

			}
			else  if (utils::IsOverlapping(m_Bounds, rightRect) && m_Velocity.x < 0)
			{
				m_IsAlive = false;
			}
		}
	}
}

void FireBall::Draw() const noexcept
{
	if (m_IsAlive) m_pTexture->Draw(m_Bounds, m_SrcRect);
}

void FireBall::SetDead() noexcept
{
	m_IsAlive = false;
}

Point2f FireBall::GetPos() const noexcept
{ 
	return m_Pos;
}

bool FireBall::GetIsAlive() const noexcept
{
	return m_IsAlive;
}

Rectf FireBall::GetBounds() const noexcept
{
	return m_Bounds;
}
