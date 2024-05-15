#include "pch.h"
#include "Chuck.h"

Chuck::Chuck(const Point2f& pos, const Texture* tex, const SoundEffect* sound)
	:Enemy::Enemy(pos, tex, sound)
	, m_OriginalPos{ pos }
{
	m_SrcRect = Rectf(146, 260, 24, 22);
	m_Bounds = Rectf(m_Pos.x, m_Pos.y, m_SrcRect.width * 2, m_SrcRect.height * 2);
	m_Velocity = Vector2f(0.f, 0.f);
}

void Chuck::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario)
{
}

void Chuck::Animate(float elapsedSec)
{
}
