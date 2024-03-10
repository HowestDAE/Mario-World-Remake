#pragma once
#include "utils.h"
#include "Texture.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	virtual void Update(float elapsedSec);
	virtual void Draw();
private:
	Point2f m_Pos;
	Vector2f m_Velocity;
	bool m_IsAlive;
};

