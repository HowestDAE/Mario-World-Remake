#pragma once
#include "Texture.h"
#include "utils.h"
#include "SoundEffect.h"

class Mario;
class Block;

class PowerUp final
{

public:
	enum class PowerUpType
	{
		Mushroom,
		Flower
	};
	PowerUp(const Mario& mario, const Point2f& pos, const Texture* tex, const SoundEffect* sound, bool iscollectable);
	PowerUp(const PowerUpType& powerup, const Point2f& pos, const Texture* tex, const SoundEffect* sound, bool iscollectable);
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, std::vector<Block*> blocks);
	void Draw() const;
	bool Collect(const Mario* mario);
	PowerUpType GetPowerUpType();
	void Reset();
	void SetPowerUpType(const PowerUpType& type);
	void SetIsCollectable(bool flag);
	void SetPosY(float pos);
	//PowerUp(const PowerUp& other) = delete; //Copy constructor afzetten (rule of three)
	//PowerUp(PowerUp&& other);
	//~PowerUp();

	//PowerUp& operator=(const PowerUp& rhs) = delete; // asignment= operator afzetten
	//PowerUp& operator=(PowerUp&& other);

protected:

	const Texture* m_pTexture;
	const SoundEffect* m_pSound;
	Vector2f m_Velocity;
	Point2f m_Pos;
	const Point2f m_OriginalPos;
	Rectf m_Bounds;
	Rectf m_SrcRect;
	PowerUpType m_Type;
	bool m_IsCollected;
	bool m_IsCollectable;
	bool m_Changable;
	bool m_OriginalCollectableState;


};

