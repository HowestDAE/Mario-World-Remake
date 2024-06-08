#pragma once
#include <vector>
#include "Texture.h"
#include "SoundEffect.h"
#include "SoundStream.h"

class Mario;
class Camera;
class Coin;
class Enemy;
class TextureManager;
class SoundEffectManager;
class PowerUp;
class EnemyManager;
class Checkpoint;
class Block;
class Finish;
class Pipe;

class Level final
{
public:
	Level(int levelNr, const Texture* levelTex, const std::vector<std::vector<Point2f>> landscape, const std::vector<std::vector<Point2f>> platforms, const Rectf vieuwPort, Mario* mario, bool start);
	Level(const Level& other) = delete; //Copy constructor afzetten (rule of three)
	Level(Level&& other);
	~Level();

	void Update(float elapsedSec) ;
	void Draw() const ;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	void Respawn();

	Level& operator=(const Level& rhs) = delete; // asignment= operator afzetten
	Level& operator=(Level&& other);

private:
	bool m_IsPaused;
	bool m_TitleScreen;
	const SoundEffect* m_pPauseSound;
	std::vector<std::vector<Point2f>> m_Landscape;
	std::vector<std::vector<Point2f>> m_Platforms;
	Mario* m_pMario;
	Pipe* m_pPipe;
	const Texture* m_pMap;
	int m_CurrLevel;
	Texture* m_pForeground;
	Texture* m_pPipes;
	Texture* m_pTitleScreen;
	Camera* m_pCamera;
	SoundStream* m_pBackgroundMusic;
	SoundStream* m_pTitleMusic;
	TextureManager* m_pTextureManager;
	SoundEffectManager* m_pSoundManager;
	SoundEffect* m_pStartSound;
	EnemyManager* m_pEnemyManager;
	Checkpoint* m_pCheckpoint;
	Finish* m_pFinish;
	Rectf m_VieuwPort;
	std::vector<Coin*> m_pCoins;
	std::vector<PowerUp*> m_pPowerUps;
	std::vector<Block*> m_pBlocks;
};

