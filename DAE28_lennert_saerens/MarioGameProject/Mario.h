#pragma once
class Mario
{
public:

private:
	enum class state {
		small,
		big,
		fireflower
	};

	Mario(Point2f startingPos, state mariostate);
	~Mario();
	void Update(float elapsedSec);
	void Draw() const;
	void KeyDownEvent(const SDL_KeyboardEvent& e);



};

