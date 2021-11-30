/**
 * \file FishMagikarp.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include <string>
#include "FishMagikarp.h"

using namespace std;

/// Fish filename 
const wstring FishMagikarpImageName = L"images/Magikarp.png";

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishMagikarp::CFishMagikarp(CAquarium* aquarium) :
    CFish(aquarium, FishMagikarpImageName)
{
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return the node we created
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishMagikarp::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);

    itemNode->SetAttribute(L"type", L"magikarp");

    return itemNode;
}