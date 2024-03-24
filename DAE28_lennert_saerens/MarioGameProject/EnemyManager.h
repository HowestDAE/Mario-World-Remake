#pragma once
#include "utils.h"
#include "Texture.h"
class EnemyManager final 
{
public:
	static enum class EnemyType
	{
		Koopa,
		Dinosaur,
		PianhaPlant,
		BulletBill,
		Chuck,
	};

	explicit EnemyManager(EnemyType enemyType, Point2f pos);
	~EnemyManager();
	void Update(float elapsedSec);
	void Draw()const;
private:
	Texture m_Texture;
};

