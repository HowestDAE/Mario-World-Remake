#pragma once
#include "Texture.h"
#include "SoundEffect.h"
#include "Mario.h"
class Block 
{
public:
	explicit Block(const Point2f& pos, const Texture* tex, const SoundEffect* sound) noexcept;
	Block(const Block& other) = default;
	Block(Block&& other) = default;
	Block& operator=(const Block& rhs) = default; 
	Block& operator=(Block&& other) = default;

	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks) noexcept;
	virtual void Draw() const noexcept;
	virtual void CheckHit(Mario* mario) noexcept;
	virtual void Reset() noexcept;
	virtual bool GetIsHit() const noexcept;
	virtual bool GetIsBroken() const noexcept;
	virtual Rectf GetBounds() const noexcept;
protected:
	void Animate(float elapsedSec) noexcept;

	Point2f m_Pos;
	Rectf m_Bounds;
	Rectf m_SrcRect;
	bool m_IsBroken;
	bool m_IsHit;
	const Texture* m_pTexture;
	const SoundEffect* m_pSoundEffect;
	float m_HitSec;
	float m_FrameSec;
	int m_FrameNr;

};

