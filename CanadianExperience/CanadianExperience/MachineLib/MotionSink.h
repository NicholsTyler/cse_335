/**
 * \file MotionSink.h
 *
 * \author Tyler Nichols
 *
 * A class for creating Motion sinks
 *
 */

#pragma once

#include "MotionSinkDestination.h"

class CMotionSource;

/**
 * A class to create Motion sinks
 */
class CMotionSink
{
public:
    /// Constructor
    CMotionSink() {}

    /// Destructor
    virtual ~CMotionSink() {}

    /// Copy constructor (disabled)
    CMotionSink(const CMotionSink&) = delete;

    /// Assignment operator (disabled)
    void operator=(const CMotionSink&) = delete;

    /**
    * Calls SetMotion on component association
    * \param force The force to set component to
    */
    void ReceiveForce(double force) { mComponent->SetMotion(force); }

    /**
    * Set the Motion source
    * \param source The Motionsource
    */
    void SetSource(CMotionSource* source) { mSource = source; }

    /**
    * Set the component association
    * \param component The component
    */
    void SetComponent(IMotionSinkDestination* component) { mComponent = component; }

private:
    CMotionSource* mSource = nullptr;              ///< This sink's Motion source
    IMotionSinkDestination* mComponent = nullptr;  ///< Component connected to this Motion sink
};

