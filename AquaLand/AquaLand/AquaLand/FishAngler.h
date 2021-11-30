/**
 * \file FishAngler.h
 *
 * \author Charles B. Owen
 *
 * Class the implements an Angler fish
 */

#pragma once

#include <memory>

#include "Fish.h"


 /**
  * Implements an angler fish
  */
class CFishAngler : public CFish
{
public:
    CFishAngler(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishAngler() = delete;

    /// Copy constructor (disabled)
    CFishAngler(const CFishAngler&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

private:
    /// The fastest the angler fish can travel in the x direction
    const double maxSpeedX = -300;
    /// The fastest the angler fish can travel in the y direction
    const double maxSpeedY = -75;
    /// The slowest the angler fish can travel in the x direction
    const double minSpeedX = -200;
    /// The slowest the angler fish can travel in the y direction
    const double minSpeedY = -25;
};