/**
 * \file RocketPadVisitor.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "RocketPadVisitor.h"

 /** Visit a Rocket object
 * \param pad The pad we are visiting */
void CRocketPadVisitor::VisitRocketPad(CTileRocketPad* pad)
{
    mNumRocketPads++;
    mIsRocketPad = true;
    if (mIsRocketPad && pad->HasRocket())
        mRocketTile = pad;
    mPrevRocketPad = pad;
}

/** Visit a CTileBuilding object
 * \param building Building we are visiting */
void CRocketPadVisitor::VisitBuilding(CTileBuilding* building) { mIsRocketPad = false; }

/** Visit a CTileCoalmine object
* \param coalmine Coal mine we are visiting */
void CRocketPadVisitor::VisitCoalmine(CTileCoalmine* coalmine) { mIsRocketPad = false; }

/** Visit a CTileLandscape object
* \param landscape Landscape tile we are visiting */
void CRocketPadVisitor::VisitLandscape(CTileLandscape* landscape) { mIsRocketPad = false; }

/** Visit a CTileRoad object
* \param road Road we are visiting */
void CRocketPadVisitor::VisitRoad(CTileRoad* road) { mIsRocketPad = false; }

/** Visit a CTileGarden object
* \param garden Garden we are visiting */
void CRocketPadVisitor::VisitGarden(CTileGarden* garden) { mIsRocketPad = false; }