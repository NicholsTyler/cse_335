/**
 * \file Chime.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "Chime.h"
#include <string>

using namespace std;
using namespace Gdiplus;

/// The chime hammer mount image
const std::wstring ChimeMountImage = L"images/hammer-mount.png";

/// The chime hammer image
const std::wstring ChimeHammerImage = L"images/hammer.png";

/// The chime itself
const std::wstring ChimeImage = L"images/chime.png";

/// Width to draw the actual chime
const int ChimeWidth = 15;

/// Offset of the Chime relative to the origin
/// of this component X value
const double ChimeOffsetX = -18.0;

/// Offset of the Chime Y value
const double ChimeOffsetY = 5.0;

/// The location in the hammer image for the pivot point X
const double HammerPivotX = 33;

/// The location in the hammer image for the pivot point X
const double HammerPivotY = 10;

/// Amount to rotate hammer away from chime in unit rotations
const double HammerRotation = 0.08;

/**
* Constructor
* \param length The length of the chime
*/
CChime::CChime(int length)
{
    mMountImage.SetImage(ChimeMountImage);
    mMountImage.Rectangle(-mMountImage.GetImageWidth() / 2, mMountImage.GetImageHeight());

    mBaseImage.SetImage(ChimeHammerImage);
    mBaseImage.Rectangle(-HammerPivotX, HammerPivotY);
    mBaseImage.SetRotation(HammerRotation);

    mChimeImage.SetImage(ChimeImage);
    mChimeImage.Rectangle(-ChimeWidth / 2, 0, ChimeWidth, -length);

    // Set up the motion sink
    mSink.SetComponent(this);

    mRotation = HammerRotation;
    mLastPressure = 0;
}

/**
* Draws the chime
* \param graphics The graphics to draw with
* \param pos The position to draw at
*/
void CChime::Draw(Graphics* graphics, Point pos)
{
    Point cPos = GetPosition();
    int posX = cPos.X + pos.X;
    int posY = cPos.Y + pos.Y;

    mMountImage.DrawPolygon(graphics, posX, posY);
    mBaseImage.DrawPolygon(graphics, posX, posY + (double)65);
    mBaseImage.SetRotation(mRotation);
    mChimeImage.DrawPolygon(graphics, posX + ChimeOffsetX, posY + ChimeOffsetY);
}

/**
* Sets the pressure for this chime
* \param pressure The pressure to set chime to
*/
void CChime::SetMotion(double pressure)
{
    if (pressure == 1 && mLastPressure < 1)
    {
        mLastPressure = 1;
        mRotation = pressure;
        wC->Play();
    }
    else
    {
        mLastPressure = pressure;
        mRotation = HammerRotation;
    }
}
