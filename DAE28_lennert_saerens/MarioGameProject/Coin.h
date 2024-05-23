#pragma once
#include "Texture.h"
#include "SoundEffect.h"
class Mario;

class Coin 
{
public:
	explicit Coin(const Point2f& pos, const Texture* coinTex, const SoundEffect* sound);
	//Coin(const Coin& other) = delete; //Copy constructor afzetten (rule of three)

	//virtual ~Coin();

	virtual void Draw() const;
	virtual void Update(float elapsedSec);
	virtual void Animate();
	virtual void Collect(Mario* mario);
	virtual void Reset();

	//Coin& operator=(const Coin& rhs) = delete; // asignment= operator afzetten

protected:

	
	bool m_IsCollected;
	const Texture* m_pCoinTex;
	Point2f m_Pos;
	Rectf m_SrcRect;
	float m_FrameTime;
	float m_ElapsedSec;
	static int m_CurrFrame;
	const SoundEffect* m_pCoinSound;

};

