/**
 * \file TileRocketPad.cpp
 *
 * \author 
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include "City.h"
#include "TileRocketPad.h"
#include "MemberReport.h"
#include "Rocket.h"
#include "RocketPadVisitor.h"
#include "RocketLander.h"

using namespace std;
using namespace Gdiplus;

/// The image to display for the rocket pad
const wstring RocketPadImage = L"pad.png";


/** Constructor
* \param city The city this is a member of
*/
CTileRocketPad::CTileRocketPad(CCity* city) : CTile(city)
{
    SetImage(RocketPadImage);

    CRocketPadVisitor visitor;
    city->Accept(&visitor);
    if (visitor.GetNumRocketPads() == 0)
    {
        auto rocket = make_shared<CRocket>(city);
        mRocket = rocket;
        mRocket->SetLaunchingPad(this);
    }
}


/**  Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileRocketPad::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CTile::XmlSave(node);

    itemNode->SetAttribute(L"type", L"rocketpad");

    return itemNode;
}


/**
 * Generate a report for this  tile.
 * @param report
*/
void CTileRocketPad::Report(std::shared_ptr<CMemberReport> report)
{
    wstringstream str;
    str << L"Rocket Pad";

    report->SetReport(str.str());
}

/**
 * Indicate that this object is about to be deleted by
 * begin dragged into the trash can. If the function
 * override returns false, the delete will not occur.
 * @return true if okay to delete.
*/
bool CTileRocketPad::PendingDelete()
{
    CRocketLander visitor;
    auto targetPad = visitor.GiveRocket(mRocket, this, GetCity());
    mRocket.get()->SetLaunchingPad(targetPad);
    return true;
}

/**
 * Handles updates for animation
 * \param elapsed The time since last update
*/
void CTileRocketPad::Update(double elapsed) 
{
    if (mRocket != nullptr)
        mRocket->Update(this, elapsed);
}

/**
 * Draw the RocketPad.
 * @param graphics
*/
void CTileRocketPad::Draw(Gdiplus::Graphics* graphics)
{
    CTile::Draw(graphics);
    if (mRocket != nullptr)
        mRocket->Draw(this, graphics);
}

/**
 * This function is called when the rocket has
 * landed on some other pad. It is no longer accessible to
 * this pad.
*/
void CTileRocketPad::RocketIsGone()
{
    mRocket = nullptr;
}

/**
 * This function is called when the rocket has landed on this
 * pad. This pad should now become the launching pad.
*/
void CTileRocketPad::RocketHasLanded()
{
    mRocket.get()->SetLaunchingPad(this);
}

