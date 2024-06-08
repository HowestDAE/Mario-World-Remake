#pragma once
#include "Enemy.h"
#include "SoundEffect.h"

class PiranhaPlant final : public Enemy
{
public:
	explicit PiranhaPlant(const Point2f& pos, const Texture* tex, const SoundEffect* sound,const SoundEffect* spinsound ) noexcept;
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms,  Mario* mario) noexcept override;
	virtual void CheckHit(Mario* mario)noexcept override;
	virtual void Reset() noexcept override;

private:
	virtual void Animate(float elapsedSec) noexcept override;
	const SoundEffect* m_pSpinSound;
	float m_AnimSec;
};

