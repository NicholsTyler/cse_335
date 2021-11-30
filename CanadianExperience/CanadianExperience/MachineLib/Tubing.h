/**
 * \file Tubing.h
 *
 * \author Tyler Nichols
 *
 * A class for creating tubing
 * 
 * Derived from CComponent, and implements AirSinkDestination interface
 *
 */

#pragma once

#include "Component.h"
#include "AirSinkDestination.h"
#include <vector>
#include <memory>
#include <gdiplus.h>
#include "AirSource.h"
#include "AirSink.h"
#include "Clamp.h"

 /**
  * A class to create tubing
  */
class CTubing : public CComponent, public IAirSinkDestination
{
public:
    /// Constructor
    CTubing() { mSink.SetComponent(this); }

    /// Destructor
    virtual ~CTubing() {}

    /// Copy constructor (disabled)
    CTubing(const CTubing&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CTubing&) = delete;

    /**
    * Get this tubing's air source
    * \return Pointer to the air source
    */
	CAirSource* GetSource() { return &mSource; }

    /**
    * Get this tubing's air sink
    * \return Pointer to the air sink
    */
	CAirSink* GetSink() { return &mSink; }

    /**
    * Sets this tubing's pressure
    * \param pressure The pressure to set component to
    */
    virtual void SetPressure(double pressure) override { mSource.SetPressure(pressure); mAirPressure = pressure; }

    void AddClamp(int start, int end, double rotation, int speed);

    virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos) override;

private:
	CAirSource mSource; ///< This tubing's air source
	CAirSink mSink;     ///< This tubing's air sink
    double mAirPressure = 0;  ///< The stiffness of this tubing
    std::vector<std::shared_ptr<CClamp>> mClamps;       ///< Vector of clamps for this tubing
    Gdiplus::Point mStartPoint = Gdiplus::Point(0, 0);  ///< The start point of this tubing
    Gdiplus::Point mEndPoint = Gdiplus::Point(0, 0);    ///< The end point of this tubing
};

