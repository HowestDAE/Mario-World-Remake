#pragma once
#include "utils.h"
#include "Texture.h"

class Mario final
{
private:
	enum class WalkingState {
		none,
		down,
		left,
		right,
		up
	};

	enum class state {
		small,
		big,
		fireflower
	};

	Point2f m_Pos;
	Vector2f m_Velocity;
	Texture* m_pSpritesheet;
	Rectf m_Bounds;
	state m_Mariostate;
	WalkingState m_WalkingState;
	float m_AccTime;
	float m_FrameTime;
	float m_JumpTime;
	float m_TimeInAir;
	int m_FrameNr;
	bool m_CanJump;
public:
	Mario(Point2f startingPos);
	~Mario();
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape);
	void Draw() const;
	void HandleMovement(float elapsedSec, const Uint8* pStates);
	void Animate(float elapsedSec);
	Rectf GetCurrFrameRect() const;
	Point2f GetPos() const;
};

