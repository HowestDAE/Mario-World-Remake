#pragma once
#include "utils.h"
#include "Texture.h"
class Enemy
{
public:
	explicit Enemy();
	virtual ~Enemy();
	virtual void Update(float elapsedSec);
	virtual void Draw();
protected:
	Point2f GetPos() const;
	void SetPos();
	Vector2f GetVel() const;
	void SetVel();
private:
	Point2f m_Pos;
	Vector2f m_Velocity;
	bool m_IsAlive;
};

