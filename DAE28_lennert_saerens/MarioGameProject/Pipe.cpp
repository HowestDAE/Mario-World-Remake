#include "pch.h"
#include "Pipe.h"
#include "Mario.h"

bool Pipe::m_Sublevel{ false };

Pipe::Pipe(const Point2f& startingPos, const Texture* tex, const SoundEffect* sound, const state& state, const bool& mirrored) noexcept
	:m_Pos {startingPos}
	, m_pSoundEffect{ sound }
	,m_pTexture{ tex }
	, m_State{state}
	,m_Mirrored{mirrored}
	,m_GoingDown{false}
	,m_GoingIn{ false }
{
	if (m_State == state::horizontal)
	{
		m_SrcRect = Rectf(192,32,32,32);
	}
	else
	{
		m_SrcRect = Rectf(96,32,32,32);
	}
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);

}

void Pipe::Update(float elapsedSec, Mario* mario) noexcept
{
	Rectf marioRect{ mario->GetBounds() };
	Rectf marioHeadRect{ marioRect.left,marioRect.bottom + (marioRect.height / 4) * 3 ,marioRect.width, marioRect.height / 4 };

	Rectf topRect{ m_Bounds.left + 5,m_Bounds.bottom + ((m_Bounds.height / 8) * 7),m_Bounds.width - 10, m_Bounds.height / 8 };
	Rectf bottomRect{ m_Bounds.left + 5 ,m_Bounds.bottom ,m_Bounds.width - 5, m_Bounds.height / 8 };
	Rectf leftRect{ m_Bounds.left,m_Bounds.bottom + 5,(m_Bounds.width / 8) * 7 , m_Bounds.height - 10 };
	Rectf rightRect{ m_Bounds.left + (m_Bounds.width / 8) * 7  ,m_Bounds.bottom + 5 ,(m_Bounds.width / 8) * 7, m_Bounds.height - 10 };

	if (m_GoingDown == true)
	{
		mario->SetVelY(-50.f);
		if (mario->GetPos().y <= m_Pos.y)
		{
			m_Sublevel = !m_Sublevel;
			mario->SetPosX(26 * 2);
			mario->SetPosY(88 * 2 - mario->GetBounds().height);
			mario->SetCanMove(true);
			m_GoingDown = false;
		}
	}
	else if (m_GoingIn)
	{
		mario->SetVelX(50.f);
		if (mario->GetPos().x >= m_Pos.x + mario->GetBounds().width/2)
		{
			m_Sublevel = !m_Sublevel;
			mario->SetPosX(2094 * 2);
			mario->SetPosY(131 * 2);
			mario->SetVel(Vector2f(600.f, 1000.f));
			mario->SetCanMove(true);
			m_GoingIn = false;
		}
	}
	else
	{
		if (utils::IsOverlapping(marioRect, topRect))
		{
			mario->SetPosY(m_Pos.y + m_Bounds.height);
			mario->SetVelY(0);
			mario->SetIsOnGround();
			const Uint8* pStates = SDL_GetKeyboardState(nullptr);
			if ((pStates[SDL_SCANCODE_DOWN]) && m_State == state::vertical)
			{
				mario->SetCanMove(false);
				m_GoingDown = true;
				m_pSoundEffect->Play(0);
			}
		}
		else  if (utils::IsOverlapping(marioRect, leftRect) && mario->GetVel().x > 0)
		{
			mario->SetVelX(0);
			mario->SetPosX(m_Pos.x - mario->GetBounds().width - 1);
			const Uint8* pStates = SDL_GetKeyboardState(nullptr);
			if ((pStates[SDL_SCANCODE_RIGHT]) && m_State == state::horizontal)
			{
				mario->SetCanMove(false);
				m_GoingIn = true;
				m_pSoundEffect->Play(0);
			}
		}
		else  if (utils::IsOverlapping(marioRect, rightRect) && mario->GetVel().x < 0)
		{
			mario->SetVelX(0);
			mario->SetPosX(m_Pos.x + m_Bounds.width + 1);
		}
	}

	
}

void Pipe::Draw() const noexcept
{
	Point2f centerPos{ m_Pos.x + m_Bounds.width / 2, m_Pos.y + m_Bounds.height / 2 };
	glPushMatrix();
	if (m_Mirrored && m_State == state::horizontal)
	{
		glTranslatef(centerPos.x, centerPos.y, 0);
		glRotatef(180.f, 0.f, 1.f, 0.f);
		glTranslatef(-centerPos.x, -centerPos.y, 0);
	}
	else if (m_Mirrored && m_State == state::vertical)
	{
		glTranslatef(centerPos.x, centerPos.y, 0);
		glRotatef(180.f, 1.f, 0.f, 0.f);
		glTranslatef(-centerPos.x, -centerPos.y, 0);
	}
	m_pTexture->Draw(m_Bounds, m_SrcRect);
	/*utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	utils::DrawRect(m_Bounds);*/
	glPopMatrix();
}
