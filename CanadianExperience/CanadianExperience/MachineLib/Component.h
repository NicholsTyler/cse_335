/**
 * \file Component.h
 *
 * \author Tyler Nichols
 *
 * Base class for all components
 */

#pragma once

#include <gdiplus.h>

 /**
  * A base class for all components
  */
class CComponent
{
public:
    /// Constructor
    CComponent() {}

    /// Destructor
    virtual ~CComponent() {}

    /// Copy constructor/disabled
    CComponent(const CComponent&) = delete;

    /// Assignment operator/disabled
    void operator=(const CComponent&) = delete;

    /**
    * Virtual function to draw each component
    * \param graphics The graphics to draw with
    * \param pos The position to draw at
    */
    virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos) { }

    /**
    * Set the position of the component
    * \param x The x position
    * \param y The y position
    */
    virtual void SetPosition(int x, int y) { mPosition.X = x; mPosition.Y = y; }

    /**
    * Get the position of the component
    * \return The position
    */
    Gdiplus::Point GetPosition() { return mPosition; }

    /**
    * Get the x position of the component
    * \return The x position
    */
    int GetX() { return mPosition.X; }

    /**
    * Get the y position of the component
    * \return The y position
    */
    int GetY() { return mPosition.Y; }

    /**
    * Set the time of the component
    * \param time The time
    */
    virtual void SetTime(double time) { mTime = time; }

private:
	Gdiplus::Point mPosition;    ///< The component's position
    double mTime = 0;            ///< The component's time
};

