#pragma once
#include "Block.h"
#include "PowerUp.h"

class QBlock : public Block
{
public:
	QBlock(const Point2f& pos, const Texture* tex, const SoundEffect* sound, PowerUp* content);
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, std::vector<Block*> blocks) override;
	void CheckHit(Mario* mario) override;
	void Draw() const override;
	void Reset() override;
private:
	void Animate(float elapsedSec);
	PowerUp* m_pContent;
	bool m_CollectablePowerUp;
};

