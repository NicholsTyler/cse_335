/**
 * \file MachineActor.h
 *
 * \author Tyler Nichols
 *
 * A class for the instantiated machine
 * 
 */

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "WavPlayer.h"

class CCardReader;


 /**
  * A class to represent an instantiated machine
  */
class CMachineActor
{
public:
    CMachineActor();
    CMachineActor(int number);
    virtual ~CMachineActor();

    /**
    * Set the position for the root of the machine
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    void SetLocation(int x, int y) { mX = x; mY = y; mLocation = Gdiplus::Point(x, y); }

    /**
    * Set the current machine animation frame
    * \param frame Frame number
    */
    void SetMachineFrame(int frame) { mFrame = frame; }

    /**
    * Set the machine number
    * \param machine An integer number. Each integer makes a different machine
    */
    void SetMachine(int machine) { mMachine = machine; }

    /**
    * Adds a component to this machine
    * \param component The component to add
    */
    void AddComponent(std::shared_ptr<CComponent> component) { mComponents.push_back(component); }

    /**
    * Gets the wav player for this Machine Actor
    * \return The wav player
    */
    CWavPlayer* GetWavPlayer() { return &wP; }

    /**
    * Set the card reader for this Machine Actor
    * \param cardReader The card reader
    */
    void SetCardReader(CCardReader* cardReader) { mCardReader = cardReader; }

    void SetMachineTime();
    void DrawMachine(Gdiplus::Graphics* graphics);

    /**
    * Get the current machine number
    * \return Machine number
    */
    virtual int GetMachine() { return mMachine; }

private:
    Gdiplus::Point mLocation = Gdiplus::Point(0, 0);    ///< This machine's location
    int mX = 0;         ///< Machine X location
    int mY = 0;         ///< Machine Y location
    int mFrame = 0;     ///< Current frame
    double mTime = 0;   ///< Current time
    int mMachine = 1;   ///< Machine number
    CWavPlayer wP;      ///< This machine's WavPlayer
    std::vector<std::shared_ptr<CComponent>> mComponents; ///< List of components
    CCardReader* mCardReader = nullptr; ///< The card reader associated with this machine
};

