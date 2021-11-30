/**
 * \file Clamp.h
 *
 * \author Tyler Nichols
 *
 * A class for creating clamps
 *
 */

#pragma once

#include "TubingPoint.h"

 /**
  * A class to create clamps
  */
class CClamp : public CTubingPoint
{
public:
    /// Constructors
    CClamp() {}
    CClamp(int x, int y, double rot, int speed);

    /// Destructor
    virtual ~CClamp() {}

    /// Copy constructor (disabled)
    CClamp(const CClamp&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CClamp&) = delete;

private:
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);    ///< This clamp's position
};

