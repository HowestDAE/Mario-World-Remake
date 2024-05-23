#pragma once
#include "Enemy.h"

class Chuck final : public Enemy
{
public:
	explicit Chuck(const Point2f& pos, const Texture* tex, const SoundEffect* sound, const SoundEffect* clapSound);
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario) override;
	virtual void Reset() override;
private:

	virtual void Animate(float elapsedSec, const Mario* mario);

	const SoundEffect* m_pClapSound;
	Point2f m_GroundPos;
	bool m_CanJump;
	bool m_IsInAir;
	bool m_InitJump;
	float m_JumpCooldown;
	float m_JumpTime;
};

