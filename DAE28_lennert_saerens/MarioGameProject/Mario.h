#pragma once
#include "utils.h"
#include "Texture.h"
#include "SoundEffect.h"
#include "PowerUp.h"
#include <vector>
class FireBall;

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
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks);
	void Draw() const;
	void HandleMovement(float elapsedSec, const Uint8* pStates) ;
	void OnKeyUpEvent(const SDL_KeyboardEvent& e);
	void OnKeyDownEvent(const SDL_KeyboardEvent& e);
	void AnimateTitle(float elapsedSec);


	void Grow(const PowerUp::PowerUpType& type);
	void AddCoin();
	bool GetIsAlive() const;
	void TakeDamage();
	void Bounce(float ypos);
	void Reset();
	void ResetStart();
	void SetCheckpointHit();
	void SetVel(const Vector2f& vel);
	void SetVelX(const float vel);
	void SetVelY(const float vel);
	void SetPosX(const float pos);
	void SetPosY(const float pos);
	void SetIsOnGround();
	void SetCanJump(bool flag);
	void SetFinishHit(bool flag);
	void SetLevelClear(bool flag);
	void SetCanMove(bool flag);

	bool GetFinishHit() const;
	bool GetLevelClear() const;
	Rectf GetCurrFrameRect() const;
	Point2f GetPos() const;
	Rectf GetBounds() const;
	Vector2f GetVel() const;
	PowerUpState GetPowerUpState() const;
	LookingState GetState() const;
	std::vector<FireBall*> GetFireBalls() const;

	Mario& operator=(const Mario& rhs) = delete; // asignment= operator afzetten
	Mario& operator=(Mario&& other);

private:
	void WalkRight(float elapsedSec, const Uint8* pStates);
	void WalkLeft(float elapsedSec, const Uint8* pStates);
	void ShootFireBall();
	void Animate(float elapsedSec);

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
	SoundEffect* m_pWinEffect;
	const SoundEffect* m_pHitEffect;
	float m_AccTime;
	float m_FrameTime;
	float m_JumpTime;
	float m_SpinJumpTime;
	float m_TimeInAir;
	int m_FrameNr;
	int m_CoinCount;
	bool m_CanJump;
	bool m_IsOnGround;
	bool m_IsAlive;
	bool m_Invincible;
	bool m_CheckpointHit;
	bool m_FinishHit;
	bool m_LevelClear;
	bool m_CanMove;
	float m_InvinTimer;
	float m_WinTimer;
	float m_IFrames;
	Rectf m_FrameRect;
	std::vector<FireBall*> m_pFireBalls;
};

