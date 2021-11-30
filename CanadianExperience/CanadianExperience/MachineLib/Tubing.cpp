/**
 * \file Tubing.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "Tubing.h"
#include "Clamp.h"

using namespace std;
using namespace Gdiplus;

/**
* Adds a clamp for this tubing
* \param x The x position of this clamp
* \param y The y position of this clamp
* \param rotation The rotation of this clamp
* \param speed The speed of this clamp
*/
void CTubing::AddClamp(int x, int y, double rotation, int speed)
{
	auto clamp = make_shared<CClamp>(x, y, rotation, speed);
	mClamps.push_back(clamp);
}

/**
* Virtual function to draw each component
* \param graphics The graphics to draw with
* \param pos The position to draw at
*/
void CTubing::Draw(Graphics* graphics, Point pos)
{
	/* Tube smoothing */
	auto saveSM = graphics->GetSmoothingMode();
	graphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);
	/* Tube smoothing */

	Pen pen(Color::Black, 3);			// Create Pen

	auto source = mSink.GetSource();	// Where to draw from
	auto sink   = mSource.GetSink();	// Where to draw to

	Point cPos = GetPosition();			// Position of the machine
	int posX   = cPos.X + pos.X;		// Machine pos(x) + param pos(x)
	int posY   = cPos.Y + pos.Y;		// Machine pos(y) + param pos(y)

	vector<CTubingPoint*> points;		// Vector of points for bezier curve
	points.push_back(source);			// Add source to vector
	for (auto clamp : mClamps)			// Add clamps to vector
		{ points.push_back(clamp.get()); }
	points.push_back(sink);				// Add sink to vector
	int size = points.size();			// The size of points vector

	// Iterate through all points
	for (int i=0; i < size-1; i++)
	{
		// The current point
		auto pointOne = points[i];
		auto posOne = pointOne->GetPosition();
		auto rotOne = pointOne->GetRotation();
		auto spdOne = pointOne->GetSpeed();

		// The next point
		auto pointTwo = points[i+1];
		auto posTwo = pointTwo->GetPosition();
		auto rotTwo = pointTwo->GetRotation();
		auto spdTwo = pointTwo->GetSpeed();

		if (i + 2 >= size - 1)
		{
			spdTwo *= -1;
			rotTwo *= -1;
		}

		// Point 1
		auto p1x = posOne.X + posX;
		auto p1y = posOne.Y + posY;

		// Point 4
		auto p4x = posTwo.X + posX;
		auto p4y = posTwo.Y + posY;

		// Point 2
		auto p2x = int(p1x - sin(rotOne * M_PI * 2) * spdOne + mAirPressure);
		auto p2y = int(p1y + cos(rotOne * M_PI * 2) * spdOne + mAirPressure);

		// Point 3
		auto p3x = int(p4x - sin(rotTwo * M_PI * 2) * -spdTwo + mAirPressure);
		auto p3y = int(p4y + cos(rotTwo * M_PI * 2) * -spdTwo + mAirPressure);
		
		graphics->DrawBezier(&pen, p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y);
	}

	graphics->SetSmoothingMode(saveSM);	// Tube smoothing
}
