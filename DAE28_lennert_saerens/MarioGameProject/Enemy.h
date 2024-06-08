#pragma once
#include "utils.h"
#include "Texture.h"
#include "SoundEffect.h"
class Mario;

class Enemy
{
public:
	explicit Enemy(const Point2f& pos, const Texture* tex, const SoundEffect* sound) noexcept;
	virtual ~Enemy() = default;
	Enemy(const Enemy& other) = default; //Copy constructor afzetten (rule of three)
	Enemy(Enemy&& other) = default;
	Enemy& operator=(const Enemy& rhs) = default; // asignment= operator afzetten
	Enemy& operator=(Enemy&& other) = default;



	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, Mario* mario) noexcept;
	virtual void Draw() const noexcept;
	virtual void CheckHit(Mario* mario) noexcept;
	virtual void Reset() noexcept;
protected:
	Rectf GetBounds() const noexcept;
	virtual void Animate(float elapsedSec) noexcept;
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

