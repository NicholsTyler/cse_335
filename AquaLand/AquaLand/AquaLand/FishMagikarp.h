/**
 * \file FishMagikarp.h
 *
 * \author Charles B. Owen
 *
 * Class the implements a Magikarp fish
 */

#pragma once

#include <memory>

#include "Fish.h"


 /**
  * Implements a Magikarp fish
  */
class CFishMagikarp : public CFish
{
public:
    CFishMagikarp(CAquarium* aquarium);

    /// Default constructor (disabled)
    CFishMagikarp() = delete;

    /// Copy constructor (disabled)
    CFishMagikarp(const CFishMagikarp&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};