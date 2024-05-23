#pragma once
#include "utils.h"
#include "Texture.h"
#include "SoundEffect.h"
class Mario;

class Enemy
{
public:
	explicit Enemy(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const Mario* mario);
	virtual void Draw() const;
	virtual void CheckHit(Mario* mario);
	virtual void Reset();
protected:
	Rectf GetBounds() const;
	virtual void Animate(float elapsedSec);
	Point2f m_Pos;
	Rectf m_Bounds;
	Rectf m_SrcRect;
	Vector2f m_Velocity;
	const Point2f m_OriginalPos;
	int m_HP;
	bool m_IsAlive;
	bool m_DeathAnimation;
	float m_Deathtimer;
	float m_FrameTime;
	float m_ElapsedSec;
	const Texture* m_pTexture;
	int m_FrameNr;
	const SoundEffect* m_StompSound;
	bool m_LookingRight;
private:
};

