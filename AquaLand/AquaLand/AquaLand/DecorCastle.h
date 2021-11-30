/**
 * \file DecorCastle.h
 *
 * \author Tyler Nichols
 *
 * Class the implements a Decor Castle
 */

#pragma once

#include <memory>

#include "Item.h"


 /**
  * Implements a Decor Castle
  */
class CDecorCastle : public CItem
{
public:
    CDecorCastle(CAquarium* aquarium);

    /// Default constructor (disabled)
    CDecorCastle() = delete;

    /// Copy constructor (disabled)
    CDecorCastle(const CDecorCastle&) = delete;

    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};