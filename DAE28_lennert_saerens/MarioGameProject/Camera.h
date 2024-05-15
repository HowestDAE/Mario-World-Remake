#pragma once
class Camera final
{
public:
	explicit Camera(float screenWidth, float screenHeight);
	void Aim(float levelW, float levelH,const Point2f& trackCenter) const;
	Point2f Reset();
private:
	float m_ScreenWidth;
	float m_ScreenHeight;
};

