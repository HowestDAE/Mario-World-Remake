#pragma once
#include "Texture.h"
#include "SoundEffect.h"
class Mario;

class Coin 
{
public:
	Coin(const Point2f& pos, const Texture* coinTex, const SoundEffect* sound);
	Coin(const Coin& other) = delete; //Copy constructor afzetten (rule of three)

	virtual ~Coin();

	virtual void Draw()const;
	virtual void Update(float elapsedSec);
	virtual void Collect(const Mario* mario);

	Coin& operator=(const Coin& rhs) = delete; // asignment= operator afzetten

protected:

	
	bool m_IsCollected;
	static int m_CoinCount;
	const Texture* m_pCoinTex;
	Point2f m_Pos;
	Rectf m_SrcRect;
	float m_FrameTime;
	float m_ElapsedSec;
	int m_CurrFrame;
	const SoundEffect* m_pCoinSound;

};

