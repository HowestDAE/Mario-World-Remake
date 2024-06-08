#pragma once
#include "Texture.h"
#include "SoundEffect.h"
#include <vector>

class Mario;

class Pipe final
{
public:
	enum class state
	{
		horizontal,
		vertical,
	};

	explicit Pipe(const Point2f& startingPos, const Texture* tex, const SoundEffect* sound, const state& state, const bool& mirrored) noexcept;
	void Update(float elapsedSec, Mario* mario) noexcept;
	void Draw() const noexcept;

	static bool m_Sublevel;

private:
	Point2f m_Pos;
	Rectf m_Bounds;
	Rectf m_SrcRect;
	const Texture* m_pTexture;
	const SoundEffect* m_pSoundEffect;
	bool m_Mirrored;
	bool m_GoingDown;
	bool m_GoingIn;
	state m_State;
};

