#include "pch.h"
#include "Coin.h"
#include "Mario.h"
#include "utils.h"

int Coin::m_CoinCount{};
Coin::Coin(const Point2f& pos)
	:m_IsCollected{ false }
	,m_CurrFrame{}
	,m_FrameTime{0.2f}
	,m_ElapsedSec{}
	, m_Pos{ pos }
{
	m_pCoinTex = new Texture("misc-8.png");
	m_pCoinSound = new SoundEffect("Sounds/smw_coin.wav");
}

Coin::~Coin()
{
	delete m_pCoinTex;
	m_pCoinTex = nullptr;
	delete m_pCoinSound;
	m_pCoinSound = nullptr;
}

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
	if (m_IsCollected == false)
	{
		m_ElapsedSec += elapsedSec;
		if (m_ElapsedSec >= m_FrameTime)
		{
			m_ElapsedSec = 0;
			++m_CurrFrame;
			if (m_CurrFrame > 3) m_CurrFrame = 0;
		}
		if (m_CurrFrame == 0) m_SrcRect = Rectf(2, 16, 12, 16);
		else if (m_CurrFrame == 1) m_SrcRect = Rectf(20, 16, 8, 16);
		else if (m_CurrFrame == 2) m_SrcRect = Rectf(37, 16, 6, 16);
		else if (m_CurrFrame == 3) m_SrcRect = Rectf(52, 16, 9, 16);
	}
}

void Coin::Collect(const Mario* mario)
{
	if (utils::IsOverlapping(Rectf{ m_Pos.x-m_SrcRect.width, m_Pos.y-m_SrcRect.height, m_SrcRect.width * 2, m_SrcRect.height * 2 }, mario->GetBounds())&& m_IsCollected == false)
	{
		++m_CoinCount;
		m_IsCollected = true;
		m_pCoinSound->Play(0);
	}
}
