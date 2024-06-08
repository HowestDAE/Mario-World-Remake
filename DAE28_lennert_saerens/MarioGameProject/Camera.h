#pragma once
class Camera final
{
public:
	explicit Camera(float screenWidth, float screenHeight) noexcept;
	void Aim(float levelW, float levelH,const Point2f& trackCenter) const noexcept;
	Point2f Reset() noexcept;
private:
	float m_ScreenWidth;
	float m_ScreenHeight;
};

