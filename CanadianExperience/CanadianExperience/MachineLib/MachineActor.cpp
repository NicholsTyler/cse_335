/**
 * \file MachineActor.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "MachineActor.h"
#include <sstream>
#include "CardReader.h"

using namespace Gdiplus;
using namespace std;

//const double M_PI = 3.1415;

/**
 * Default Constructor
 */
CMachineActor::CMachineActor()
{
    SetMachine(1);
}

/**
 * Constructor
 * \param number The machine number
 */
CMachineActor::CMachineActor(int number)
{
    SetMachine(number);
}


/**
 * Destructor
 */
CMachineActor::~CMachineActor()
{
}


/**
* Draw the machine at the currently specified location
* \param graphics GDI+ Graphics object
*/
void CMachineActor::DrawMachine(Gdiplus::Graphics* graphics)
{
    Point pos(mX, mY);
    for (auto component : mComponents)
    {
        component->Draw(graphics, pos);
    }
}

/**
* Set the current machine time
*/
void CMachineActor::SetMachineTime()
{ 
    mTime = mFrame / 30.0; 
    if (mCardReader != nullptr && mTime <= 28)
        mCardReader->SetTime(mTime);
}
