#pragma once
#include "Texture.h"
#include "utils.h"
#include "SoundEffect.h"

class Mario;

class PowerUp final
{

public:
	enum class PowerUpType
	{
		Mushroom,
		Flower
	};
	PowerUp(const Mario& mario, const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	PowerUp(const PowerUpType& powerup, const Point2f& pos, const Texture* tex, const SoundEffect* sound);
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms);
	void Draw() const;
	bool Collect(const Mario* mario);
	virtual PowerUpType GetPowerUpType();
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
	Rectf m_Bounds;
	Rectf m_SrcRect;
	PowerUpType m_Type;
	bool m_IsCollected;


};

