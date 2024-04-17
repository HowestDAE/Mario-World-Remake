#include "pch.h"
#include "Game.h"
#include "Mario.h"
#include "Camera.h"
#include "SVGParser.h"
#include "Matrix2x3.h"
#include "Coin.h"

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
	m_pBackgroundMusic = new SoundStream("Sounds/12. Overworld.mp3");
	m_pBackgroundMusic->Play(true);
	m_pMario = new Mario(Point2f(50, 200));
	m_pMap = new Texture("yoshis-island-1-top no enemies.png");
	m_pCamera = new Camera(GetViewPort().width, GetViewPort().height);
	SVGParser::GetVerticesFromSvgFile("yoshis-island-1-top.svg", m_Landscape);
	for (int idx{}; idx < m_Landscape.size(); ++idx)
	{
		for (int i{}; i < m_Landscape[idx].size(); ++i)
		{
			m_Landscape[idx][i].x;
			m_Landscape[idx][i].y;
		}
	}

	Matrix2x3 scaleMat{};
	scaleMat.SetAsScale(2.f);

	for (int idx{}; idx < m_Landscape.size(); ++idx)
	{
		Matrix2x3 transformMatrix{ scaleMat };
		m_Landscape[idx] = transformMatrix.Transform(m_Landscape[idx]);
	}
	
	m_pCoins.push_back(new Coin(Point2f(100, 250)));
	m_pCoins.push_back(new Coin(Point2f(125, 250)));
	m_pCoins.push_back(new Coin(Point2f(150, 250)));
	m_pCoins.push_back(new DragonCoin(Point2f(279*2, 161*2)));
}

void Game::Cleanup( )
{
	delete m_pMario;
	m_pMario = nullptr;
	delete m_pMap;
	m_pMap = nullptr;
	delete m_pCamera;
	m_pCamera = nullptr;
	delete m_pBackgroundMusic;
	m_pBackgroundMusic = nullptr;
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		delete m_pCoins[idx];
		m_pCoins[idx] = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_pMario->HandleMovement(elapsedSec, pStates);
	m_pMario->Update(elapsedSec,m_Landscape);

	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		m_pCoins[idx]->Update(elapsedSec);
		m_pCoins[idx]->Collect(m_pMario);
	}
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
	m_pMario->Draw();
	for (int idx{}; idx < m_pCoins.size(); ++idx)
	{
		m_pCoins[idx]->Draw();
	}
	m_pCamera->Reset();
	//glPopMatrix();
	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
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
