#include "pch.h"
#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight) noexcept
	:m_ScreenWidth{screenWidth}
	,m_ScreenHeight{ screenHeight }
{
}

void Camera::Aim(float levelW, float levelH,const Point2f& trackCenter) const noexcept
{
	Point2f bottomLeft{ trackCenter.x-m_ScreenWidth/2,trackCenter.y-m_ScreenHeight/2 };
	if (bottomLeft.x <0)
	{
		bottomLeft.x = 0;
	}
	if (bottomLeft.y <0)
	{
		bottomLeft.y = 0;
	}	
	if (bottomLeft.x + m_ScreenWidth >levelW)
	{
		bottomLeft.x = levelW - m_ScreenWidth;
	}
	if (bottomLeft.y+m_ScreenHeight > levelH)
	{
		bottomLeft.y = levelH-m_ScreenHeight;
	}

	glPushMatrix();
	glTranslatef(-bottomLeft.x, -bottomLeft.y,0);
}

Point2f Camera::Reset() noexcept
{
	glPopMatrix();
	return Point2f();
}
