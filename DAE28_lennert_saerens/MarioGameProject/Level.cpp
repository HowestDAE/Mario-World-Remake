#include "pch.h"
#include "Level.h"
#include "Game.h"
#include "Mario.h"
#include "Camera.h"
#include "SVGParser.h"
#include "Matrix2x3.h"
#include "Coin.h"
#include "DragonCoin.h"
#include "TextureManager.h"
#include "SoundEffectManager.h"
#include "PowerUp.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Checkpoint.h"
#include "Block.h"
#include "QBlock.h"
#include "Finish.h"
#include "Pipe.h"

Level::Level(int levelNr, const Texture* levelTex, const std::vector<std::vector<Point2f>> landscape, const std::vector<std::vector<Point2f>> platforms, const Rectf vieuwPort, Mario* mario, bool start)
{
	m_VieuwPort = vieuwPort;
	m_pTextureManager = new TextureManager();
	m_pSoundManager = new SoundEffectManager();
	m_IsPaused = start;
	m_TitleScreen = start;
	m_pPauseSound = m_pSoundManager->GiveSound(SoundEffectManager::Sounds::pause);
	m_Landscape = landscape;
	m_Platforms = platforms;
	m_pMario = mario;
	m_pMap = levelTex;
	m_pCamera = new Camera(vieuwPort.width, vieuwPort.height);
	m_pEnemyManager = new EnemyManager(m_pTextureManager->GiveTexture(TextureManager::Textures::Enemies));
	m_CurrLevel = levelNr;


	

	if (levelNr == 1)
	{
		m_pBackgroundMusic = new SoundStream("Sounds/12. Overworld.mp3");
		m_pTitleMusic = new SoundStream("Sounds/04. Wandering the Plains.mp3");
		m_pForeground = new Texture("Level1.png");
		m_pPipes = new Texture("Pipes.png");
		m_pTitleScreen = new Texture("TitleScreen.png");
		m_pStartSound = m_pSoundManager->GiveSound(SoundEffectManager::Sounds::cannon);


		m_pCoins.push_back(new Coin(Point2f(100, 250), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		m_pCoins.push_back(new Coin(Point2f(125, 250), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		m_pCoins.push_back(new Coin(Point2f(150, 250), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		m_pCoins.push_back(new DragonCoin(Point2f(279 * 2, 161 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));
		m_pCoins.push_back(new DragonCoin(Point2f(1416 * 2, 161 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));
		m_pCoins.push_back(new DragonCoin(Point2f(2871 * 2, 193 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));
		m_pCoins.push_back(new DragonCoin(Point2f(4615 * 2, 161 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));

		m_pPowerUps.push_back(new PowerUp(PowerUp::PowerUpType::Flower, Point2f(589 * 2, 98 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::PowerUp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::PowerUp), false));
		m_pPowerUps.push_back(new PowerUp(*m_pMario, Point2f(3888 * 2, 144 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::PowerUp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::PowerUp), false));

		m_pEnemyManager->PushBackEnemy(Point2f(528 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(748 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(875 * 2, 128 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(1148 * 2, 112 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(1308 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(1420 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(1788 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(2204 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(2748 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(2908 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(2940 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(2972 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(3020 * 2, 80 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(3308 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(3868 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(4108 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(4204 * 2, 48 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(4636 * 2, 96 * 2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));

		m_pEnemyManager->PushBackEnemy(Point2f(492 * 2, 64 * 2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(3228 * 2, 48 * 2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(3612 * 2, 48 * 2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
		m_pEnemyManager->PushBackEnemy(Point2f(4460 * 2, 48 * 2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));

		m_pEnemyManager->PushBackEnemy(Point2f(1816 * 2, 70 * 2), EnemyManager::EnemyType::PianhaPlant, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::spinStomp));
		m_pEnemyManager->PushBackEnemy(Point2f(4552 * 2, 70 * 2), EnemyManager::EnemyType::PianhaPlant, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::spinStomp));
		m_pEnemyManager->PushBackEnemy(Point2f(2232 * 2, 88 * 2), EnemyManager::EnemyType::PianhaPlant, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::spinStomp));

		m_pEnemyManager->PushBackEnemy(Point2f(4761 * 2, 52 * 2), EnemyManager::EnemyType::Chuck, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Clap));

		m_pEnemyManager->PushBackEnemy(Point2f(207 * 2, 144 * 2), EnemyManager::EnemyType::Koopa, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));

		m_pPipe = new Pipe(Point2f(1920 * 2, 48 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::pipeHit), Pipe::state::vertical, false);
		m_pCheckpoint = new Checkpoint(Point2f(2408 * 2, 49 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::Checkpoint), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::CheckPoint));
		m_pFinish = new Finish(Point2f(4816 * 2, 49 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::Finish), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::CheckPoint));

		m_pBlocks.push_back(new Block(Point2f(1920 * 2, 96 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
		m_pBlocks.push_back(new Block(Point2f(1936 * 2, 96 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
		m_pBlocks.push_back(new Block(Point2f(3344 * 2, 178 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
		m_pBlocks.push_back(new Block(Point2f(3824 * 2, 96 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
		m_pBlocks.push_back(new Block(Point2f(3888 * 2, 80 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
		m_pBlocks.push_back(new Block(Point2f(3952 * 2, 96 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));

		m_pBlocks.push_back(new QBlock(Point2f(589 * 2, 98 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block), m_pPowerUps[0]));
		m_pBlocks.push_back(new QBlock(Point2f(3888 * 2, 144 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block), m_pPowerUps[1]));
	
	}
	else if (levelNr == 2)
	{
		m_pBackgroundMusic = new SoundStream("Sounds/20. Underground.mp3");
		m_pTitleMusic = nullptr;
		m_pForeground = nullptr;
		m_pPipes = nullptr;
		m_pTitleScreen = nullptr;
		m_pStartSound = m_pSoundManager->GiveSound(SoundEffectManager::Sounds::pipeHit);

		m_pBlocks.push_back(new Block(Point2f(336 * 2, 88 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
		m_pBlocks.push_back(new Block(Point2f(352 * 2, 88 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
		m_pBlocks.push_back(new Block(Point2f(368 * 2, 88 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));

		m_pCoins.push_back(new Coin(Point2f(120*2, 79*2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		m_pCoins.push_back(new Coin(Point2f(136*2, 79 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		m_pCoins.push_back(new Coin(Point2f(152*2, 79 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		
		m_pCoins.push_back(new Coin(Point2f(216*2, 111*2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		m_pCoins.push_back(new Coin(Point2f(232*2, 111 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
		m_pCoins.push_back(new Coin(Point2f(248*2, 111 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
	
		m_pCoins.push_back(new DragonCoin(Point2f(360 * 2, 55 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));

		m_pPipe = new Pipe(Point2f(448 * 2, 40 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::pipeHit), Pipe::state::horizontal, false);

	}

	if (m_TitleScreen == true)
	{
		m_pTitleMusic->Play(true);
	}
	else
	{
		(m_pBackgroundMusic->Play(true));
		m_pStartSound->Play(0);
	}
}

Level::Level(Level&& other)
	:m_Landscape{other.m_Landscape}
	,m_pBackgroundMusic{other.m_pBackgroundMusic}
	,m_pBlocks{other.m_pBlocks}
	,m_pCamera{other.m_pCamera}
	,m_pCheckpoint{other.m_pCheckpoint}
	,m_pCoins{other.m_pCoins}
	, m_pEnemyManager{ other.m_pEnemyManager }
	, m_pFinish{ other.m_pFinish }
	,m_pForeground{other.m_pForeground}
	,m_Platforms{other.m_Platforms}
	,m_pMap{other.m_pMap}
	,m_pMario{other.m_pMario}
	,m_pPipes{other.m_pPipes}
	,m_pPowerUps{other.m_pPowerUps}
	,m_pSoundManager{ other.m_pSoundManager }
	,m_pTextureManager{other.m_pTextureManager}
	,m_VieuwPort{other.m_VieuwPort}
{
	other.m_pBackgroundMusic = nullptr;
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		other.m_pBlocks[idx] = nullptr;
	}
	other.m_pCamera = nullptr;
	other.m_pCheckpoint = nullptr;
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		other.m_pCoins[idx] = nullptr;
	}
	m_pEnemyManager = nullptr;
	m_pFinish = nullptr;
	m_pForeground = nullptr;
}

Level::~Level()
{
	delete m_pTextureManager;
	m_pTextureManager = nullptr;
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	
	if (m_CurrLevel == 1)
	{
		delete m_pForeground;
		m_pForeground = nullptr;
		delete m_pPipes;
		m_pPipes = nullptr;
		delete m_pCheckpoint;
		m_pCheckpoint = nullptr;
		delete m_pFinish;
		m_pFinish = nullptr;
		delete m_pTitleScreen;
		m_pTitleScreen = nullptr;
		for (int idx{}; idx < m_pPowerUps.size(); ++idx)
		{
			delete m_pPowerUps[idx];
			m_pPowerUps[idx] = nullptr;
		}
		delete m_pTitleMusic;
		m_pTitleMusic = nullptr;
	}
	
	delete m_pCamera;
	m_pCamera = nullptr;
	delete m_pBackgroundMusic;
	m_pBackgroundMusic = nullptr;
	
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		delete m_pCoins[idx];
		m_pCoins[idx] = nullptr;
	}
	
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		delete m_pBlocks[idx];
		m_pBlocks[idx] = nullptr;
	}
	delete m_pPipe;
	m_pPipe = nullptr;
	delete m_pEnemyManager;
	m_pEnemyManager = nullptr;
	
}

void Level::Update(float elapsedSec)
{
	if (!m_IsPaused)
	{
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if (m_pMario->GetLevelClear())
		{
			Respawn();
			m_pMario->SetLevelClear(false);
			m_TitleScreen = true;
			m_IsPaused = true;
			m_pBackgroundMusic->Stop();
			m_pTitleMusic->Play(1);
		}

		m_pMario->HandleMovement(elapsedSec, pStates);
		m_pMario->Update(elapsedSec, m_Landscape, m_Platforms, m_pBlocks);
		if (m_pCoins[0] != nullptr)
		{
			m_pCoins[0]->Update(elapsedSec);
		}
		for (int idx{}; idx < m_pCoins.size(); ++idx)
		{
			m_pCoins[idx]->Animate();
			m_pCoins[idx]->Collect(m_pMario);
		}
		if (m_CurrLevel == 1)
		{
			for (int idx{}; idx < m_pPowerUps.size(); ++idx)
			{
				m_pPowerUps[idx]->Update(elapsedSec, m_Landscape, m_Platforms, m_pBlocks);
				if (m_pPowerUps[idx]->Collect(m_pMario))
				{
					m_pMario->Grow(m_pPowerUps[idx]->GetPowerUpType());
				}
			}
			m_pEnemyManager->Update(elapsedSec, m_Landscape, m_Platforms, m_pMario);
			m_pCheckpoint->Update();
			m_pCheckpoint->CheckIsHit(m_pMario);
			m_pFinish->Update(elapsedSec);
			m_pFinish->CheckIsHit(m_pMario);
			if (m_pMario->GetFinishHit())
			{
				m_pBackgroundMusic->Stop();
			}
		}
		for (int idx{}; idx < m_pBlocks.size(); ++idx)
		{
			m_pBlocks[idx]->Update(elapsedSec, m_Landscape, m_Platforms, m_pBlocks);
			
		}
		
		if (m_pMario->GetIsAlive() == false)
		{
			m_pBackgroundMusic->Stop();
			if (m_pMario->GetPos().y <= -5000.f)
			{
				Respawn();
			}
		}
		
		/*else if (m_pBackgroundMusic->IsPlaying() == false)
		{
			m_pBackgroundMusic->Play(1);
		}*/
		m_pPipe->Update(elapsedSec, m_pMario);

	}
	if (m_TitleScreen)
	{
		m_pMario->AnimateTitle(elapsedSec);
	}
}

void Level::Draw() const
{
	/*glPushMatrix();
	glScalef(2.f, 2.f, 0.f);*/
	m_pCamera->Aim(m_pMap->GetWidth() * 2, m_pMap->GetHeight() * 2, m_pMario->GetPos());
	m_pMap->Draw(Rectf(0, 0, m_pMap->GetWidth() * 2, m_pMap->GetHeight() * 2));
	if (m_CurrLevel == 1)
	{
		m_pForeground->Draw(Rectf(0, 0, m_pForeground->GetWidth() * 2, m_pForeground->GetHeight() * 2));
		for (int idx{}; idx < m_pPowerUps.size(); ++idx)
		{
			m_pPowerUps[idx]->Draw();
		}
		m_pCheckpoint->Draw();
		m_pEnemyManager->Draw();
		m_pPipes->Draw(Rectf(0, 0, m_pPipes->GetWidth() * 2, m_pPipes->GetHeight() * 2));
		m_pFinish->Draw();
	}
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		m_pCoins[idx]->Draw();
	}
	
	/*utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	for (int idx{}; idx < m_Landscape.size(); ++idx)
	{
		utils::DrawPolygon(m_Landscape[idx]);
	}
	for (int idx{}; idx < m_Platforms.size(); ++idx)
	{
		utils::DrawPolygon(m_Platforms[idx]);
	}*/
	
	m_pMario->Draw();
	m_pPipe->Draw();
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		m_pBlocks[idx]->Draw();
		m_pBlocks[idx]->CheckHit(m_pMario);
	}
	//utils::DrawRect(m_pMario->GetBounds());
	m_pCamera->Reset();
	//glPopMatrix();
	if (m_TitleScreen)
	{
		m_pTitleScreen->Draw();
		m_pMario->Draw();

	}
	else if (m_IsPaused)
	{
		utils::SetColor(Color4f(0.3, 0.3, 0.3, 0.3));
		utils::FillRect(m_VieuwPort);
		std::string pausedString{ "Paused" };
		Texture pausedTexture{pausedString, "Super-Mario-World.ttf", 80, Color4f(0.f, 0.f, 0.f, 1.f) };
		pausedTexture.Draw(Rectf(m_VieuwPort.width / 2 - pausedTexture.GetWidth() / 2, m_VieuwPort.height / 2 - pausedTexture.GetHeight() / 2, pausedTexture.GetWidth(), pausedTexture.GetHeight()));
	}
}

void Level::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	m_pMario->OnKeyDownEvent(e);

}

void Level::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	m_pMario->OnKeyUpEvent(e);
	if (m_TitleScreen == false)
	{
		switch (e.keysym.sym)
		{
		case SDLK_ESCAPE:
			m_IsPaused = !m_IsPaused;
			m_pPauseSound->Play(0);
			if (m_IsPaused == true)
			{
				m_pBackgroundMusic->Pause();
			}
			else
			{
				m_pBackgroundMusic->Resume();
			}
			break;
		}
	}
	else
	{
		if (m_TitleScreen == true)
		{
			switch (e.keysym.sym)
			{
			case SDLK_SPACE:
				m_TitleScreen = false;
				m_IsPaused = false;
				m_pTitleMusic->Stop();
				m_pBackgroundMusic->Play(true);
				break;
			}
		}
	}
	

}

void Level::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Level::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Level::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Level::Respawn()
{
	m_pEnemyManager->Reset();
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		m_pCoins[idx]->Reset();
	}
	for (int idx{}; idx < m_pPowerUps.size(); ++idx)
	{
		m_pPowerUps[idx]->Reset();
	}
	m_pMario->Reset();
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		m_pBlocks[idx]->Reset();
	}
	m_pBackgroundMusic->Play(1);
}

Level& Level::operator=(Level&& other)
{
	m_Landscape = other.m_Landscape;
	m_pBackgroundMusic= other.m_pBackgroundMusic;
	m_pBlocks= other.m_pBlocks;
	m_pCamera= other.m_pCamera;
	m_pCheckpoint= other.m_pCheckpoint;
	m_pCoins= other.m_pCoins;
	m_pEnemyManager= other.m_pEnemyManager;
	m_pFinish= other.m_pFinish;
	m_pForeground= other.m_pForeground;
	m_Platforms= other.m_Platforms;
	m_pMap= other.m_pMap;
	m_pMario= other.m_pMario;
	m_pPipes= other.m_pPipes;
	m_pPowerUps= other.m_pPowerUps;
	m_pSoundManager= other.m_pSoundManager;
	m_pTextureManager= other.m_pTextureManager;
	m_VieuwPort= other.m_VieuwPort;
	
	other.m_pBackgroundMusic = nullptr;
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		other.m_pBlocks[idx] = nullptr;
	}
	other.m_pCamera = nullptr;
	other.m_pCheckpoint = nullptr;
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		other.m_pCoins[idx] = nullptr;
	}
	m_pEnemyManager = nullptr;
	m_pFinish = nullptr;
	m_pForeground = nullptr;
	return *this;
}
