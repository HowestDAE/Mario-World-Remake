#pragma once
#include "Enemy.h"

class Chuck : public Enemy
{
public:
	explicit Chuck();
	~Chuck();
	virtual void Update(float elapsedSec) override;
	virtual void Draw() override;
private:
};

