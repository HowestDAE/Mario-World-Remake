#include "pch.h"
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


Game::Game(const Window& window)
	:BaseGame{ window }
{
	Initialize();
	
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	//std::vector<Point2f> platformOne{ Point2f(0, 50), Point2f(5000, 50) };
	//m_Landscape.push_back(platformOne);
	m_pTextureManager = new TextureManager();
	m_pSoundManager = new SoundEffectManager();
	m_pBackgroundMusic = new SoundStream("Sounds/12. Overworld.mp3");
	m_pBackgroundMusic->Play(true);
	m_pMario = new Mario(Point2f(50, 200), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::pipeHit));
	m_pMap = new Texture("yoshis-island-1-top no enemies.png");
	m_pForeground = new Texture("Level1.png");
	m_pPipes = new Texture("Pipes.png");
	m_pCamera = new Camera(GetViewPort().width, GetViewPort().height);
	m_pEnemyManager = new EnemyManager(m_pTextureManager->GiveTexture(TextureManager::Textures::Enemies));
	SVGParser::GetVerticesFromSvgFile("yoshis-island-1-top-NoLag.svg", m_Landscape);
	SVGParser::GetVerticesFromSvgFile("yoshis-island-1-top-Platforms.svg", m_Platforms);
	for (int idx{}; idx < m_Landscape.size(); ++idx)
	{
		utils::DrawPolygon(m_Landscape[idx]);
	}

	Matrix2x3 scaleMat{};
	scaleMat.SetAsScale(2.f);

	for (int idx{}; idx < m_Landscape.size(); ++idx)
	{
		Matrix2x3 transformMatrix{ scaleMat };
		m_Landscape[idx] = transformMatrix.Transform(m_Landscape[idx]);
	}
	for (int idx{}; idx < m_Platforms.size(); ++idx)
	{
		Matrix2x3 transformMatrix{ scaleMat };
		m_Platforms[idx] = transformMatrix.Transform(m_Platforms[idx]);
	}
	
	m_pCoins.push_back(new Coin(Point2f(100, 250),m_pTextureManager->GiveTexture(TextureManager::Textures::coins),m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
	m_pCoins.push_back(new Coin(Point2f(125, 250), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
	m_pCoins.push_back(new Coin(Point2f(150, 250), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::coins)));
	m_pCoins.push_back(new DragonCoin(Point2f(279*2, 161*2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));
	m_pCoins.push_back(new DragonCoin(Point2f(1416 * 2, 161 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));
	m_pCoins.push_back(new DragonCoin(Point2f(2871*2, 193*2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));
	m_pCoins.push_back(new DragonCoin(Point2f(4615*2, 161*2), m_pTextureManager->GiveTexture(TextureManager::Textures::coins), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::dragonCoins)));

	m_pPowerUps.push_back(new PowerUp(PowerUp::PowerUpType::Flower, Point2f(589 * 2, 98 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::PowerUp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::PowerUp), false));
	m_pPowerUps.push_back(new PowerUp(*m_pMario, Point2f(3888 * 2, 144 * 2),m_pTextureManager->GiveTexture(TextureManager::Textures::PowerUp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::PowerUp),false));

	m_pEnemyManager->PushBackEnemy(Point2f(528*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(748*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(875*2, 128*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(1148*2, 112*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(1308*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(1420*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(1788*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(2204*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(2748*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(2908*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(2940*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(2972*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(3020*2, 80*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(3308*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(3868*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(4108*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(4204*2, 48*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(4636*2, 96*2), EnemyManager::EnemyType::Enemy, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));

	m_pEnemyManager->PushBackEnemy(Point2f(492*2, 64*2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(3228*2, 48*2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(3612*2, 48*2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	m_pEnemyManager->PushBackEnemy(Point2f(4460*2, 48*2), EnemyManager::EnemyType::BulletBill, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));

	m_pEnemyManager->PushBackEnemy(Point2f(1816*2, 70*2), EnemyManager::EnemyType::PianhaPlant, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::spinStomp));
	m_pEnemyManager->PushBackEnemy(Point2f(4552*2, 70*2), EnemyManager::EnemyType::PianhaPlant, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::spinStomp));
	m_pEnemyManager->PushBackEnemy(Point2f(2232*2, 88*2), EnemyManager::EnemyType::PianhaPlant, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::spinStomp));

	m_pEnemyManager->PushBackEnemy(Point2f(4761*2, 52*2), EnemyManager::EnemyType::Chuck, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Clap));

	m_pEnemyManager->PushBackEnemy(Point2f(207*2, 144*2), EnemyManager::EnemyType::Koopa, m_pSoundManager->GiveSound(SoundEffectManager::Sounds::Stomp));
	
	m_pCheckpoint = new Checkpoint(Point2f(2408 * 2, 49 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::Checkpoint), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::CheckPoint));
	m_pFinish = new Finish(Point2f(4816 * 2, 49 * 2), m_pTextureManager->GiveTexture(TextureManager::Textures::Finish), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::CheckPoint));

	m_pBlocks.push_back(new Block(Point2f(1920*2, 96*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
	m_pBlocks.push_back(new Block(Point2f(1936*2, 96*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
	m_pBlocks.push_back(new Block(Point2f(3344*2, 178*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
	m_pBlocks.push_back(new Block(Point2f(3824*2, 96*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
	m_pBlocks.push_back(new Block(Point2f(3888*2, 80*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));
	m_pBlocks.push_back(new Block(Point2f(3952*2, 96*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block)));

	m_pBlocks.push_back(new QBlock(Point2f(589*2, 98*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block),m_pPowerUps[0]));
	m_pBlocks.push_back(new QBlock(Point2f(3888*2, 144*2), m_pTextureManager->GiveTexture(TextureManager::Textures::block), m_pSoundManager->GiveSound(SoundEffectManager::Sounds::block), m_pPowerUps[1]));
}

void Game::Respawn()
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
}

void Game::Cleanup()
{
	delete m_pTextureManager;
	m_pTextureManager = nullptr;
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pMario;
	m_pMario = nullptr;
	delete m_pMap;
	m_pMap = nullptr;
	delete m_pForeground;
	m_pForeground = nullptr;
	delete m_pPipes;
	m_pPipes = nullptr;
	delete m_pCheckpoint;
	m_pCheckpoint = nullptr;
	delete m_pCamera;
	m_pCamera = nullptr;
	delete m_pBackgroundMusic;
	m_pBackgroundMusic = nullptr;
	delete m_pFinish;
	m_pFinish = nullptr;
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		delete m_pCoins[idx];
		m_pCoins[idx] = nullptr;
	}
	for (int idx{}; idx < m_pPowerUps.size(); ++idx)
	{
		delete m_pPowerUps[idx];
		m_pPowerUps[idx] = nullptr;
	}
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		delete m_pBlocks[idx];
		m_pBlocks[idx] = nullptr;
	}

	delete m_pEnemyManager;
	m_pEnemyManager = nullptr;
}

void Game::Update( float elapsedSec )
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_pMario->HandleMovement(elapsedSec, pStates);
	m_pMario->Update(elapsedSec,m_Landscape, m_Platforms);
	if (m_pCoins[0] != nullptr)
	{
		m_pCoins[0]->Update(elapsedSec);
	}
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		m_pCoins[idx]->Animate();
		m_pCoins[idx]->Collect(m_pMario);
	}
	for (int idx{}; idx < m_pPowerUps.size(); ++idx)
	{
		m_pPowerUps[idx]->Update(elapsedSec, m_Landscape, m_Platforms, m_pBlocks);
		if (m_pPowerUps[idx]->Collect(m_pMario))
		{
			m_pMario->Grow(m_pPowerUps[idx]->GetPowerUpType());
		}
	}
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		m_pBlocks[idx]->Update(elapsedSec, m_Landscape,m_Platforms, m_pBlocks);
	}
	m_pEnemyManager->Update(elapsedSec, m_Landscape, m_Platforms, m_pMario);
	m_pCheckpoint->Update();
	m_pCheckpoint->CheckIsHit(m_pMario);
	if (m_pMario->GetIsAlive() == false)
	{
		m_pBackgroundMusic->Stop();
		if (m_pMario->GetPos().y <= -5000.f)
		{
			Respawn();
		}
	}
	else if (m_pBackgroundMusic->IsPlaying() == false)
	{
		m_pBackgroundMusic->Play(1);
	}
	m_pFinish->Update(elapsedSec);
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	/*glPushMatrix();
	glScalef(2.f, 2.f, 0.f);*/
	m_pCamera->Aim(m_pMap->GetWidth()*2, m_pMap->GetHeight()*2, m_pMario->GetPos());
	ClearBackground( );
	m_pMap->Draw(Rectf(0,0,m_pMap->GetWidth()*2,m_pMap->GetHeight()*2));
	m_pForeground->Draw(Rectf(0,0, m_pForeground->GetWidth()*2, m_pForeground->GetHeight()*2));
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		m_pCoins[idx]->Draw();
	}
	for (int idx{}; idx < m_pPowerUps.size(); ++idx)
	{
		m_pPowerUps[idx]->Draw();
	}
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	/*for (int idx{}; idx < m_Landscape.size(); ++idx)
	{
		utils::DrawPolygon(m_Landscape[idx]);
	}*/
	/*for (int idx{}; idx < m_Platforms.size(); ++idx)
	{
		utils::DrawPolygon(m_Platforms[idx]);
	}*/
	m_pCheckpoint->Draw();
	m_pEnemyManager->Draw();
	m_pPipes->Draw(Rectf(0, 0, m_pPipes->GetWidth() * 2, m_pPipes->GetHeight() * 2));
	m_pFinish->Draw();
	m_pMario->Draw();
	for (int idx{}; idx < m_pBlocks.size(); ++idx)
	{
		m_pBlocks[idx]->Draw();
		m_pBlocks[idx]->CheckHit(m_pMario);
	}
	//utils::DrawRect(m_pMario->GetBounds());
	m_pCamera->Reset();
	//glPopMatrix();
	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	m_pMario->OnKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_pMario->OnKeyUpEvent(e);
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
