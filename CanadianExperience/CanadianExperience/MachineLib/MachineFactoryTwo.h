/**
 * \file MachineFactoryTwo.h
 *
 * \author Tyler Nichols
 *
 * Machine factory class. Creates Machine Type Two object
 */

#pragma once

#include <memory>
#include "MachineActor.h"

 /**
  * A factory to create a machine type two
  */
class CMachineFactoryTwo
{
public:
    CMachineFactoryTwo() {}

    std::shared_ptr<CMachineActor> CreateMachine();
};

