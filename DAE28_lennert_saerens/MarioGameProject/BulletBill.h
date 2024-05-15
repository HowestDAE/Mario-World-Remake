#pragma once
#include "Enemy.h"

class BulletBill final : public Enemy
{
public:
	explicit BulletBill(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario) override;
	virtual void CheckHit(Mario* mario) override;

private:
};

