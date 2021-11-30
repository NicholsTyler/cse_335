/**
 * \file Fish.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 50;

/**
 * Constructor
 * \param aquarium The aquarium we are in
 * \param filename Filename for the image we use
 */
CFish::CFish(CAquarium* aquarium, const std::wstring& filename) :
    CItem(aquarium, filename)
{
    mSpeedX = ((double)rand() / RAND_MAX) * MaxSpeedX;
    mSpeedY = ((double)rand() / RAND_MAX) * MaxSpeedY;
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CFish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
        GetY() + mSpeedY * elapsed);

    AdjustX();
    AdjustY();
}

/**
 * Handle needed x adjustments for fish
 *
 * This is called after updating fish location
 * allowing for needed adjustments to image orientation
 * and speed on the x axis.
 */
void CFish::AdjustX()
{
    // X Location of fish + 10 pixels + half its width
    double fishRight = GetX() + 10 + (GetItemWidth() / 2);

    // X Location of fish - 10 pixels - half its width
    double fishLeft = GetX() - 10 - (GetItemWidth() / 2);

    if (mSpeedX > 0 && fishRight >= GetAquarium()->GetWidth())
    {
        mSpeedX = -mSpeedX;
        SetMirror(mSpeedX < 0);
    }
    else if (mSpeedX < 0 && fishLeft <= 0)
    {
        mSpeedX = -mSpeedX;
        SetMirror(mSpeedX < 0);
    }
}

/**
 * Handle needed y adjustments for fish
 *
 * This is called after updating fish location
 * allowing for needed adjustments to speed on
 * the y axis.
 */
void CFish::AdjustY()
{
    // Y Location of fish + 10 pixels + half its height
    double fishUp = GetY() + 10 + (GetItemHeight() / 2);

    // Y Location of fish - 10 pixels - half its height
    double fishDown = GetY() - 10 - (GetItemHeight() / 2);

    if (mSpeedY > 0 && fishUp >= GetAquarium()->GetHeight())
    {
        mSpeedY = -mSpeedY;
    }
    else if (mSpeedY < 0 && fishDown <= 0)
    {
        mSpeedY = -mSpeedY;
    }
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return the node we created
 */
std::shared_ptr<xmlnode::CXmlNode>
CFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = node->AddChild(L"item");

    itemNode->SetAttribute(L"x", GetX());
    itemNode->SetAttribute(L"y", GetY());
    itemNode->SetAttribute(L"xSpeed", mSpeedX);
    itemNode->SetAttribute(L"ySpeed", mSpeedY);

    return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * Override of the base class version. Adds attributes
 * for x and y speed.
 *
 * \param node The Xml node we are loading the item from
 */
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    mSpeedX = node->GetAttributeDoubleValue(L"xSpeed", 0);
    mSpeedY = node->GetAttributeDoubleValue(L"ySpeed", 0);
}