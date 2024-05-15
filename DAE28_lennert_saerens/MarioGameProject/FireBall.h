#pragma once
#include "utils.h"
#include "Texture.h"

class FireBall final
{
public:
	FireBall(const Point2f& pos,const Vector2f& velocity, const Texture* tex );
	//FireBall(const FireBall& other) = delete; //Copy constructor afzetten (rule of three)
	//FireBall(FireBall&& other);
	//~FireBall();

	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms);
	void Draw()const;
	void SetDead();
	Point2f GetPos();
	bool GetIsAlive();
	Rectf GetBounds() const;

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

