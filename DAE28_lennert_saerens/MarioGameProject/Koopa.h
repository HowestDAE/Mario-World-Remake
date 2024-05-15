#pragma once
#include "Enemy.h"

class Koopa final : public Enemy
{
public:
	explicit Koopa();
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario) override;
	virtual void Draw() const override;
private:
	Point2f m_ShellPos;
	bool m_IsOutOfShell;
};

