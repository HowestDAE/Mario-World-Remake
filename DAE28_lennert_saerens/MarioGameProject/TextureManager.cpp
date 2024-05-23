#include "pch.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
	m_pCoinTexture = new Texture("misc-8.png");
	m_pPowerUpTexture = new Texture("PowerUpBlock.png");
	m_pEnemyTexture = new Texture("misc-3.png");
	m_pCheckpointTexture = new Texture("Checkpoint.png");
	m_pFinishTexture = new Texture("Finish.png");
}

TextureManager::~TextureManager()
{
	delete m_pCoinTexture;
	m_pCoinTexture = nullptr;
	delete m_pPowerUpTexture;
	m_pPowerUpTexture = nullptr;
	delete m_pEnemyTexture;
	m_pEnemyTexture = nullptr;
	delete m_pCheckpointTexture;
	m_pCheckpointTexture = nullptr;
	delete m_pFinishTexture;
	m_pFinishTexture = nullptr;
}


TextureManager::TextureManager(TextureManager&& other) 
	:m_pCoinTexture{ std::move(other.m_pCoinTexture) }
	,m_pPowerUpTexture{std::move(other.m_pCoinTexture)}
{
	other.m_pCoinTexture = nullptr;
	other.m_pPowerUpTexture = nullptr;
}

Texture* TextureManager::GiveTexture(const Textures& tex)
{
	if (tex == Textures::coins) return m_pCoinTexture;
	else if (tex == Textures::PowerUp) return m_pPowerUpTexture;
	else if (tex == Textures::Enemies) return m_pEnemyTexture;
	else if (tex == Textures::Checkpoint) return m_pCheckpointTexture;
	else if (tex == Textures::block) return m_pCoinTexture;
	else if (tex == Textures::Finish) return m_pFinishTexture;
}


TextureManager& TextureManager::operator=(TextureManager&& other)
{
	if (&other != this)
	{
		m_pCoinTexture = std::move(other.m_pCoinTexture);
		m_pPowerUpTexture = std::move(other.m_pPowerUpTexture);

		other.m_pCoinTexture = nullptr;
		other.m_pPowerUpTexture = nullptr;
	}

	return *this;
}
