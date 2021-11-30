/**
 * \file Fish.h
 *
 * \author Charles B. Owen
 *
 * Base class for any fish in our aquarium.
 * Derived from CItem
 */

#pragma once
#include "Item.h"

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
    /// Default constructor (disabled)
    CFish() = delete;

    /// Copy constructor (disabled)
    CFish(const CFish&) = delete;

    void Update(double elapsed);

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /** Set the x speed
    * \param x x speed */
    void SetSpeedX(double x) { mSpeedX = x; }

    /** Set the y speed
    * \param y y speed */
    void SetSpeedY(double y) { mSpeedY = y; }

protected:
    CFish(CAquarium* aquarium, const std::wstring& filename);

private:
    /// Fish speed in the X direction
    double mSpeedX;

    /// Fish speed in the Y direction
    double mSpeedY;

    void AdjustX();
    void AdjustY();
};

