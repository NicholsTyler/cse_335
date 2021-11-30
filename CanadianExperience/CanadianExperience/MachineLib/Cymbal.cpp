/**
 * \file Cymbal.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "Cymbal.h"

using namespace std;
using namespace Gdiplus;

/// File name for the cymbal stand
const std::wstring CymbalStandFilename = L"images/cymbal-stand.png";

/// File name for the cymbal image
const std::wstring CymbalFileName = L"images/cymbal.png";

/// Offset to the center of the cymbal from the left in pixels
const int CymbalCenterX = 57;

/// Offset to the center of the cymbal from the bottom in pixels
const int CymbalCenterY = 36;

/// X Location to place the cymbal relative to the stand
const int CymbalPlaceX = 0;

/// Y location to place the cymbal relative to the stand
const double CymbalPlaceY = -205;

/// How long the rocking lasts in seconds
const double RockingTime = 2.0;

/// Maximum amount to rock in unit rotations
const double RockAmount = 0.03;

/// How quickly to rock in radians per second
const double RockRate = M_PI * 4;

CCymbal::CCymbal()
{
    mStand.SetImage(CymbalStandFilename);
    mStand.Rectangle(-mStand.GetImageWidth() / 2, 0);

    mCymbal.SetImage(CymbalFileName);
    mCymbal.Rectangle(-mCymbal.GetImageWidth() / 2, 0);
    mCymbal.SetRotation(0);

    mRockTimeRem = 0;
}

/**
* Draws the polygons associated with this cymbal
* \param graphics The graphics to draw with
* \param pos The position to draw at
*/
void CCymbal::Draw(Graphics* graphics, Point pos)
{
    Point cPos = GetPosition();
    int posX = cPos.X + pos.X;
    int posY = cPos.Y + pos.Y;

    mStand.DrawPolygon(graphics, posX, posY);

    // Handles the rocking
    if (mRockTimeRem > 0)
    {
        double rockRatio = mRockTimeRem / RockingTime;
        double rockPos = cos(RockRate * rockRatio);
        mCymbal.SetRotation(-rockPos * RockAmount * rockRatio);
        mRockTimeRem -= 0.1;
    }

    mCymbal.DrawPolygon(graphics, posX + CymbalPlaceX, posY + CymbalPlaceY + CymbalCenterY);
}

/**
* Sets the pressure for this shape
* \param pressure The pressure to set shape to
*/
void CCymbal::SetMotion(double pressure)
{
    CShape::SetMotion(pressure);

    if (pressure == 1 && GetLastPressure() == 1)
    {
        mRockTimeRem = RockingTime;
    }
}
