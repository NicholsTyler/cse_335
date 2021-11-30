/**
 * \file AirSinkDestination.h
 *
 * \author Tyler Nichols
 *
 * An interface for all air sink destinations
 *
 */

#pragma once

 /**
  * An interface for air sink destinations
  */
class IAirSinkDestination
{
public:
    /**
    * Sets a component's pressure
    * \param pressure The pressure to set component to
    */
    virtual void SetPressure(double pressure) = 0;
};

