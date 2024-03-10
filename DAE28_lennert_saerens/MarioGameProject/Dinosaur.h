#pragma once
#include "Enemy.h"

class Dinosaur : public Enemy
{
public:
	Dinosaur();
	~Dinosaur();
	virtual void Update(float elapsedSec) override;
	virtual void Draw() override;
private:
	bool m_IsFlat;
};

