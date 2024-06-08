#pragma once
#include "Coin.h"
#include "Texture.h"

class DragonCoin final: public Coin 
{
public:
	explicit DragonCoin(const Point2f& pos, const Texture* tex, const SoundEffect* sound) noexcept;


	virtual void Animate() noexcept override;
	virtual void Collect(Mario* mario) noexcept;

};

