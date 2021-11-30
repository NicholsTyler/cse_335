/**
 * \file Clamp.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "Clamp.h"

 /**
 * Constructor
 * \param x The x position
 * \param y The y position
 * \param rot The rotation
 * \param speed The speed
 */
CClamp::CClamp(int x, int y, double rot, int speed)
{
	SetPosition(x, y);
	SetRotation(rot);
	SetSpeed(speed);
}