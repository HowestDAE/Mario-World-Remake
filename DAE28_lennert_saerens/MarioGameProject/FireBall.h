#pragma once
#include "utils.h"
#include "Texture.h"
#include "Block.h"

class FireBall final
{
public:
	explicit FireBall(const Point2f& pos,const Vector2f& velocity, const Texture* tex ) noexcept;
	//FireBall(const FireBall& other) = delete; //Copy constructor afzetten (rule of three)
	//FireBall(FireBall&& other);
	//~FireBall();

	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks) noexcept;
	void Draw()const noexcept;
	void SetDead() noexcept;
	Point2f GetPos() const noexcept;
	bool GetIsAlive() const noexcept;
	Rectf GetBounds() const noexcept;

	//FireBall& operator=(const FireBall& rhs) = delete; // asignment= operator afzetten
	//FireBall& operator=(FireBall&& other);
private:

	Point2f m_Pos;
	Vector2f m_Velocity;
	const Texture* m_pTexture;
	Rectf m_Bounds;
	Rectf m_SrcRect;
	float m_ElapsedSec;
	float m_FrameTime;
	int m_FrameNr;
	bool m_IsAlive;


};

