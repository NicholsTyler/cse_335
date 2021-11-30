/**
 * \file TubingPoint.h
 *
 * \author Tyler Nichols
 *
 * A class for creating tubing points
 *
 */

#pragma once

#include <gdiplus.h>

 /**
  * A class to create tubing points
  */
class CTubingPoint
{
public:
    /// Constructor
    CTubingPoint() {}

    /// Destructor
    virtual ~CTubingPoint() {}

    /// Copy constructor (disabled)
    CTubingPoint(const CTubingPoint&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CTubingPoint&) = delete;

    /**
    * Get this tubing point's position 
    * \return The position
    */
    Gdiplus::Point GetPosition() { return mLocation; }

    /**
    * Set this tubing point's position
    * \param x The x position
    * \param y The y position
    */
    void SetPosition(int x, int y) { mLocation = Gdiplus::Point(x,y); }

    /**
    * Get this tubing point's rotation
    * \return The rotation
    */
    double GetRotation() { return mRotation; }

    /**
    * Set this tubing point's rotation
    * \param rot The rotation
    */
    void SetRotation(double rot) { mRotation = rot; }

    /**
    * Get this tubing point's speed
    * \return The speed
    */
    double GetSpeed() { return mSpeed; }

    /**
    * Set this tubing point's speed
    * \param speed The speed
    */
    void SetSpeed(double speed) { mSpeed = speed; }

private:
    Gdiplus::Point mLocation = Gdiplus::Point(0, 0); ///< This tubing point's position
	double mRotation = 0;	///< This tubing point's rotation
	double mSpeed = 100;	///< This tubing point's speed
};

