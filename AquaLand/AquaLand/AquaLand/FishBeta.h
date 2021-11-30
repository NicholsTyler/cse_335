/**
 * \file FishBeta.h
 *
 * \author Charles B. Owen
 *
 * Class the implements a Beta fish
 */

#pragma once

#include <memory>

#include "Fish.h"


 /**
  * Implements a Beta fish
  */
class CFishBeta : public CFish
{
public:
    CFishBeta(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishBeta() = delete;

    /// Copy constructor (disabled)
    CFishBeta(const CFishBeta&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

private:
    /// The fastest the beta fish can travel in the x direction
    const double maxSpeedX = 75;
    /// The fastest the beta fish can travel in the y direction
    const double maxSpeedY = 200;
    /// The slowest the beta fish can travel in the x direction
    const double minSpeedX = 0;
    /// The slowest the beta fish can travel in the y direction
    const double minSpeedY = 100;
};