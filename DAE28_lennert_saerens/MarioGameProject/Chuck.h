#pragma once
#include "Enemy.h"

class Chuck final : public Enemy
{
public:
	explicit Chuck(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario) override;
private:
	virtual void Animate(float elapsedSec) override;
	const Point2f m_OriginalPos;
};

