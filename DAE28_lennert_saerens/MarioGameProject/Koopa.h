#pragma once
#include "Enemy.h"

class Koopa final : public Enemy
{
public:
	explicit Koopa(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms,  Mario* mario) override;
	virtual void Reset() override;
	virtual void Animate(float elapsedSec) override;

private:

};

