#include "pch.h"
#include "Chuck.h"
#include "Mario.h"

Chuck::Chuck(const Point2f& pos, const Texture* tex, const SoundEffect* sound, const SoundEffect* clapSound) noexcept
	:Enemy::Enemy(pos, tex, sound)
	, m_CanJump{ true }
	,m_JumpCooldown{0.f}
	,m_IsInAir{false}
	,m_InitJump{false}
	,m_pClapSound{clapSound}
{
	m_SrcRect = Rectf(36, 259, 24, 19);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
	m_Velocity = Vector2f(0.f, 0.f);
}

void Chuck::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, Mario* mario) noexcept
{
	if (m_Pos.x - mario->GetPos().x <= 500.f)
	{
		const float gravity{ -6.f };
		m_Pos.x += m_Velocity.x * elapsedSec;
		m_Pos.y += m_Velocity.y * elapsedSec;

		m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);

		if (m_HP <= 0 && m_DeathAnimation == false)
		{
			m_DeathAnimation = true;
			mario->AddPoints(200);

		}
		if (m_DeathAnimation == true)
		{
			m_Velocity = Vector2f(-30.f, -200.f);
		}
		if (m_DeathAnimation == false)
		{
			

			
				m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);


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
						m_CanJump = true;
						m_IsInAir = false;
						m_Velocity.y = 0;
						m_Pos.y = hitInfo.intersectPoint.y;
						m_GroundPos = m_Pos;
					}



				}
				for (int idx{ 0 }; idx < platforms.size(); ++idx)
				{
					const std::vector <Point2f>& collissionShape{ platforms[idx] };
					if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
					{
						m_CanJump = true;
						m_IsInAir = false;
						m_Velocity.y = 0;
						m_Pos.y = hitInfo.intersectPoint.y;
						m_GroundPos = m_Pos;
					}
				}
				m_Velocity.y += gravity;	
				const Uint8* pStates = SDL_GetKeyboardState(nullptr);
				if ((pStates[SDL_SCANCODE_SPACE] || pStates[SDL_SCANCODE_LALT]) && m_CanJump && m_JumpCooldown <= 0.f && m_InitJump == false)
				{
					m_InitJump = true;
					m_JumpTime = 0.f;
				}
				if (m_InitJump)
				{
					m_JumpTime += elapsedSec;
				}
				if (m_InitJump && m_JumpTime >= 0.2f && m_IsInAir==false)
				{
					m_Pos.y = m_GroundPos.y + 1;
					m_Velocity.y = 400.f;
					m_ElapsedSec = 0;
					m_JumpCooldown = 2;
					m_IsInAir = true;
					m_CanJump = false;
					m_InitJump = false;
				}
				if (m_JumpCooldown > 0.f)
				{
					m_JumpCooldown -= elapsedSec;
				}
				/*if (m_Pos.y >= (m_GroundPos.y + 300.f) && m_Velocity.y > 0)
				{
					m_Velocity.y = -75;
				}*/
		}
	}
	Animate(elapsedSec, mario);
}

void Chuck::Reset() noexcept
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
	m_GroundPos = m_OriginalPos;
	m_CanJump = true;
	m_IsInAir = false;
	m_InitJump = false;
	m_JumpCooldown = 0;
	m_Velocity = Vector2f(0, 0);

}



void Chuck::Animate(float elapsedSec, const Mario* mario) noexcept
{
	if (mario->GetPos().x > m_Pos.x)
	{
		m_LookingRight = true;
	}
	else
	{
		m_LookingRight = false;
	}
	
		if (m_CanJump)
		{
			m_SrcRect = Rectf(36, 259, 24, 19);
		}
		if (m_InitJump)
		{
			m_SrcRect = Rectf(64, 259, 24, 23);
		}
		if (m_IsInAir && m_Velocity.y > -50.f)
		{
			m_SrcRect = Rectf(7, 291, 28, 27);
		}
		if (m_IsInAir &&  m_Velocity.y < 50.f)
		{
			m_SrcRect = Rectf(38, 292, 30, 26);
		}
		if (m_IsInAir && m_Velocity.y > -3.f && m_Velocity.y < 3.f)
		{
			m_pClapSound->Play(0);
		}
	
}
