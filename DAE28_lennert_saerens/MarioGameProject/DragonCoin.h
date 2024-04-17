#pragma once
#include "Coin.h"

class DragonCoin final: public Coin 
{
public:
	explicit DragonCoin(const Point2f& pos);
	DragonCoin(const DragonCoin& other) = delete;

	virtual void Update(float elapsedSec) override;

	DragonCoin& operator=(const DragonCoin& rhs) = delete; // asignment= operator afzetten

};

