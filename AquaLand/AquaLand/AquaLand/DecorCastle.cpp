/**
 * \file DecorCastle.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include <string>
#include "DecorCastle.h"

using namespace std;

/// Castle filename 
const wstring DecorCastleImageName = L"images/castle.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CDecorCastle::CDecorCastle(CAquarium* aquarium) :
    CItem(aquarium, DecorCastleImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return the node we created
 */
std::shared_ptr<xmlnode::CXmlNode>
CDecorCastle::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CItem::XmlSave(node);

    itemNode->SetAttribute(L"type", L"castle");

    return itemNode;
}