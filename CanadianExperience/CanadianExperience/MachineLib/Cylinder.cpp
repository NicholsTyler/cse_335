/**
 * \file Cylinder.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "Cylinder.h"

using namespace std;
using namespace Gdiplus;

/// Cylinder base image
const std::wstring CylinderBaseImage = L"images/cylinder-base.png";

/// Cylinder body image
const std::wstring CylinderBodyImage = L"images/cylinder.png";

/// Cylinder ram image
const std::wstring CylinderRamImage = L"images/cylinder-ram.png";

/// The maximum pixels to move the cylinder ram when enabled
const int CylinderMaxExtent = 44;

/// Angle from bottom center of the cylinder
/// to the tubing connector in rotations
const double ConnectorAngle = -0.17;

/// Distance from bottom center of the cylinder to the tubing connector
const double ConnectorDistance = 24.5;

CCylinder::CCylinder()
{
    mMount.SetImage(CylinderBaseImage);
    mMount.Rectangle(-mMount.GetImageWidth() / 2, 0);

    mCylinder.SetImage(CylinderBodyImage);
    mCylinder.Rectangle(-mCylinder.GetImageWidth() / 2, 0);

    mRam.SetImage(CylinderRamImage);
    mRam.Rectangle(-mCylinder.GetImageWidth() / 2, 0);

    // Set up the air sink
    mSink.SetComponent(this);

    // Set up the motion source
    auto source = make_shared<CMotionSource>();
    mSource = source;

    mExtensionDistance = CylinderMaxExtent;
}

/**
* Draws the cylinder
* \param graphics The graphics to draw with
* \param pos The position to draw at
*/
void CCylinder::Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos)
{
    Point cPos = GetPosition();
    int posX = cPos.X + pos.X;
    int posY = cPos.Y + pos.Y;
    double extension = mRamPos * mExtensionDistance;

    mMount.DrawPolygon(graphics, posX, posY);
    mRam.DrawPolygon(graphics, posX + extension * sin(mRot), posY - extension * cos(mRot));
    mCylinder.DrawPolygon(graphics, posX, posY);
}

/**
* Sets the ram position to the supplied pressure
* \param pressure The pressure to set ram position to
*/
void CCylinder::SetPressure(double pressure)
{ 
    mRamPos = pressure;
    mSource->ApplyForce(pressure);
}

/**
* Sets the rotation of this cylinder
* \param rot The rotation to set cylinder to
*/
void CCylinder::SetRotation(double rot)
{
    mMount.SetRotation(rot);
    mRam.SetRotation(rot);
    mCylinder.SetRotation(rot);
    mSink.SetRotation(rot);
    mRot = DegreeToRadian(rot * 360);

    double airX = GetX();
    double airY = GetY();
    if (rot == 0.5) // Upside Down
    {
        airX -= cos(ConnectorAngle * M_PI * 2) * ConnectorDistance;
        airY -= sin(ConnectorAngle * M_PI * 2) * ConnectorDistance;
    }
    else if (rot == 0.25)   // Right
    {
        airX -= sin(ConnectorAngle * M_PI * 2) * ConnectorDistance;
        airY += cos(ConnectorAngle * M_PI * 2) * ConnectorDistance;
        mSink.SetSpeed(rot);
    }

    mSink.SetPosition((int)airX, (int)airY);
}

/**
* Converts a given degree to radians
* \param degree The degree to convert
* \return The given degree as radians
*/
double CCylinder::DegreeToRadian(double degree)
{
    return (degree * (M_PI / 180));
}

/**
* Sets the position of this cylinder and sink
* \param x The x position
* \param y The y position
*/
void CCylinder::SetPosition(int x, int y)
{
    double airX = x + cos(ConnectorAngle * M_PI * 2) * ConnectorDistance;
    double airY = y + sin(ConnectorAngle * M_PI * 2) * ConnectorDistance;

    CComponent::SetPosition(x, y);
    mSink.SetPosition((int)airX, (int)airY);
}
