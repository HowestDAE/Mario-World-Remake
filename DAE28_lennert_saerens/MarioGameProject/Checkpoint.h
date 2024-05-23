#pragma once
#include "Texture.h"
#include "SoundEffect.h"
#include "Mario.h"
class Checkpoint final
{
public:
	Checkpoint(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	void Draw() const;
	void CheckIsHit(Mario* mario);
	void Update();
private:
	const Point2f m_Pos;
	bool m_IsHit;
	const Texture* m_pTexture;
	const SoundEffect* m_pSoundEffect;
	Rectf m_Bounds;
	Rectf m_SrcRect;
};

