/**
 * \file MotionSource.h
 *
 * \author Tyler Nichols
 *
 * A class for creating Motion sources
 *
 */

#pragma once

#include "MotionSink.h"
#include "Chime.h"

 /**
  * A class to create Motion sources
  */
class CMotionSource
{
public:
    /// Constructor
    CMotionSource() {}

    /// Destructor
    virtual ~CMotionSource() {}

    /// Copy constructor (disabled)
    CMotionSource(const CMotionSource&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CMotionSource&) = delete;

    /**
    * Calls ApplyForce on associated motion sink
    * \param force The force to set motion sink to
    */
    void ApplyForce(double force) { if (mSink != nullptr) mSink->ReceiveForce(force); }

    /**
    * Sets the association for the motion sink
    * \param sink The motion sink
    */
    void SetSink(CMotionSink* sink) { mSink = sink; }

private:
    CMotionSink* mSink = nullptr;    ///< This source's Motion sink
};

