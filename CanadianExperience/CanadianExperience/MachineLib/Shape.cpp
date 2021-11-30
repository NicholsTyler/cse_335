/**
 * \file Shape.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "Shape.h"

using namespace Gdiplus;

CShape::CShape()
{
    // Set up the motion sink
    mSink.SetComponent(this);
}

/**
* Draws the polygon associated with this shape
* \param graphics The graphics to draw with
* \param pos The position to draw at
*/
void CShape::Draw(Graphics* graphics, Point pos)
{
	Point cPos = GetPosition();
	int posX = cPos.X + pos.X;
	int posY = cPos.Y + pos.Y;

    mImage.DrawPolygon(graphics, posX, posY);
}

/**
* Sets the pressure for this shape
* \param pressure The pressure to set shape to
*/
void CShape::SetMotion(double pressure)
{
    if (pressure == 1 && mLastPressure < 1)
    {
        mLastPressure = 1;
        wC->Play();
    }
    else
    {
        mLastPressure = pressure;
    }
}
