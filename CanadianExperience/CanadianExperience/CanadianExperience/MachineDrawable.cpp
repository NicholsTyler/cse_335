/**
 * \file MachineDrawable.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "MachineFactory.h"
#include "Timeline.h"

using namespace Gdiplus;

/** Constructor
* \param name The name of the machine
* \param seed The machine number to construct
*/
CMachineDrawable::CMachineDrawable(const std::wstring& name, int seed) :
    CDrawable(name)
{
    // Updates the mMachine variable for this class
    CMachineFactory factory;
    mMachine = factory.CreateMachine();
    mMachine->SetMachineNumber(seed);
}

/** Draw the drawable
* \param graphics Graphics object to draw on */
void CMachineDrawable::Draw(Graphics* graphics)
{
    // Plays music after play is clicked
    int currentFrame = mTimeline->GetCurrentFrame();
    if (mStartTime == -1 || currentFrame < mStartTime)
    {
        currentFrame = 0;
    }
    else
    {
        currentFrame -= mStartTime;
    }
    mMachine->SetMachineFrame(currentFrame);

    float scale = 0.5f; // The scale of the machine

    // Draws the machine
    auto save = graphics->Save();
    graphics->TranslateTransform((float)mPlacedPosition.X,
        (float)mPlacedPosition.Y);
    graphics->ScaleTransform(scale, scale);
    mMachine->DrawMachine(graphics);
    graphics->Restore(save);
}

/** Set the timeline for this machine drawable
* \param timeline The timeline class.
*/
void CMachineDrawable::SetTimeline(CTimeline* timeline)
{
    mTimeline = timeline;
}
