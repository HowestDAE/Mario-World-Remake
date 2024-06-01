#pragma once
#include "BaseGame.h"
#include <vector>
#include "Texture.h"
#include "Level.h"

//#include <vector>
//#include "Texture.h"
//#include "SoundStream.h"
//
//class Mario;
//class Camera;
//class Coin;
//class Enemy;
//class TextureManager;
//class SoundEffectManager;
//class PowerUp;
//class EnemyManager;
//class Checkpoint;
//class Block;
//class Finish;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	/*
	Texture* m_pForeground;
	Texture* m_pPipes;
	Camera* m_pCamera;
	SoundStream* m_pBackgroundMusic;
	TextureManager* m_pTextureManager;
	SoundEffectManager* m_pSoundManager;
	EnemyManager* m_pEnemyManager;
	Checkpoint* m_pCheckpoint;
	Finish* m_pFinish;
	std::vector<Coin*> m_pCoins;
	std::vector<PowerUp*> m_pPowerUps;
	std::vector<Block*> m_pBlocks;*/
	Mario* m_pMario;
	std::vector<std::vector<Point2f>> m_Landscape;
	std::vector<std::vector<Point2f>> m_Platforms;
	Texture* m_pMap;
	Level* m_pLevel;
	

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};