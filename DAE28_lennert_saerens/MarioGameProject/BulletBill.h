#pragma once
#include "Enemy.h"

class BulletBill : public Enemy
{
public:
	BulletBill();
	~BulletBill();
	virtual void Update(float elapsedSec) override;
	virtual void Draw() override;
private:
};

