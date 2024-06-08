#pragma once
#include "Block.h"
#include "PowerUp.h"
#include "Mario.h"


class QBlock : public Block
{
public:
	explicit QBlock(const Point2f& pos, const Texture* tex, const SoundEffect* sound, PowerUp* content) noexcept;
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, const std::vector<Block*>& blocks) noexcept override;
	void CheckHit(Mario* mario) noexcept override;
	void Draw() const noexcept override;
	void Reset()noexcept  override;
private:
	void Animate(float elapsedSec) noexcept;
	PowerUp* m_pContent;
	bool m_CollectablePowerUp;
};

