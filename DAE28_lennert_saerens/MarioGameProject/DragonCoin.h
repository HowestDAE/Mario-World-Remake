#pragma once
#include "Coin.h"
#include "Texture.h"

class DragonCoin final: public Coin 
{
public:
	explicit DragonCoin(const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	DragonCoin(const DragonCoin& other) = delete;


	virtual void Update(float elapsedSec) override;

	DragonCoin& operator=(const DragonCoin& rhs) = delete; // asignment= operator afzetten


};

