/**
 * \file ActualMachine.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "ActualMachine.h"
#include <stdexcept>
#include "MachineActor.h"
#include "MachineFactoryOne.h"
#include "MachineFactoryTwo.h"

using namespace Gdiplus;
using namespace std;


CActualMachine::CActualMachine()
{
    SetMachineNumber(1);
}

void CActualMachine::SetLocation(int x, int y)
{
    mMachine->SetLocation(x, y);
}

void CActualMachine::DrawMachine(Gdiplus::Graphics* graphics)
{
    mMachine->DrawMachine(graphics);
}


void CActualMachine::SetMachineFrame(int frame)
{
    mMachine->SetMachineFrame(frame);
    mMachine->SetMachineTime();
}


void CActualMachine::SetMachineNumber(int seed)
{
    if (seed == 1)
    {
        CMachineFactoryOne factory;
        mMachine = factory.CreateMachine();
    }
    else if (seed == 2)
    {
        CMachineFactoryTwo factory;
        mMachine = factory.CreateMachine();
    }
    else
    {
        throw std::runtime_error("Invalid Machine Number " + seed);
    }
    mMachine->SetMachine(seed);
}

int CActualMachine::GetMachineNumber()
{
    return mMachine->GetMachine();
}
