#pragma once
#include "Texture.h"
#include "SoundEffect.h"
#include "Mario.h"



class Finish final
{
public:
	Finish(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	void Draw() const;
	void CheckIsHit(Mario* mario);
	void Update(float elapsedSec);
private:
	Point2f m_Pos;
	Point2f m_BarPos;
	const Point2f m_OriginalPos;
	bool m_IsHit;
	const Texture* m_pTexture;
	const SoundEffect* m_pSoundEffect;
	Rectf m_Bounds;
	Rectf m_PoleBounds;
	Rectf m_SrcRectPole;
	Rectf m_SrcRectBar;
	Vector2f m_Vel;
};

