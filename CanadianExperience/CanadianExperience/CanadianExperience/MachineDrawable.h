/**
 * \file MachineDrawable.h
 *
 * \author Tyler Nichols
 * 
 * Handles drawing machines
 */

#pragma once

#include "Drawable.h"
#include "Machine.h"
#include <memory>
#include <string>

/**
* Class to draw machines
*/
class CMachineDrawable : public CDrawable
{
public:
    /** Constructor */
    CMachineDrawable(const std::wstring& name, int seed);

    /** Destructor */
    virtual ~CMachineDrawable() {}

    /** Default constructor disabled */
    CMachineDrawable() = delete;
    /** Copy constructor disabled */
    CMachineDrawable(const CMachineDrawable&) = delete;
    /** Assignment operator disabled */
    void operator=(const CMachineDrawable&) = delete;

    /** The machine this class draws
    * \returns Machine */
    std::shared_ptr<CMachine> GetMachine() { return mMachine; }

    /** The name of this machine drawable
    * \returns Name */
    std::wstring GetName() { return mName; }

    /** Set the name of this machine drawable
    * \param name The name */
    void SetName(std::wstring name) { mName = name; }

    /**
     * Get the start frame of this machine
     * \return Start Frame
     */
    int GetStartTime() { return mStartTime; }

    /**
     * Set the start frame of this machine
     * \param startTime The start frame
     */
    void SetStartTime(int startTime) { mStartTime = startTime; }

    /**
     * Get the current machine number
     * \return Machine number integer
     */
    int GetMachineNumber() { return mMachine->GetMachineNumber(); }

    /**
     * Set the current machine number
     * \param number The machine number
     */
    void SetMachineNumber(int number) { mMachine->SetMachineNumber(number); }

    /// No need to set keyframe for machines
    virtual void SetKeyframe() override {}

    /**
     * Is this machine movable?
     * \return True if movable
     */
    bool IsMovable() { return false; }

    virtual void Draw(Gdiplus::Graphics* graphics) override;
    virtual void SetTimeline(CTimeline* timeline) override;

private:
    std::shared_ptr<CMachine> mMachine; ///< The actual machine
    CTimeline* mTimeline;               ///< The timeline
    int mStartTime = -1;                ///< The frame to begin playing machine
    std::wstring mName;                 ///< The name of this machine drawable
};

