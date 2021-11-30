/**
 * \file MotionSinkDestination.h
 *
 * \author Tyler Nichols
 *
 * An interface for all Motion sink destinations
 *
 */

#pragma once

class CMotionSink;

 /**
  * An interface for Motion sink destinations
  */
class IMotionSinkDestination
{
public:
    /**
    * Sets a component's pressure
    * \param pressure The pressure to set component to
    */
    virtual void SetMotion(double pressure) = 0;

    /**
     * Get this motion sink's motion sink component
     * @return Pointer to CMotionSink object.
    */
    virtual CMotionSink* GetSink() = 0;
};

