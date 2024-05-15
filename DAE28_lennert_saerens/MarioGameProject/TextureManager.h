#pragma once
#include "Texture.h"
class TextureManager final
{
public:
	enum class Textures
	{
		coins,
		PowerUp,
		Enemies,
	};

	TextureManager();
	~TextureManager();
	TextureManager(const TextureManager& other) = delete; //Copy constructor afzetten (rule of three)
	TextureManager(TextureManager&& other);

	Texture* GiveTexture(const Textures& tex);

	TextureManager& operator=(const TextureManager& rhs) = delete; // asignment= operator afzetten
	TextureManager& operator=(TextureManager&& other);
protected:
	Texture* m_pCoinTexture;
	Texture* m_pPowerUpTexture;
	Texture* m_pEnemyTexture;
};

