#pragma once
#include "utils.h"
#include "Texture.h"
#include "SoundEffect.h"

class Mario final
{
private:
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

	Point2f m_Pos;
	Vector2f m_Velocity;
	Texture* m_pSpritesheet;
	Rectf m_Bounds;
	PowerUpState m_Mariostate;
	WalkingState m_WalkingState;
	LookingState m_LookingState;
	SoundEffect* m_pJumpEffect;
	SoundEffect* m_pSpinJumpEffect;
	float m_AccTime;
	float m_FrameTime;
	float m_JumpTime;
	float m_SpinJumpTime;
	float m_TimeInAir;
	int m_FrameNr;
	bool m_CanJump;
	bool m_IsOnGround;
	Rectf m_FrameRect;


public:
	explicit Mario(const Point2f& startingPos);
	Mario(const Mario& other) = delete; //Copy constructor afzetten (rule of three)
	~Mario();
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape);
	void Draw() const;
	void WalkRight(float elapsedSec, const Uint8* pStates) ;
	void WalkLeft(float elapsedSec, const Uint8* pStates) ;
	void HandleMovement(float elapsedSec, const Uint8* pStates) ;
	void OnKeyUpEvent(const SDL_KeyboardEvent& e);
	void Animate(float elapsedSec);
	Rectf GetCurrFrameRect() const;
	Point2f GetPos() const;
	Rectf GetBounds() const;

	Mario& operator=(const Mario& rhs) = delete; // asignment= operator afzetten
};

