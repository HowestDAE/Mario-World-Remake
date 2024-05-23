#include "pch.h"
#include "Coin.h"
#include "Mario.h"
#include "utils.h"

int Coin::m_CurrFrame{ 0 };


Coin::Coin(const Point2f& pos, const Texture* coinTex, const SoundEffect* sound)
	:m_IsCollected{ false }
	, m_FrameTime{ 0.3f }
	, m_ElapsedSec{}
	, m_Pos{ pos }
{
	m_pCoinTex = coinTex;
	m_pCoinSound = sound;
}

//Coin::~Coin()
//{
//	m_pCoinSound = nullptr;
//	m_pCoinTex = nullptr;
//}

void Coin::Draw() const
{
	if (m_IsCollected == false)
	{
		Rectf drawRect{ m_Pos.x - m_SrcRect.width, m_Pos.y - m_SrcRect.height, m_SrcRect.width * 2, m_SrcRect.height * 2 };
		m_pCoinTex->Draw(drawRect, m_SrcRect);
	}
}

void Coin::Update(float elapsedSec)
{
	
	m_ElapsedSec += elapsedSec;
	if (m_ElapsedSec >= m_FrameTime)
	{
		m_ElapsedSec = 0;
		++m_CurrFrame;
		if (m_CurrFrame > 12) m_CurrFrame = 0;
	}
		
	
}

void Coin::Animate()
{
	if (m_IsCollected == false)
	{
		if (m_CurrFrame%4 == 0) m_SrcRect = Rectf(2, 16, 12, 16);
		else if (m_CurrFrame%4 == 1) m_SrcRect = Rectf(20, 16, 8, 16);
		else if (m_CurrFrame%4 == 2) m_SrcRect = Rectf(37, 16, 6, 16);
		else if (m_CurrFrame%4 == 3) m_SrcRect = Rectf(52, 16, 9, 16);
	}
}

void Coin::Collect(Mario* mario)
{
	if (utils::IsOverlapping(Rectf{ m_Pos.x-m_SrcRect.width, m_Pos.y-m_SrcRect.height, m_SrcRect.width * 2, m_SrcRect.height * 2 }, mario->GetBounds())&& m_IsCollected == false)
	{
		m_IsCollected = true;
		m_pCoinSound->Play(0);
		mario->AddCoin();
	}
}

void Coin::Reset()
{
	m_IsCollected = false;
}
