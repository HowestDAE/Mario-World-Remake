#pragma once
#include "Enemy.h"

class Koopa : public Enemy
{
public:
	explicit Koopa();
	~Koopa();
	virtual void Update(float elapsedSec) override;
	virtual void Draw() override;
private:
	Point2f m_ShellPos;
	bool m_IsOutOfShell;
};

