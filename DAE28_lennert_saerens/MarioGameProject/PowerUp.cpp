#include "pch.h"
#include "PowerUp.h"
#include "Mario.h"
#include "utils.h"

PowerUp::PowerUp(const Mario& mario, const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:m_Pos{pos}
	,m_Velocity{Vector2f(0,0)}
	,m_pSound{sound}
	,m_IsCollected{ false }
{
	m_pTexture = tex;
	if (mario.GetPowerUpState() == Mario::PowerUpState::small) m_Type = PowerUpType::Mushroom;
	else m_Type = PowerUpType::Flower;
	if (m_Type == PowerUpType::Mushroom)
	{
		m_SrcRect = Rectf(69, 17, 16, 16);
		m_Velocity = Vector2f(30.f, 0.f);
	}
	else m_SrcRect = Rectf(89, 17, 16, 16);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width, m_SrcRect.height);
}

PowerUp::PowerUp(const PowerUpType& powerup, const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:m_Pos{ pos }
	, m_Velocity{ Vector2f(0,0) }
	, m_pSound{ sound }
	, m_IsCollected{ false }

{
	m_pTexture = tex;
	m_Type = powerup;
	if (m_Type == PowerUpType::Mushroom)
	{
		m_SrcRect = Rectf(69, 17, 16, 16);
		m_Velocity = Vector2f(100.f, 0.f);
	}
	else m_SrcRect = Rectf(89, 17, 16, 16);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width, m_SrcRect.height);

}

void PowerUp::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms)
{
	if (m_IsCollected == 0)
	{
		m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width*2, m_SrcRect.height*2);


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
		if (m_Velocity.x < 1.f && m_Velocity.x >-1.f) m_Velocity.x = 0;


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
						m_Velocity.x =  -m_Velocity.x;
						m_Pos.x = hitInfo.intersectPoint.x;
					}

				}
			}
			if ((utils::Raycast(collissionShape, lowerRight, lowerMiddle, hitInfo)))
			{
				if (hitInfo.normal.Normalized().x <= 0.1)
				{
					if (m_Velocity.x >= 0)
					{
						m_Velocity.x = -m_Velocity.x;
						m_Pos.x = hitInfo.intersectPoint.x - m_Bounds.width;
					}
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
			}
		}
		m_Pos.x += m_Velocity.x * elapsedSec;




		//Animate(elapsedSec);
	}
}

void PowerUp::Draw() const
{
	if (m_IsCollected==false) m_pTexture->Draw(m_Bounds, m_SrcRect);
}

bool PowerUp::Collect(const Mario* mario)
{
	if (utils::IsOverlapping(Rectf{ m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2 }, mario->GetBounds()) && m_IsCollected == false)
	{
		m_IsCollected = true;
		m_pSound->Play(0);
		return true;
	}
	return false;
}

PowerUp::PowerUpType PowerUp::GetPowerUpType()
{
	return m_Type;
}

//PowerUp::PowerUp(PowerUp&& other)
//{
//}
//
//PowerUp::~PowerUp()
//{
//}
//
//PowerUp& PowerUp::operator=(PowerUp&& other)
//{
//	
//}


