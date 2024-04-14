#pragma once
#include "Texture.h"
#include "SoundEffect.h"
class Mario;

class Coin final
{
public:
	Coin(const Point2f& pos);
	Coin(const Coin& other) = delete; //Copy constructor afzetten (rule of three)

	~Coin();

	void Draw()const;
	void Update(float elapsedSec);
	void Collect(const Mario* mario);

	Coin& operator=(const Coin& rhs) = delete; // asignment= operator afzetten

private:

	
	bool m_IsCollected;
	static int m_CoinCount;
	Texture* m_pCoinTex;
	Point2f m_Pos;
	Rectf m_SrcRect;
	float m_FrameTime;
	float m_ElapsedSec;
	int m_CurrFrame;
	SoundEffect* m_pCoinSound;

};

