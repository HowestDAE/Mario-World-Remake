#include "pch.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
	m_pCoinTexture = new Texture("misc-8.png");
	m_pPowerUpTexture = new Texture("PowerUpBlock.png");
}

TextureManager::~TextureManager()
{
	delete m_pCoinTexture;
	m_pCoinTexture = nullptr;
	delete m_pPowerUpTexture;
	m_pPowerUpTexture = nullptr;
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
