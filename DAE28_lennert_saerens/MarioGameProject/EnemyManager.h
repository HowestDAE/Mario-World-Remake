#pragma once
#include "utils.h"
#include "Texture.h"
#include "Enemy.h"
#include "BulletBill.h"
#include "PiranhaPlant.h"
#include "Koopa.h"
#include "Chuck.h"
#include <vector>
class EnemyManager final 
{
public:
	static enum class EnemyType
	{
		Enemy,
		Koopa,
		Dinosaur,
		PianhaPlant,
		BulletBill,
		Chuck,
	};

	explicit EnemyManager(Texture* tex);
	EnemyManager(const EnemyManager& other) = delete; //Copy constructor afzetten (rule of three)
	EnemyManager(EnemyManager&& other);

	~EnemyManager();
	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& landscape, const std::vector<std::vector<Point2f>>& platforms, Mario* mario);
	void Draw()const;
	void PushBackEnemy(const Point2f& pos, const EnemyType& enemy, const SoundEffect* sound);
	void PushBackEnemy(const Point2f& pos, const EnemyType& enemy,const SoundEffect* sound, const SoundEffect* spinSound);
	void Reset();


	EnemyManager& operator=(const EnemyManager& rhs) = delete; // asignment= operator afzetten
	EnemyManager& operator=(EnemyManager&& other);
private:
	Texture* m_pTexture;
	std::vector<Enemy*> m_pEnemies;
};

