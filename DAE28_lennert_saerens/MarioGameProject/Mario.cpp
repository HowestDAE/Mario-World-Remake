#include "pch.h"
#include "Mario.h"
#include "iostream"
#include "FireBall.h"
#include <sstream>
#include <iomanip>


Mario::Mario(const Point2f& startingPos) noexcept
	:m_Pos{startingPos}
	,m_Velocity{}
	,m_WalkingState{WalkingState::none}
	,m_LookingState{ LookingState::right }
	,m_AccTime{}
	,m_FrameNr{1}
	,m_FrameTime{ 0.22f }
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
	,m_CheckpointHit{false}
	,m_FinishHit{false}
	,m_WinTimer{0}
	,m_LevelClear{false}
	,m_CanMove{true}
	,m_LivesCount{5}
	,m_PointCount{0}
	/*,m_pLivesTex{}
	,m_pLivesAmountTex{}
	,m_pCoinAmountTex{}
	,m_pCoinStringTex{}
	,m_pPointsStringTex{}*/
{
	m_pSpritesheet = new Texture("mario-spritesheet2.png");
	m_Bounds = Rectf(400, 110, GetCurrFrameRect().width*2, GetCurrFrameRect().height*2);
	m_pJumpEffect = new SoundEffect("Sounds/smw_jump.wav");
	m_pSpinJumpEffect = new SoundEffect("Sounds/smw_spin_jump.wav");
	m_pDeathEffect = new SoundEffect( "Sounds/smw_lost_a_life.wav");
	m_pFireBallTex = new Texture("FireBall.png");
	m_pFireEffect = new SoundEffect("Sounds/smw_fireball.wav");
	m_pHitEffect = new SoundEffect("Sounds/smw_pipeandhit.wav");
	m_pWinEffect = new SoundEffect("Sounds/smw_course_clear.wav");
}


Mario::Mario(Mario&& other) noexcept
	: m_Pos{other.m_Pos }
	, m_Velocity{other.m_Velocity }
	, m_pSpritesheet{other.m_pSpritesheet }
	, m_pFireBallTex{other.m_pFireBallTex }
	, m_Bounds{other.m_Bounds }
	, m_Mariostate{other.m_Mariostate }
	, m_WalkingState{other.m_WalkingState }
	, m_LookingState{other.m_LookingState }
	, m_pJumpEffect{other.m_pJumpEffect }
	, m_pSpinJumpEffect{other.m_pSpinJumpEffect }
	, m_pDeathEffect{other.m_pDeathEffect }
	, m_pFireEffect{other.m_pFireEffect }
	, m_pWinEffect{other.m_pWinEffect }
	, m_pHitEffect{other.m_pHitEffect }
	, m_AccTime{other.m_AccTime }
	, m_FrameTime{other.m_FrameTime }
	, m_JumpTime{other.m_JumpTime }
	, m_SpinJumpTime{other.m_SpinJumpTime }
	, m_TimeInAir{other.m_TimeInAir }
	, m_FrameNr{other.m_FrameNr }
	, m_CoinCount{other.m_CoinCount }
	, m_PointCount{other.m_PointCount }
	, m_LivesCount{other.m_LivesCount }
	, m_CanJump{other.m_CanJump }
	, m_IsOnGround{other.m_IsOnGround }
	, m_IsAlive{other.m_IsAlive }
	, m_Invincible{other.m_Invincible }
	, m_CheckpointHit{other.m_CheckpointHit }
	, m_FinishHit{other.m_FinishHit }
	, m_LevelClear{other.m_LevelClear }
	, m_CanMove{other.m_CanMove }
	, m_InvinTimer{other.m_InvinTimer }
	, m_WinTimer{other.m_WinTimer }
	, m_IFrames{other.m_IFrames }
	, m_FrameRect{other.m_FrameRect }
	, m_pFireBalls{other.m_pFireBalls }


{
	other.m_pJumpEffect = nullptr;
	other.m_pSpinJumpEffect = nullptr;
	other.m_pSpritesheet = nullptr;
	other.m_pDeathEffect = nullptr;
	other.m_pFireBallTex = nullptr;
	other.m_pFireEffect = nullptr;
	other.m_pWinEffect = nullptr;
	other.m_pHitEffect = nullptr;
	for (int idx{}; idx < m_pFireBalls.size(); ++idx)
	{
		m_pFireBalls[idx] = nullptr;
	}
}
 
Mario::~Mario() noexcept
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
	delete m_pHitEffect;
	m_pHitEffect = nullptr;
	delete m_pWinEffect;
	m_pWinEffect = nullptr;
	for (int idx{}; idx < m_pFireBalls.size(); ++idx)
	{
		if (m_pFireBalls[idx] != nullptr) delete m_pFireBalls[idx];
		m_pFireBalls[idx] = nullptr;
	}
	/*m_pSpritesheet = new Texture("mario-spritesheet2.png");
	m_Bounds = Rectf(0, 0, GetCurrFrameRect().width * 2, GetCurrFrameRect().height * 2);
	m_pJumpEffect = new SoundEffect("Sounds/smw_jump.wav");
	m_pSpinJumpEffect = new SoundEffect("Sounds/smw_spin_jump.wav");
	m_pDeathEffect = new SoundEffect("Sounds/smw_lost_a_life.wav");
	m_pFireBallTex = new Texture("FireBall.png");
	m_pFireEffect = new SoundEffect("Sounds/smw_fireball.wav");
	m_pHitEffect = new SoundEffect("Sounds/smw_pipeandhit.wav");*/
}


void Mario::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks) noexcept
{

	const float gravity{ -21.f };
	const float friction{ -600.f };

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
		m_Velocity.y += gravity;

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
			if ((utils::Raycast(collissionShape, leftTop, leftMiddle, hitInfo) || utils::Raycast(collissionShape, rightTop, rightMiddle, hitInfo)) && m_Velocity.y > 0)
			{
				m_Velocity.y = 0;
				m_Pos.y = hitInfo.intersectPoint.y - m_Bounds.height;
				m_CanJump = false;
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
			m_IsAlive = false;
			m_Velocity.y = 500;
			m_Velocity.x = 0;
			m_pDeathEffect->Play(0);
		}
	}
	if (m_Velocity.x > 0 && m_IsOnGround == 1) m_Velocity.x += friction * elapsedSec;
	if (m_Velocity.x > -2.f && m_Velocity.x < 2.f) m_Velocity.x = 0;
	if (m_Velocity.x < 0 && m_IsOnGround == 1)m_Velocity.x -= friction * elapsedSec;
	if (m_Velocity.x > -2.f && m_Velocity.x < 2.f) m_Velocity.x = 0;

	if (m_IsAlive == false)
	{
		m_Velocity.y += gravity/3;
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
			m_pFireBalls[idx]->Update(elapsedSec, landscape, platforms, blocks);
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
	if (m_FinishHit)
	{
		if (m_Pos.x < 4990 * 2)
		{
			if (m_Velocity.x <= 140.f && m_Velocity.x >= -0.5f && m_IsOnGround == 1) m_Velocity.x += 1000.f * elapsedSec;
			m_WalkingState = WalkingState::right;
		}
		else if (m_Pos.x > 4990 * 2 && m_WinTimer < 7.f)
		{
			m_WinTimer += elapsedSec;
			m_WalkingState = WalkingState::none;

		}
		else if (m_Pos.x > 4990 * 2 && m_WinTimer > 7.f)
		{
			if (m_Velocity.x <= 140.f && m_Velocity.x >= -0.5f && m_IsOnGround == 1) m_Velocity.x += 1000.f * elapsedSec;
			m_WalkingState = WalkingState::right;
		}
		if (m_Pos.x > 5119 * 2)
		{
			ResetStart();
			m_LevelClear = true;
		}
		
	}
	/*if (m_LivesCount < 0)
	{
		ResetStart();
		m_LevelClear = true;
	}*/
}

void Mario::Draw() const noexcept
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

void Mario::DrawUI(const Rectf& vieuwPort) const noexcept
{
	std::string livesSting{ "Mario" };
	std::string livesStingAmount = 'x' + std::to_string(m_LivesCount);
	Texture* livesStringTex = new Texture(livesSting, "typeface-mario-world-pixel-filled.ttf", 24, Color4f(1.f, 0.f, 0.f, 1.f));
	Texture* livesStringAmountTex = new Texture(livesStingAmount, "Super-Mario-World.ttf", 18, Color4f(1.f, 1.f, 1.f, 1.f));
	livesStringTex->Draw(Point2f(50.f, vieuwPort.height - 50.f));
	livesStringAmountTex->Draw(Point2f(50.f, vieuwPort.height - 50.f - livesStringTex->GetHeight()));
	
	std::string coinAmount = 'x' + std::to_string(m_CoinCount);
	std::ostringstream pointsAmount{};
	//pointsAmount.str() << std::to_string(m_PointCount);
	pointsAmount << std::setfill('0') << std::setw(5)<< std::to_string(m_PointCount);
	Texture* coinStringTex = new Texture(coinAmount, "Super-Mario-World.ttf", 18, Color4f(1.f, 1.f, 1.f, 1.f));
	Texture* pointsStringAmountTex = new Texture(pointsAmount.str(), "Super-Mario-World.ttf", 18, Color4f(1.f, 1.f, 1.f, 1.f));
	coinStringTex->Draw(Point2f(vieuwPort.width - 50.f - coinStringTex->GetWidth(), vieuwPort.height - 50.f));
	pointsStringAmountTex->Draw(Point2f(vieuwPort.width - 50.f - pointsStringAmountTex->GetWidth(), vieuwPort.height - 50.f - livesStringTex->GetHeight()));
	delete livesStringTex;
	delete livesStringAmountTex;
	delete coinStringTex;
	delete pointsStringAmountTex;
}

void Mario::WalkRight(float elapsedSec, const Uint8* pStates) noexcept
{
	if (m_Velocity.x <= 140.f && m_Velocity.x >= -5.f && m_IsOnGround == 1) m_Velocity.x += 1000.f * elapsedSec;
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
		if (m_Velocity.x <= 300.f && m_Velocity.x >= -5.f) m_Velocity.x += 1000.f * elapsedSec;
		//if (m_Velocity.x >= 300.f) m_Velocity.x = 300.f;
		m_FrameTime = 0.25f;
	}
	if (pStates[SDL_SCANCODE_LSHIFT]) m_JumpTime = 0.4f;
	else m_JumpTime = 0.25f;
}

void Mario::WalkLeft(float elapsedSec, const Uint8* pStates) noexcept
{
	/*if (m_Velocity.x >= -140.f && m_Velocity.x <= 0.f && m_CanJump == 1) m_Velocity.x = -140.f;
		else if (m_Velocity.x >= -80.f && m_CanJump == 0)m_Velocity.x = -80.f;
		m_WalkingState = WalkingState::left;
		m_AccTime += elapsedSec;
		if (pStates[SDL_SCANCODE_LSHIFT]&& m_CanJump ==1)
		{
			if (m_Velocity.x >= -300.f) m_Velocity.x = -300.f;
		}*/
	if (m_Velocity.x >= -140.f && m_Velocity.x <= 5.f && m_IsOnGround == 1) m_Velocity.x -= 1000.f * elapsedSec;
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
		if (m_Velocity.x >= -300.f && m_Velocity.x <= 5.f) m_Velocity.x -= 1000.f * elapsedSec;
		//if (m_Velocity.x <= -300.f) m_Velocity.x = -300.f;
		m_FrameTime = 0.25f;
	}
	if (pStates[SDL_SCANCODE_LSHIFT]) m_JumpTime = 0.4f;
	else m_JumpTime = 0.25f;
}


void Mario::HandleMovement(float elapsedSec, const Uint8* pStates) noexcept
{
	if (!m_FinishHit && m_CanMove)
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
						m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(-400.f, 0.f), m_pFireBallTex));
						m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(400.f, 0.f), m_pFireBallTex));
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
}



bool Mario::GetFinishHit() const noexcept
{
	return m_FinishHit;
}

bool Mario::GetLevelClear() const noexcept
{
	return m_LevelClear;
}

Rectf Mario::GetCurrFrameRect() const noexcept
{
	return m_FrameRect;
}

Point2f Mario::GetPos() const noexcept
{
	return m_Pos;
}

Rectf Mario::GetBounds() const noexcept
{
	return m_Bounds;
}

Vector2f Mario::GetVel() const noexcept
{
	return m_Velocity;
}

Mario::PowerUpState Mario::GetPowerUpState() const noexcept
{ 
	return m_Mariostate;
}

Mario::LookingState Mario::GetState() const noexcept
{
	return m_LookingState;
}

bool Mario::GetCheckpointHit() const noexcept
{
	return m_CheckpointHit;
}

int Mario::GetLivesAmount() const noexcept
{
	return m_LivesCount;
}

std::vector<FireBall*> Mario::GetFireBalls() const noexcept
{
	return m_pFireBalls;
}

Mario& Mario::operator=(Mario&& other) noexcept
{
	if (&other != this)
	{
		m_Pos = other.m_Pos;
		m_Velocity = other.m_Velocity;
		m_pSpritesheet = other.m_pSpritesheet;
		m_pFireBallTex = other.m_pFireBallTex;
		m_Bounds = other.m_Bounds;
		m_Mariostate = other.m_Mariostate;
		m_WalkingState = other.m_WalkingState;
		m_LookingState = other.m_LookingState;
		m_pJumpEffect = other.m_pJumpEffect;
		m_pSpinJumpEffect = other.m_pSpinJumpEffect;
		m_pDeathEffect = other.m_pDeathEffect;
		m_pFireEffect = other.m_pFireEffect;
		m_pWinEffect = other.m_pWinEffect;
		m_pHitEffect = other.m_pHitEffect;
		m_AccTime = other.m_AccTime;
		m_FrameTime = other.m_FrameTime;
		m_JumpTime = other.m_JumpTime;
		m_SpinJumpTime = other.m_SpinJumpTime;
		m_TimeInAir = other.m_TimeInAir;
		m_FrameNr = other.m_FrameNr;
		m_CoinCount = other.m_CoinCount;
		m_PointCount = other.m_PointCount;
		m_LivesCount = other.m_LivesCount;
		m_CanJump = other.m_CanJump;
		m_IsOnGround = other.m_IsOnGround;
		m_IsAlive = other.m_IsAlive;
		m_Invincible = other.m_Invincible;
		m_CheckpointHit = other.m_CheckpointHit;
		m_FinishHit = other.m_FinishHit;
		m_LevelClear = other.m_LevelClear;
		m_CanMove = other.m_CanMove;
		m_InvinTimer = other.m_InvinTimer;
		m_WinTimer = other.m_WinTimer;
		m_IFrames = other.m_IFrames;
		m_FrameRect = other.m_FrameRect;
		m_pFireBalls = other.m_pFireBalls;

		other.m_pJumpEffect = nullptr;
		other.m_pSpinJumpEffect = nullptr;
		other.m_pSpritesheet = nullptr;
		other.m_pDeathEffect = nullptr;
		other.m_pFireBallTex = nullptr;
		other.m_pFireEffect = nullptr;

	}
	return *this;
}

void Mario::Animate(float elapsedSec) noexcept
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
			
			if (m_Pos.x > 4990 * 2 && m_WinTimer > 4.f && m_WinTimer < 7.f && m_FinishHit)
			{
				m_FrameRect = Rectf(89, 57, 15, 14);
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
			if (m_Pos.x > 4990 * 2 && m_WinTimer > 4.f && m_WinTimer < 7.f && m_FinishHit)
			{
				m_FrameRect = Rectf(328, 144, 16, 28);
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
			if (m_Pos.x > 4990 * 2 && m_WinTimer > 4.f && m_WinTimer < 7.f && m_FinishHit)
			{
				m_FrameRect = Rectf(8, 224, 16, 28);
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

void Mario::Grow(const PowerUp::PowerUpType& type) noexcept
{
	if (type == PowerUp::PowerUpType::Mushroom && m_Mariostate == PowerUpState::small) m_Mariostate = PowerUpState::big;
	else if (type == PowerUp::PowerUpType::Flower && (m_Mariostate == PowerUpState::small || m_Mariostate == PowerUpState::big)) m_Mariostate = PowerUpState::fireflower;
	
}

void Mario::ShootFireBall() noexcept
{
	if (m_pFireBalls.size() < 2 && m_Mariostate == PowerUpState::fireflower)
	{
		m_pFireEffect->Play(0);
		if (m_LookingState == LookingState::left) m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(-400.f, 0.f), m_pFireBallTex));
		if (m_LookingState == LookingState::right)m_pFireBalls.push_back(new FireBall(m_Pos, Vector2f(400.f, 0.f), m_pFireBallTex));
	}
}

void Mario::AddCoin() noexcept
{
	++m_CoinCount;
}

bool Mario::GetIsAlive() const noexcept
{
	return m_IsAlive;
}

void Mario::TakeDamage() noexcept
{
	if (m_IsAlive == true)
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
}

void Mario::Bounce(float ypos) noexcept
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_SPACE] || pStates[SDL_SCANCODE_LALT])
	{
		m_CanJump = true;
		m_TimeInAir = 0;
		m_Pos.y = ypos+7;
	}
	else
	{
		m_Velocity.y = 400.f;
		m_Pos.y = ypos + 7;
	}
}
 
void Mario::Reset() noexcept
{
	m_CoinCount = 0;
	m_PointCount = 0;
	m_IsAlive = true;
	if (m_CheckpointHit == false)
	{
		m_Pos = Point2f(50, 100);
	}
	else
	{
		m_Pos = Point2f(2414 * 2, 49 * 2);
	}
	m_Mariostate = PowerUpState::small;
	m_Velocity.y = 0;
	m_LivesCount -= 1;
}

void Mario::ResetStart() noexcept
{
	m_Pos = Point2f(50, 200);
	m_Velocity = Vector2f(0, 0);
	m_WalkingState = WalkingState::none;
	m_LookingState = LookingState::right;
	m_AccTime = 0;
	m_FrameNr = 1;
	m_FrameTime = 0.22f;
	m_JumpTime = 0.4f;
	m_SpinJumpTime = 0.25f;
	m_TimeInAir = 0;
	m_Mariostate = PowerUpState::small;
	m_CanJump = 1;
	m_IsOnGround = 0;
	m_FrameRect = Rectf(328, 19, 16, 19);
	m_IsAlive = 1;
	m_CoinCount = 0;
	m_Invincible = false;
	m_InvinTimer = 0;
	m_IFrames = 1.f;
	m_CheckpointHit = false;
	m_FinishHit = false;
	m_WinTimer = 0;
	m_LivesCount = 6;
}

void Mario::SetCheckpointHit() noexcept
{
	m_CheckpointHit = true;
}

void Mario::SetVel(const Vector2f& vel) noexcept
{
	m_Velocity = vel;
}

void Mario::SetVelX(const float vel) noexcept
{
	m_Velocity.x = vel;

}

void Mario::SetVelY(const float vel) noexcept
{
	m_Velocity.y = vel;
}

void Mario::SetPosX(const float pos) noexcept
{
	m_Pos.x = pos;

}

void Mario::SetPosY(const float pos) noexcept
{
	m_Pos.y = pos;
}



void Mario::SetIsOnGround() noexcept
{
	m_Velocity.y = 0;
	m_TimeInAir = 0;
	m_CanJump = 1;
	m_IsOnGround = 1;
}

void Mario::SetCanJump(bool flag) noexcept
{
	m_CanJump = flag;
}

void Mario::SetFinishHit(bool flag) noexcept
{
	m_FinishHit = flag;
	if (m_FinishHit)
	{
		m_pWinEffect->Play(0);
	}
}

void Mario::SetLevelClear(bool flag) noexcept
{
	m_LevelClear = flag;
}

void Mario::SetCanMove(bool flag) noexcept
{
	m_CanMove = flag;
}

void Mario::SetDead() noexcept
{
	m_IsAlive = false;
	m_Velocity.y = 500;
	m_Velocity.x = 0;
	m_pDeathEffect->Play(0);
}

void Mario::AddPoints(int points) noexcept
{
	m_PointCount += points;
}
 
void Mario::OnKeyUpEvent(const SDL_KeyboardEvent& e) noexcept
{
	if (!m_FinishHit&& m_CanMove)
	{
		switch (e.keysym.sym)
		{
		case SDLK_SPACE:
		case SDLK_LALT:
			m_CanJump = false;
			break;
		}
	}
}

void Mario::OnKeyDownEvent(const SDL_KeyboardEvent& e) noexcept
{ 
	if (!m_FinishHit && m_CanMove)
	{
		switch (e.keysym.sym)
		{
		case SDLK_LSHIFT:
			ShootFireBall();
			break;
		}
	}
}

void Mario::AnimateTitle(float elapsedSec) noexcept
{
	m_AccTime += elapsedSec;
	m_FrameTime= 0.22f ;
	if (m_AccTime >= m_FrameTime)
	{
		++m_FrameNr;
		m_AccTime = 0;
		if (m_FrameNr % 2 == 1) m_FrameRect = Rectf(288, 57, 15, 14);
		else if (m_FrameNr % 2 == 0) m_FrameRect = Rectf(209, 20, 14, 20);
	}
	m_Bounds = Rectf(400, 110, GetCurrFrameRect().width * 2, GetCurrFrameRect().height * 2);

}
