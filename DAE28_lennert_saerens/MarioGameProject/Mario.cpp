#include "pch.h"
#include "Mario.h"
#include "iostream"

Mario::Mario(const Point2f& startingPos)
	:m_Pos{startingPos}
	,m_Velocity{}
	,m_WalkingState{}
	,m_AccTime{}
	,m_FrameNr{1}
	,m_FrameTime{ 0.28f }
	, m_JumpTime{ 0.4f }
	,m_TimeInAir{0}
	, m_Mariostate{ state::small }
	, m_CanJump{ 1 }
	,m_IsOnGround{  }
{
	m_pSpritesheet = new Texture("mario-spritesheet.png");
	m_Bounds = Rectf(0, 0, GetCurrFrameRect().width*2, GetCurrFrameRect().height*2);
	m_pJumpEffect = new SoundEffect("Sounds/smw_jump.wav");
}

Mario::~Mario()
{
	delete m_pSpritesheet;
	m_pSpritesheet = nullptr;
	delete m_pJumpEffect;
	m_pJumpEffect = nullptr;
}

void Mario::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape)
{

	const float gravity{ -7.f };
	const float friction{ -1.4f };

	Point2f leftTop{ m_Pos.x, m_Pos.y + m_Bounds.height };
	Point2f leftBottom{ m_Pos.x, m_Pos.y };
	Point2f leftMiddle{ m_Pos.x, m_Pos.y + m_Bounds.height / 2 };
	Point2f rightTop{ m_Pos.x + m_Bounds.width, m_Pos.y + m_Bounds.height };
	Point2f rightBottom{ m_Pos.x + m_Bounds.width, m_Pos.y };
	Point2f rightMiddle{ m_Pos.x + m_Bounds.width, m_Pos.y + m_Bounds.height / 2 };

	utils::HitInfo hitInfo{};

	m_Pos.x += m_Velocity.x * elapsedSec;
	m_Pos.y += m_Velocity.y * elapsedSec;
	if (m_Velocity.x < 1.f && m_Velocity.x >-1.f) m_Velocity.x = 0;
	m_Bounds.left = m_Pos.x;
	m_Bounds.bottom = m_Pos.y;

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
		else
		{
			m_Velocity.y += gravity;
		}
		if (m_Velocity.x > 0 && m_IsOnGround == 1) m_Velocity.x += friction;
		if (m_Velocity.x < 1.f && m_Velocity.x >-1.f) m_Velocity.x = 0;
		if (m_Velocity.x < 0 && m_IsOnGround == 1) m_Velocity.x -= friction;
		if (m_Velocity.x < 1.f && m_Velocity.x >-1.f) m_Velocity.x = 0;


	}

	//Animate(elapsedSec);

}

void Mario::Draw() const
{
	/*glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	m_pTexture->Draw();
	glPopMatrix();*/

	Rectf drawRect{ m_Pos.x,m_Pos.y, GetCurrFrameRect().width*2,GetCurrFrameRect().height*2};
	m_pSpritesheet->Draw(drawRect,GetCurrFrameRect());
}


void Mario::HandleMovement(float elapsedSec, const Uint8* pStates)
{
	m_WalkingState = WalkingState::none;

	if (pStates[SDL_SCANCODE_RIGHT])
	{
		if (m_Velocity.x <= 140.f && m_Velocity.x >= 0.f && m_IsOnGround == 1) m_Velocity.x += 1000.f*elapsedSec;
		else if (m_Velocity.x <= 140.f && m_IsOnGround == 0 )m_Velocity.x += 2500.f*elapsedSec;
		m_WalkingState = WalkingState::right;
		m_AccTime += elapsedSec;
		if (pStates[SDL_SCANCODE_LSHIFT] && m_IsOnGround == 1)
		{
			if (m_Velocity.x <= 300.f && m_Velocity.x >= 0.f) m_Velocity.x += 1000.f*elapsedSec;
			if (m_Velocity.x >= 300.f) m_Velocity.x = 300.f;
		}
		if (pStates[SDL_SCANCODE_LSHIFT]) m_JumpTime = 0.4f;
		else m_JumpTime = 0.25f;
	}
	if (pStates[SDL_SCANCODE_LEFT])
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
		m_WalkingState = WalkingState::left;
		m_AccTime += elapsedSec;
		if (pStates[SDL_SCANCODE_LSHIFT] && m_IsOnGround == 1)
		{
			if (m_Velocity.x >= -300.f && m_Velocity.x <= 0.f) m_Velocity.x -= 1000.f * elapsedSec;
			if (m_Velocity.x <= -300.f) m_Velocity.x = -300.f;
		}
		if (pStates[SDL_SCANCODE_LSHIFT]) m_JumpTime = 0.4f;
		else m_JumpTime = 0.25f;

	}

	if (pStates[SDL_SCANCODE_DOWN])
	{
		m_WalkingState = WalkingState::down;

	}
	if (pStates[SDL_SCANCODE_UP])
	{
		m_WalkingState = WalkingState::up;
	}
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

	if (m_AccTime >= m_FrameTime)
	{
		m_AccTime = 0;
		++m_FrameNr;
	}
	if (m_TimeInAir >= m_JumpTime)
	{
 		m_CanJump = 0;
	}
	/*if ((pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_RIGHT] )==0)
	{
		m_WalkingState = WalkingState::none;
	}*/
}



Rectf Mario::GetCurrFrameRect() const
{
	return Rectf(328, 19, 16, 19);
}

Point2f Mario::GetPos() const
{
	return m_Pos;
}

void Mario::Animate(float elapsedSec)
{
}

void Mario::OnKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:
		m_CanJump = 0;
		break;
	}
}
