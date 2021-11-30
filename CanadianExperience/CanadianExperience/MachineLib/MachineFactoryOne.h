/**
 * \file MachineFactoryOne.h
 *
 * \author Tyler Nichols
 *
 * Machine factory class. Creates Machine Type One object
 */

#pragma once

#include <memory>
#include "MachineActor.h"

 /**
  * A factory to create a machine type one
  */
class CMachineFactoryOne
{
public:
    CMachineFactoryOne() {}

    std::shared_ptr<CMachineActor> CreateMachine();
};

