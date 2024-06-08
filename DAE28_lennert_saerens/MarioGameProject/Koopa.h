#pragma once
#include "Enemy.h"

class Koopa final : public Enemy
{
public:
	explicit Koopa(const Point2f& pos, const Texture* tex, const SoundEffect* sound) noexcept;
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms,  Mario* mario)noexcept override ;
	virtual void Reset() noexcept override;
	virtual void Animate(float elapsedSec)noexcept override;

private:

};

