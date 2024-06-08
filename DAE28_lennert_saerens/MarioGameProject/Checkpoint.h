#pragma once
#include "Texture.h"
#include "SoundEffect.h"
#include "Mario.h"
class Checkpoint final
{
public:
	explicit Checkpoint(const Point2f& pos, const Texture* tex, const SoundEffect* sound) noexcept;
	void Draw() const noexcept;
	void CheckIsHit(Mario* mario) noexcept;
	void Update() noexcept;
	void Reset() noexcept;
private:
	const Point2f m_Pos;
	bool m_IsHit;
	const Texture* m_pTexture;
	const SoundEffect* m_pSoundEffect;
	Rectf m_Bounds;
	Rectf m_SrcRect;
};

