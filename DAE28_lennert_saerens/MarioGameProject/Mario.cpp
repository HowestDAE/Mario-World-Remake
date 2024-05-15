#include "pch.h"
#include "Mario.h"
#include "iostream"

Mario::Mario(const Point2f& startingPos, const SoundEffect* hiteffect)
	:m_Pos{startingPos}
	,m_Velocity{}
	,m_WalkingState{WalkingState::none}
	,m_LookingState{ LookingState::right }
	,m_AccTime{}
	,m_FrameNr{1}
	,m_FrameTime{ 0.5f }
	, m_JumpTime{ 0.4f }
	, m_SpinJumpTime{ 0.25f }
	,m_TimeInAir{0}
	, m_Mariostate{ PowerUpState::small }
	, m_CanJump{ 1 }
	,m_IsOnGround{  }
	,m_FrameRect{ Rectf(328, 19, 16, 19) }
	,m_IsAlive{ 1 }
	,m_CoinCount{ 0 }
	,m_Invincible{false}
	,m_InvinTimer{0}
	,m_IFrames{1.f}
	, m_pHitEffect{hiteffect}
{
	m_pSpritesheet = new Texture("mario-spritesheet2.png");
	m_Bounds = Rectf(0, 0, GetCurrFrameRect().width*2, GetCurrFrameRect().height*2);
	m_pJumpEffect = new SoundEffect("Sounds/smw_jump.wav");
	m_pSpinJumpEffect = new SoundEffect("Sounds/smw_spin_jump.wav");
	m_pDeathEffect = new SoundEffect( "Sounds/smw_lost_a_life.wav");
	m_pFireBallTex = new Texture("FireBall.png");
	m_pFireEffect = new SoundEffect("Sounds/smw_fireball.wav");
}


Mario::Mario(Mario&& other)
	:m_AccTime{std::move(other.m_AccTime)}
	,m_Bounds{std::move(other.m_Bounds)}
	,m_CanJump{std::move(other.m_CanJump)}
	,m_FrameNr{std::move(other.m_FrameNr)}
	,m_FrameRect{std::move(other.m_FrameRect)}
	,m_FrameTime{std::move(other.m_FrameTime)}
	,m_IsOnGround{std::move(other.m_IsOnGround)}
	,m_JumpTime{std::move(other.m_JumpTime)}
	,m_CoinCount{std::move(other.m_CoinCount)}
	,m_LookingState{std::move(other.m_LookingState)}
	,m_Mariostate{std::move(other.m_Mariostate)}
	,m_Pos{std::move(other.m_Pos)}
	,m_SpinJumpTime{std::move(other.m_SpinJumpTime)}
	,m_TimeInAir{std::move(other.m_TimeInAir)}
	,m_Velocity{std::move(other.m_Velocity)}
	,m_WalkingState{std::move(other.m_WalkingState)}
	,m_pJumpEffect{std::move(other.m_pJumpEffect)}
	,m_pSpinJumpEffect{std::move(other.m_pJumpEffect)}
	,m_pSpritesheet{std::move(other.m_pSpritesheet)}
	,m_IsAlive{ std::move(other.m_IsAlive)}
	,m_pDeathEffect{std::move(other.m_pDeathEffect)}
	,m_pFireBallTex{ std::move(other.m_pFireBallTex) }
	,m_pFireEffect{std::move(other.m_pFireEffect)}
{
	other.m_pJumpEffect = nullptr;
	other.m_pSpinJumpEffect = nullptr;
	other.m_pSpritesheet = nullptr;
	other.m_pDeathEffect = nullptr;
	other.m_pFireBallTex = nullptr;
	other.m_pFireEffect = nullptr;
}

Mario::~Mario()
{
	delete m_pSpritesheet;
	m_pSpritesheet = nullptr;
	delete m_pJumpEffect;
	m_pJumpEffect = nullptr;
	delete m_pSpinJumpEffect;
	m_pSpinJumpEffect = nullptr;
	delete m_pDeathEffect;
	m_pDeathEffect = nullptr;
	delete m_pFireBallTex;
	m_pFireBallTex = nullptr;
	delete m_pFireEffect;
	m_pFireEffect = nullptr;
	for (int idx{}; idx < m_pFireBalls.size(); ++idx)
	{
		if (m_pFireBalls[idx] != nullptr) delete m_pFireBalls[idx];
		m_pFireBalls[idx] = nullptr;
	}
}


void Mario::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms)
{

	const float gravity{ -7.f };
	const float friction{ -1.4f };

	const Point2f leftTop{ m_Pos.x+1, m_Pos.y + m_Bounds.height };
	const Point2f leftBottom{ m_Pos.x+1, m_Pos.y };
	const Point2f leftMiddle{ m_Pos.x+1, m_Pos.y + m_Bounds.height / 2 };
	const Point2f rightTop{ m_Pos.x + m_Bounds.width-1, m_Pos.y + m_Bounds.height };
	const Point2f rightBottom{ m_Pos.x + m_Bounds.width-1, m_Pos.y };
	const Point2f rightMiddle{ m_Pos.x + m_Bounds.width-1, m_Pos.y + m_Bounds.height / 2 };


	const Point2f lowerLeft{ m_Pos.x, m_Pos.y + m_Bounds.height / 4 };
	const Point2f lowerMiddle{ m_Pos.x + m_Bounds.width/2, m_Pos.y + m_Bounds.height / 4 };
	const Point2f lowerRight{ m_Pos.x + m_Bounds.width, m_Pos.y + m_Bounds.height / 4 };

	utils::HitInfo hitInfo{};

	m_Pos.x += m_Velocity.x * elapsedSec;
	m_Pos.y += m_Velocity.y * elapsedSec;
	if (m_Velocity.x < 1.f && m_Velocity.x >-1.f) m_Velocity.x = 0;
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, GetCurrFrameRect().width * 2, GetCurrFrameRect().height * 2);


	if (m_IsAlive == true)
	{
		for (int idx{ 0 }; idx < landscape.size(); ++idx)
		{

			const std::vector <Point2f>& collissionShape{ landscape[idx] };
			if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
			{
				m_Velocity.y = 0;
				m_Pos.y = hitInfo.intersectPoint.y;
				m_TimeInAir = 0;
				m_CanJump = 1;
				m_IsOnGround = 1;
			}
			else
			{
				m_Velocity.y += gravity;
			}
			if ((utils::Raycast(collissionShape, lowerLeft, lowerMiddle, hitInfo)))
			{
				if (hitInfo.normal.Normalized().x >= 0.1)
				{
					if (m_Velocity.x <= 0)
					{
						m_Velocity.x = 0;
						m_Pos.x = hitInfo.intersectPoint.x;
					}

				}
			}
			if ((utils::Raycast(collissionShape, lowerRight, lowerMiddle, hitInfo)))
			{
				if (hitInfo.normal.Normalized().x <= -0.1)
				{
					if (m_Velocity.x >= 0)
					{
						m_Velocity.x = 0;
						m_Pos.x = hitInfo.intersectPoint.x - m_Bounds.width;
					}
				}
			}
			/*else if ((utils::Raycast(collissionShape, leftTop, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightTop, rightMiddle, hitInfo)) && m_Velocity.y < 0)
			{
				m_Velocity.y = 0;
				m_Pos.y = hitInfo.intersectPoint.y - m_Bounds.height;

			}*/
			/*else if (utils::Raycast(landscape, rightTop, rightBottom, infoRight))
			{
				m_Velocity.y = 0;
				m_Bounds.height = infoLeft.intersectPoint.y;
			}*/
			/*else
			{
				m_Velocity.y += gravity;
			}*/
			if (m_Velocity.y > 5)
			{
				m_IsOnGround = 0;
			}
			if (m_Velocity.y < -100)
			{
				m_IsOnGround = 0;
				m_CanJump = false;
			}
			if (m_Velocity.x > 0 && m_IsOnGround == 1) m_Velocity.x += friction;
			if (m_Velocity.x < 1.f && m_Velocity.x >-1.f) m_Velocity.x = 0;
			if (m_Velocity.x < 0 && m_IsOnGround == 1) m_Velocity.x -= friction;
			if (m_Velocity.x < 1.f && m_Velocity.x >-1.f) m_Velocity.x = 0;



		}
		for (int idx{ 0 }; idx < platforms.size(); ++idx)
		{
			const std::vector <Point2f>& collissionShape{ platforms[idx] };
			if ((utils::Raycast(collissionShape, leftBottom, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightBottom, rightMiddle, hitInfo)) && m_Velocity.y < 0)
			{
				m_Velocity.y = 0;
				m_Pos.y = hitInfo.intersectPoint.y;
				m_TimeInAir = 0;
				m_CanJump = 1;
				m_IsOnGround = 1;
			}
		}
		if (m_Pos.y < 0)
		{
			m_IsAlive = 0;
			m_Velocity.y = 500;
			m_Velocity.x = 0;
			m_pDeathEffect->Play(0);
		}
	}
	
	if (m_IsAlive == false)
	{
		m_Velocity.y += gravity;
		m_FrameTime = 0.05f;
	}
	if (m_Invincible == true)
	{
		m_InvinTimer += elapsedSec;
		if (m_InvinTimer >= m_IFrames)
		{
			m_Invincible = false;
			m_InvinTimer = 0;
		}
	}
	Animate(elapsedSec);
	for (int idx{}; idx < m_pFireBalls.size(); ++idx)
	{
		if (m_pFireBalls[idx] != nullptr)
		{
			m_pFireBalls[idx]->Update(elapsedSec, landscape, platforms);
			if (m_pFireBalls[idx]->GetIsAlive() == false)
			{
				delete m_pFireBalls[idx];
				m_pFireBalls[idx] = nullptr;
			}
			if (m_pFireBalls[idx] != nullptr)
			{
				if (abs(m_pFireBalls[idx]->GetPos().x - m_Pos.x) > 500.f)
				{
					delete m_pFireBalls[idx];
					m_pFireBalls[idx] = nullptr;
				}
			}
		}
	}
	if (m_pFireBalls.size() == 2)
	{
		if (m_pFireBalls[0] == nullptr && m_pFireBalls[1] == nullptr)
		{
			m_pFireBalls.pop_back();
			m_pFireBalls.pop_back();
		}
	}
	if (m_pFireBalls.size() == 1)
	{
		if (m_pFireBalls[0] == nullptr)
		{
			m_pFireBalls.pop_back();

		}
	}
	
}

void Mario::Draw() const
{
	/*glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	m_pTexture->Draw();
	glPopMatrix();*/

	m_pSpritesheet->Draw(m_Bounds, m_FrameRect);
	for (int idx{}; idx < m_pFireBalls.size(); ++idx)
	{
		if (m_pFireBalls[idx] != nullptr) m_pFireBalls[idx]->Draw();
	}
}

void Mario::WalkRight(float elapsedSec, const Uint8* pStates)
{
	if (m_Velocity.x <= 140.f && m_Velocity.x >= 0.f && m_IsOnGround == 1) m_Velocity.x += 1000.f * elapsedSec;
	else if (m_Velocity.x <= 140.f && m_IsOnGround == 0)m_Velocity.x += 2500.f * elapsedSec;
	if (m_LookingState != LookingState::leftSpin && m_LookingState != LookingState::rightSpin)
	{
		m_WalkingState = WalkingState::right;
		m_LookingState = LookingState::right;

		m_AccTime += elapsedSec;
		m_FrameTime = 0.5f;
	}
	if (pStates[SDL_SCANCODE_LSHIFT] && m_IsOnGround == 1)
	{
		if (m_Velocity.x <= 300.f && m_Velocity.x >= 0.f) m_Velocity.x += 1000.f * elapsedSec;
		if (m_Velocity.x >= 300.f) m_Velocity.x = 300.f;
		m_FrameTime = 0.25f;
	}
	if (pStates[SDL_SCANCODE_LSHIFT]) m_JumpTime = 0.4f;
	else m_JumpTime = 0.25f;
}

void Mario::WalkLeft(float elapsedSec, const Uint8* pStates)
{
	/*if (m_Velocity.x >= -140.f && m_Velocity.x <= 0.f && m_CanJump == 1) m_Velocity.x = -140.f;
		else if (m_Velocity.x >= -80.f && m_CanJump == 0)m_Velocity.x = -80.f;
		m_WalkingState = WalkingState::left;
		m_AccTime += elapsedSec;
		if (pStates[SDL_SCANCODE_LSHIFT]&& m_CanJump ==1)
		{
			if (m_Velocity.x >= -300.f) m_Velocity.x = -300.f;
		}*/
	if (m_Velocity.x >= -140.f && m_Velocity.x <= 0.f && m_IsOnGround == 1) m_Velocity.x -= 1000.f * elapsedSec;
	else if (m_Velocity.x >= -140.f && m_IsOnGround == 0)m_Velocity.x -= 2500.f * elapsedSec;
	if (m_LookingState != LookingState::leftSpin && m_LookingState != LookingState::rightSpin)
	{
		m_WalkingState = WalkingState::left;
		m_LookingState = LookingState::left;
		m_AccTime += elapsedSec;
		m_FrameTime = 0.5f;
	}
	if (pStates[SDL_SCANCODE_LSHIFT] && m_IsOnGround == 1)
	{
		if (m_Velocity.x >= -300.f && m_Velocity.x <= 0.f) m_Velocity.x -= 1000.f * elapsedSec;
		if (m_Velocity.x <= -300.f) m_Velocity.x = -300.f;
		m_FrameTime = 0.25f;
	}
	if (pStates[SDL_SCANCODE_LSHIFT]) m_JumpTime = 0.4f;
	else m_JumpTime = 0.25f;
}


void Mario::HandleMovement(float elapsedSec, const Uint8* pStates)
{
	// Aparte functions voor elke movement method want ze worden lang
	if (m_IsAlive == true)
	{
		if (m_IsOnGround == 1)
		{
			m_WalkingState = WalkingState::none;
			if (m_LookingState == LookingState::leftSpin) m_LookingState = LookingState::left;
			if (m_LookingState == LookingState::rightSpin) m_LookingState = LookingState::right;
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			m_WalkingState = WalkingState::down;

		}
		if (pStates[SDL_SCANCODE_UP])
		{
			m_WalkingState = WalkingState::up;
		}
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			WalkRight(elapsedSec, pStates);
		}
		else if (pStates[SDL_SCANCODE_LEFT])
		{
			WalkLeft(elapsedSec, pStates);
		}

		/*if (pStates[SDL_SCANCODE_LSHIFT] && m_Mariostate == PowerUpState::fireflower)
		{
			ShootFireBall();
		}*/

		if (pStates[SDL_SCANCODE_SPACE])
		{
			if (m_IsOnGround == 1)
			{
				m_pJumpEffect->Play(0);
				m_IsOnGround = 0;
			}

			if (m_CanJump == 1)
			{
				m_Velocity.y = 400.f;
				m_TimeInAir += elapsedSec;
			}

		}

		if (pStates[SDL_SCANCODE_LALT])
		{
			if (m_IsOnGround == 1)
			{
				m_pSpinJumpEffect->Play(0);
				m_IsOnGround = 0;
				m_FrameNr = 0;
				if (m_IsOnGround == 0 && m_LookingState == LookingState::left) m_LookingState = LookingState::leftSpin;
				if (m_IsOnGround == 0 && m_LookingState == LookingState::right) m_LookingState = LookingState::rightSpin;
				if (m_pFireBalls.size() < 1 && m_Mariostate == PowerUpState::fireflower)
				{
					m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(-300.f, 0.f), m_pFireBallTex));
					m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(300.f, 0.f), m_pFireBallTex));
				}
			}


			if (m_CanJump == 1)
			{
				m_Velocity.y = 400.f;
				m_TimeInAir += elapsedSec;
			}

			if (m_TimeInAir >= m_SpinJumpTime)
			{
				m_CanJump = 0;
			}
			m_FrameTime = 0.05f;
		}

		/*if (m_AccTime >= m_FrameTime)
		{
			m_AccTime = 0;
			++m_FrameNr;
		}*/
		if (m_IsOnGround == 0) (m_WalkingState = WalkingState::midAir);
		if (m_TimeInAir >= m_JumpTime)
		{
			m_CanJump = 0;
		}
		/*if ((pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_RIGHT] )==0)
		{
			m_WalkingState = WalkingState::none;
		}*/
	}
}



Rectf Mario::GetCurrFrameRect() const
{
	return m_FrameRect;
}

Point2f Mario::GetPos() const
{
	return m_Pos;
}

Rectf Mario::GetBounds() const
{
	return m_Bounds;
}

Vector2f Mario::GetVel() const
{
	return m_Velocity;
}

Mario::PowerUpState Mario::GetPowerUpState() const
{
	return m_Mariostate;
}

Mario::LookingState Mario::GetState() const
{
	return m_LookingState;
}

std::vector<FireBall*> Mario::GetFireBalls() const
{
	return m_pFireBalls;
}

Mario& Mario::operator=(Mario&& other)
{
	if (&other != this)
	{
		m_AccTime = std::move(other.m_AccTime);
		m_Bounds = std::move(other.m_Bounds);
		m_CanJump = std::move(other.m_CanJump);
		m_FrameNr = std::move(other.m_FrameNr);
		m_FrameRect = std::move(other.m_FrameRect);
		m_FrameTime = std::move(other.m_FrameTime);
		m_IsOnGround = std::move(other.m_IsOnGround);
		m_JumpTime = std::move(other.m_JumpTime);
		m_LookingState = std::move(other.m_LookingState);
		m_Mariostate = std::move(other.m_Mariostate);
		m_Pos = std::move(other.m_Pos);
		m_SpinJumpTime = std::move(other.m_SpinJumpTime);
		m_TimeInAir = std::move(other.m_TimeInAir);
		m_Velocity = std::move(other.m_Velocity);
		m_WalkingState = std::move(other.m_WalkingState);
		m_IsAlive= std::move(other.m_IsAlive);
		m_CoinCount = std::move(other.m_CoinCount);

		m_pJumpEffect = std::move(other.m_pJumpEffect);
		m_pSpinJumpEffect = std::move(other.m_pJumpEffect);
		m_pSpritesheet = std::move(other.m_pSpritesheet);
		m_pFireBallTex = std::move(other.m_pFireBallTex);
		m_pDeathEffect = std::move(other.m_pDeathEffect);
		m_pFireEffect = std::move(other.m_pFireEffect);

		other.m_pJumpEffect = nullptr;
		other.m_pSpinJumpEffect = nullptr;
		other.m_pSpritesheet = nullptr;
		other.m_pDeathEffect = nullptr;
		other.m_pFireBallTex = nullptr;
		other.m_pFireEffect = nullptr;

	}
	return *this;
}

void Mario::Animate(float elapsedSec)
{
	m_AccTime += elapsedSec;
	if (m_IsAlive == true)
	{
		if (m_Mariostate == Mario::PowerUpState::small)
		{
			if (m_WalkingState == WalkingState::none && m_LookingState == LookingState::left) m_FrameRect = Rectf(169, 20, 14, 20);
			else if (m_WalkingState == WalkingState::none && m_LookingState == LookingState::right) m_FrameRect = Rectf(209, 20, 14, 20);
			else if (m_WalkingState == WalkingState::left)
			{
				if (m_Velocity.x >= 10) m_FrameRect = Rectf(8, 21, 15, 21);
				else if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 2 == 0) m_FrameRect = Rectf(49, 19, 15, 19);
					else if (m_FrameNr % 2 == 1) m_FrameRect = Rectf(169, 20, 14, 20);
				}

			}
			else if (m_WalkingState == WalkingState::right)
			{
				if (m_Velocity.x <= -10) m_FrameRect = Rectf(369, 21, 15, 21);
				else if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 2 == 1) m_FrameRect = Rectf(328, 19, 15, 19);
					else if (m_FrameNr % 2 == 0) m_FrameRect = Rectf(209, 20, 14, 20);
				}
			}
			else if (m_WalkingState == WalkingState::down && m_LookingState == LookingState::left)
			{
				m_FrameRect = Rectf(89, 57, 15, 14);
			}
			else if (m_WalkingState == WalkingState::down && m_LookingState == LookingState::right)
			{
				m_FrameRect = Rectf(288, 57, 15, 14);
			}
			else if (m_WalkingState == WalkingState::up && m_LookingState == LookingState::left)
			{
				m_FrameRect = Rectf(49, 60, 15, 21);
			}
			else if (m_WalkingState == WalkingState::up && m_LookingState == LookingState::right)
			{
				m_FrameRect = Rectf(328, 60, 15, 21);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::left && m_Velocity.y > 0)
			{
				m_FrameRect = Rectf(168, 61, 16, 22);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::right && m_Velocity.y > 0)
			{
				m_FrameRect = Rectf(208, 61, 16, 22);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::left && m_Velocity.y <= 0)
			{
				m_FrameRect = Rectf(128, 60, 16, 20);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::right && m_Velocity.y <= 0)
			{
				m_FrameRect = Rectf(247, 60, 16, 20);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::leftSpin)
			{
				if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(289, 20, 14, 20);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(169, 20, 14, 20);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(249, 20, 14, 20);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(209, 20, 14, 20);
				}
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::rightSpin)
			{
				if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(289, 20, 14, 20);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(169, 20, 14, 20);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(249, 20, 14, 20);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(209, 20, 14, 20);
				}
			}

			
		}





		else if (m_Mariostate == Mario::PowerUpState::big)
		{
			if (m_WalkingState == WalkingState::none && m_LookingState == LookingState::left) m_FrameRect = Rectf(169, 104, 15, 28);
			else if (m_WalkingState == WalkingState::none && m_LookingState == LookingState::right) m_FrameRect = Rectf(208, 104, 15, 28);
			else if (m_WalkingState == WalkingState::left)
			{
				if (m_Velocity.x >= 10) m_FrameRect = Rectf(8, 144, 16, 29);
				else if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(48, 103, 16, 27);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(8, 104, 16, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(169, 104, 15, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(8, 104, 16, 28);
				}

			}
			else if (m_WalkingState == WalkingState::right)
			{
				if (m_Velocity.x <= -10) m_FrameRect = Rectf(368, 144, 16, 29);
				else if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(328, 103, 16, 27);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(368, 104, 16, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(208, 104, 15, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(368, 104, 16, 28);
				}
			}
			else if (m_WalkingState == WalkingState::down && m_LookingState == LookingState::left)
			{
				m_FrameRect = Rectf(88, 136, 16, 15);
			}
			else if (m_WalkingState == WalkingState::down && m_LookingState == LookingState::right)
			{
				m_FrameRect = Rectf(288, 136, 16, 15);
			}
			else if (m_WalkingState == WalkingState::up && m_LookingState == LookingState::left)
			{
				m_FrameRect = Rectf(130, 223, 15, 27);
			}
			else if (m_WalkingState == WalkingState::up && m_LookingState == LookingState::right)
			{
				m_FrameRect = Rectf(247, 223, 15, 27);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::left && m_Velocity.y > 0)
			{
				m_FrameRect = Rectf(168, 145, 16, 31);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::right && m_Velocity.y > 0)
			{
				m_FrameRect = Rectf(208, 145, 16, 31);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::left && m_Velocity.y <= 0)
			{
				m_FrameRect = Rectf(128, 144, 16, 29);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::right && m_Velocity.y <= 0)
			{
				m_FrameRect = Rectf(248, 144, 16, 29);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::leftSpin)
			{
				if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(88, 104, 16, 28);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(208, 104, 15, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(248, 104, 16, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(169, 104, 15, 28);
				}
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::rightSpin)
			{
				if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(248, 104, 16, 28);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(169, 104, 15, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(88, 104, 16, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(208, 104, 15, 28);
				}
			}
		}
		
		else if (m_Mariostate == Mario::PowerUpState::fireflower)
		{
			if (m_WalkingState == WalkingState::none && m_LookingState == LookingState::left) m_FrameRect = Rectf(169, 260, 15, 28);
			else if (m_WalkingState == WalkingState::none && m_LookingState == LookingState::right) m_FrameRect = Rectf(208, 260, 15, 28);
			else if (m_WalkingState == WalkingState::left)
			{
				if (m_Velocity.x >= 10) m_FrameRect = Rectf(8, 300, 16, 29);
				else if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(48, 259, 16, 27);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(8, 260, 16, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(169, 260, 15, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(8, 260, 16, 28);
				}

			}
			else if (m_WalkingState == WalkingState::right)
			{
				if (m_Velocity.x <= -10) m_FrameRect = Rectf(368, 300, 16, 29);
				else if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(328, 259, 16, 27);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(368, 260, 16, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(208, 260, 15, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(368, 260, 16, 28);
				}
			}
			else if (m_WalkingState == WalkingState::down && m_LookingState == LookingState::left)
			{
				m_FrameRect = Rectf(88, 293, 16, 15);
			}
			else if (m_WalkingState == WalkingState::down && m_LookingState == LookingState::right)
			{
				m_FrameRect = Rectf(288, 293, 16, 15);
			}
			else if (m_WalkingState == WalkingState::up && m_LookingState == LookingState::left)
			{
				m_FrameRect = Rectf(50, 299, 15, 27);
			}
			else if (m_WalkingState == WalkingState::up && m_LookingState == LookingState::right)
			{
				m_FrameRect = Rectf(327, 299, 15, 27);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::left && m_Velocity.y > 0)
			{
				m_FrameRect = Rectf(168, 301, 16, 31);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::right && m_Velocity.y > 0)
			{
				m_FrameRect = Rectf(208, 301, 16, 31);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::left && m_Velocity.y <= 0)
			{
				m_FrameRect = Rectf(128, 300, 16, 29);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::right && m_Velocity.y <= 0)
			{
				m_FrameRect = Rectf(248, 300, 16, 31);
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::leftSpin)
			{
				if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(88, 260, 16, 28);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(208, 260, 15, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(248, 260, 16, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(169, 260, 15, 28);
				}
			}
			else if (m_WalkingState == WalkingState::midAir && m_LookingState == LookingState::rightSpin)
			{
				if (m_AccTime >= m_FrameTime)
				{
					++m_FrameNr;
					m_AccTime = 0;
					if (m_FrameNr % 4 == 0) m_FrameRect = Rectf(248, 260, 16, 28);
					else if (m_FrameNr % 4 == 1) m_FrameRect = Rectf(169, 260, 15, 28);
					else if (m_FrameNr % 4 == 2) m_FrameRect = Rectf(88, 260, 16, 28);
					else if (m_FrameNr % 4 == 3) m_FrameRect = Rectf(208, 260, 15, 28);
				}
			}
		}
	}
	else
	{
		if (m_AccTime >= m_FrameTime)
		{
			++m_FrameNr;
			m_AccTime = 0;
			if (m_FrameNr % 2 == 0) m_FrameRect = Rectf(8, 62, 16, 24);
			else if (m_FrameNr % 2 == 1) m_FrameRect = Rectf(368, 62, 16, 24);
		}
	}
}

void Mario::Grow(const PowerUp::PowerUpType& type)
{
	if (type == PowerUp::PowerUpType::Mushroom && m_Mariostate == PowerUpState::small) m_Mariostate = PowerUpState::big;
	else if (type == PowerUp::PowerUpType::Flower && (m_Mariostate == PowerUpState::small || m_Mariostate == PowerUpState::big)) m_Mariostate = PowerUpState::fireflower;
	
}

void Mario::ShootFireBall()
{
	if (m_pFireBalls.size() < 2 && m_Mariostate == PowerUpState::fireflower)
	{
		m_pFireEffect->Play(0);
		if (m_LookingState == LookingState::left) m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(-300.f, 0.f), m_pFireBallTex));
		if (m_LookingState == LookingState::right)m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(300.f, 0.f), m_pFireBallTex));
	}
}

void Mario::AddCoin()
{
	++m_CoinCount;
}

bool Mario::GetIsAlive() const
{
	return m_IsAlive;
}

void Mario::TakeDamage()
{
	if (m_Invincible == false)
	{
		if (m_Mariostate == PowerUpState::fireflower)
		{
			m_Mariostate = PowerUpState::big;
			m_Invincible = true;
			m_pHitEffect->Play(0);
		}
		else if (m_Mariostate == PowerUpState::big)
		{
			m_Mariostate = PowerUpState::small;
			m_Invincible = true;
			m_pHitEffect->Play(0);

		}
		else if (m_Mariostate == PowerUpState::small)
		{
			m_IsAlive = false;
			m_Velocity.y = 500;
			m_Velocity.x = 0;
			m_pDeathEffect->Play(0);

		}
	}
}

void Mario::Bounce(float ypos)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_SPACE])
	{
		m_CanJump = true;
		m_TimeInAir = 0;
		m_Pos.y = ypos+7;
	}
	else
	{
		m_Velocity.y = 400.f;
		m_Pos.y = ypos+7;
	}
}

void Mario::OnKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:
	case SDLK_LALT:
		m_CanJump = false;
		break;
	}
}

void Mario::OnKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_LSHIFT:
		ShootFireBall();
		break;
	}
}
