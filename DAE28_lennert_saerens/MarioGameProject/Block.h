#pragma once
#include "Texture.h"
#include "SoundEffect.h"
#include "Mario.h"
class Block 
{
public:
	explicit Block(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	Block(const Block& other) = default;
	Block(Block&& other) = default;
	Block& operator=(const Block& rhs) = default; 
	Block& operator=(Block&& other) = default;

	virtual void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks);
	virtual void Draw() const;
	virtual void CheckHit(Mario* mario);
	virtual void Reset();
	virtual bool GetIsHit() const;
	virtual bool GetIsBroken() const;
	virtual Rectf GetBounds() const;
protected:
	void Animate(float elapsedSec);

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

