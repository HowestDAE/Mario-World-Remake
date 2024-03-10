#pragma once
#include "Enemy.h"

class PiranhaPlant : public Enemy
{
public:
	PiranhaPlant();
	~PiranhaPlant();
	virtual void Update(float elapsedSec) override;
	virtual void Draw() override;
private:
};

