#pragma once
#include "Coin.h"
#include "Texture.h"

class DragonCoin final: public Coin 
{
public:
	explicit DragonCoin(const Point2f& pos, const Texture* tex, const SoundEffect* sound);


	virtual void Animate()override;
};

