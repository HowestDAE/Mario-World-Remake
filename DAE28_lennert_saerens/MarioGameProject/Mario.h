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
	explicit Mario(const Point2f& startingPos) noexcept;
	Mario(const Mario& other) = delete; //Copy constructor afzetten (rule of three)
	Mario(Mario&& other) noexcept;
	~Mario() noexcept;
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks) noexcept;
	void Draw() const noexcept;
	void DrawUI(const Rectf& vieuwPort) const noexcept;
	void HandleMovement(float elapsedSec, const Uint8* pStates) noexcept;
	void OnKeyUpEvent(const SDL_KeyboardEvent& e) noexcept;
	void OnKeyDownEvent(const SDL_KeyboardEvent& e) noexcept;
	void AnimateTitle(float elapsedSec) noexcept;


	void Grow(const PowerUp::PowerUpType& type) noexcept;
	void AddCoin() noexcept;
	bool GetIsAlive() const noexcept;
	void TakeDamage() noexcept;
	void Bounce(float ypos) noexcept;
	void Reset() noexcept;
	void ResetStart() noexcept;
	void SetCheckpointHit() noexcept;
	void SetVel(const Vector2f& vel) noexcept;
	void SetVelX(const float vel) noexcept;
	void SetVelY(const float vel) noexcept;
	void SetPosX(const float pos) noexcept;
	void SetPosY(const float pos) noexcept;
	void SetIsOnGround() noexcept;
	void SetCanJump(bool flag) noexcept;
	void SetFinishHit(bool flag) noexcept;
	void SetLevelClear(bool flag) noexcept;
	void SetCanMove(bool flag) noexcept;
	void SetDead() noexcept;
	void AddPoints(int points) noexcept;

	bool GetFinishHit() const noexcept;
	bool GetLevelClear() const noexcept;
	Rectf GetCurrFrameRect() const noexcept;
	Point2f GetPos() const noexcept;
	Rectf GetBounds() const noexcept;
	Vector2f GetVel() const noexcept;
	PowerUpState GetPowerUpState() const noexcept;
	LookingState GetState() const noexcept;
	bool GetCheckpointHit() const noexcept;
	int GetLivesAmount() const noexcept;
	std::vector<FireBall*> GetFireBalls() const noexcept;

	Mario& operator=(const Mario& rhs) = delete; // asignment= operator afzetten
	Mario& operator=(Mario&& other) noexcept;

private:
	void WalkRight(float elapsedSec, const Uint8* pStates) noexcept;
	void WalkLeft(float elapsedSec, const Uint8* pStates) noexcept;
	void ShootFireBall() noexcept;
	void Animate(float elapsedSec) noexcept;

	
	/*Texture* m_pLivesTex;
	Texture* m_pLivesAmountTex;
	Texture* m_pCoinAmountTex;
	Texture* m_pCoinStringTex;
	Texture* m_pPointsStringTex;*/
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
	int m_PointCount;
	int m_LivesCount;
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

