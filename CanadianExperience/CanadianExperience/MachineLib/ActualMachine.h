/**
 * \file ActualMachine.h
 *
 * \author Tyler Nichols
 *
 * Class that represents the actual machine.
 */

#pragma once

#include "Machine.h"
#include "MachineActor.h"

 /**
  * A class to represent the actual machine
  *
  * Derived from CMachine
  */
class CActualMachine : public CMachine
{
public:
    /// Constructor
    CActualMachine();

    /// Destructor
    virtual ~CActualMachine() override {}

    /// Copy constructor/disabled
    CActualMachine(const CActualMachine&) = delete;

    /// Assignment operator/disabled
    void operator=(const CActualMachine&) = delete;

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    virtual void SetLocation(int x, int y) override;

    /**
    * Draw the machine at the currently specified location
    * \param graphics GDI+ Graphics object
    */
    virtual void DrawMachine(Gdiplus::Graphics* graphics) override;

    /**
    * Set the current machine animation frame
    * \param frame Frame number
    */
    virtual void SetMachineFrame(int frame) override;

    /**
    * Set the machine number
    * \param machine An integer number. Each number makes a different machine
    */
    virtual void SetMachineNumber(int machine) override;

    /**
     * Get the current machine number
     * \return Machine number integer
     */
    virtual int GetMachineNumber() override;

private:
    std::shared_ptr<CMachineActor> mMachine;  ///< The working machine
};

