#pragma once
#include "utils.h"
#include "Texture.h"
#include "SoundEffect.h"
#include "PowerUp.h"
#include "FireBall.h"

class Mario final
{
public:
	enum class WalkingState {
		none,
		down,
		left,
		right,
		up,
		midAir
	};
	enum class LookingState {
		left,
		right,
		leftSpin,
		rightSpin
	};
	enum class PowerUpState {
		small,
		big,
		fireflower
	};
	explicit Mario(const Point2f& startingPos);
	Mario(const Mario& other) = delete; //Copy constructor afzetten (rule of three)
	Mario(Mario&& other);
	~Mario();
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms);
	void Draw() const;
	void WalkRight(float elapsedSec, const Uint8* pStates) ;
	void WalkLeft(float elapsedSec, const Uint8* pStates) ;
	void HandleMovement(float elapsedSec, const Uint8* pStates) ;
	void OnKeyUpEvent(const SDL_KeyboardEvent& e);
	void OnKeyDownEvent(const SDL_KeyboardEvent& e);
	void Animate(float elapsedSec);
	void Grow(const PowerUp::PowerUpType& type);
	void ShootFireBall();
	bool GetIsAlive()const;
	Rectf GetCurrFrameRect() const;
	Point2f GetPos() const;
	Rectf GetBounds() const;
	PowerUpState GetPowerUpState() const;

	Mario& operator=(const Mario& rhs) = delete; // asignment= operator afzetten
	Mario& operator=(Mario&& other);

private:
	Point2f m_Pos;
	Vector2f m_Velocity;
	Texture* m_pSpritesheet;
	Texture* m_pFireBallTex;
	Rectf m_Bounds;
	PowerUpState m_Mariostate;
	WalkingState m_WalkingState;
	LookingState m_LookingState;
	SoundEffect* m_pJumpEffect;
	SoundEffect* m_pSpinJumpEffect;
	SoundEffect* m_pDeathEffect;
	SoundEffect* m_pFireEffect;
	float m_AccTime;
	float m_FrameTime;
	float m_JumpTime;
	float m_SpinJumpTime;
	float m_TimeInAir;
	int m_FrameNr;
	bool m_CanJump;
	bool m_IsOnGround;
	bool m_IsAlive;
	Rectf m_FrameRect;
	std::vector<FireBall*> m_pFireBalls;
};

