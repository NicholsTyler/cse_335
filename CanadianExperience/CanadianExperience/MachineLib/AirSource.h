/**
 * \file AirSource.h
 *
 * \author Tyler Nichols
 *
 * A class for creating air sources
 *
 */

#pragma once

#include "AirSink.h"
#include <gdiplus.h>
#include "TubingPoint.h"

 /**
  * A class to create air sources
  */
class CAirSource : public CTubingPoint
{
public:
    /// Constructor
    CAirSource() {}

    /// Destructor
    virtual ~CAirSource() {}

    /// Copy constructor (disabled)
    CAirSource(const CAirSource&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CAirSource&) = delete;

    /**
    * Calls SetPressure on associated air sink
    * \param pressure The pressure to set air sink to
    */
    void SetPressure(double pressure) { if (mSink != nullptr) mSink->SetPressure(pressure); }

    /**
    * Sets the association for the air sink
    * \param sink The air sink
    */
    void SetSink(CAirSink* sink) { mSink = sink; mSink->SetSource(this);
    }

    /**
    * Get this air source's sink
    * \return The air sink
    */
    CAirSink* GetSink() { return mSink; }

    /**
    * Sends pressure from this source to the sink
    * \param pressure The amount of pressure
    */
    void SendAir(double pressure) { mSink->ReceiveAir(pressure); }

private:
    CAirSink* mSink = nullptr;    ///< This source's air sink
};

