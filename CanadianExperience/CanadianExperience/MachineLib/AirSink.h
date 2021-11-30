/**
 * \file AirSink.h
 *
 * \author Tyler Nichols
 *
 * A class for creating air sinks
 *
 */

#pragma once

#include "AirSinkDestination.h"
#include "TubingPoint.h"

class CAirSource;

 /**
  * A class to create air sinks
  */
class CAirSink : public CTubingPoint
{
public:
    /// Constructor
    CAirSink() {}

    /// Destructor
    virtual ~CAirSink() {}

    /// Copy constructor (disabled)
    CAirSink(const CAirSink&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CAirSink&) = delete;

    /**
    * Calls SetPressure on component association
    * \param pressure The pressure to set component to
    */
    void SetPressure(double pressure) { mComponent->SetPressure(pressure); }

    /**
    * Set the air source
    * \param source The airsource
    */
    void SetSource(CAirSource* source) { mSource = source; }

    /**
    * Get this air source's source
    * \return The air source
    */
    CAirSource* GetSource() { return mSource; }

    /**
    * Set the component association
    * \param component The component
    */
    void SetComponent(IAirSinkDestination* component) { mComponent = component; }

    /**
    * Receive air from air source
    * \param pressure The pressure amount
    */
    void ReceiveAir(double pressure) { airPressure = pressure; }

private:
    CAirSource* mSource = nullptr;              ///< This sink's air source
    IAirSinkDestination* mComponent = nullptr;  ///< Component connected to this air sink
    double airPressure = 0;                     ///< The amount of air pressure in this sink
};

