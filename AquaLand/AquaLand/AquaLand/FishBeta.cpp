/**
 * \file FishBeta.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include <string>
#include "FishBeta.h"

using namespace std;

/// Fish filename 
const wstring FishBetaImageName = L"images/beta.png";

/** Constructor
 * \param aquarium The aquarium this is a member of
*/
CFishBeta::CFishBeta(CAquarium* aquarium) :
    CFish(aquarium, FishBetaImageName)
{
    SetSpeedX(minSpeedX + ((double)rand() / RAND_MAX) * (maxSpeedX - minSpeedX));
    SetSpeedY(minSpeedY + ((double)rand() / RAND_MAX) * (maxSpeedY - minSpeedY));
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return the node we created
 */
std::shared_ptr<xmlnode::CXmlNode>
CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CFish::XmlSave(node);

    itemNode->SetAttribute(L"type", L"beta");

    return itemNode;
}