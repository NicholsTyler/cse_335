/**
 * \file FishAngler.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include <string>
#include "FishAngler.h"

using namespace std;

/// Fish filename 
const wstring FishAnglerImageName = L"images/angler.png";

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishAngler::CFishAngler(CAquarium* aquarium) :
    CFish(aquarium, FishAnglerImageName)
{
    imgReversed = true;
    SetSpeedX(minSpeedX + ((double)rand() / RAND_MAX) * (maxSpeedX - minSpeedX));
    SetSpeedY(minSpeedY + ((double)rand() / RAND_MAX) * (maxSpeedY - minSpeedY));
    SetMirror(imgReversed);
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return the node we created
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishAngler::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);

    itemNode->SetAttribute(L"type", L"angler");

    return itemNode;
}