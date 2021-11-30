/**
 * \file RocketPadVisitor.h
 *
 * \author Tyler Nichols
 *
 * Derived from Tile visitor base class.
 */

#pragma once

#include "TileVisitor.h"
#include "TileRocketPad.h"
#include "City.h"

 /**
  *  Implements a visitor to launch the rocket and verify rocket pads
  */
class CRocketPadVisitor : public CTileVisitor
{
public:
    /** Get the number of rocket pads
    * \returns Number of rocket pads */
    int GetNumRocketPads() const { return mNumRocketPads; }

    /** Determines if last visited tile was a rocket pad
    * \returns true if last tile was a rocket pad. */
    bool IsRocketPad() { return mIsRocketPad; }

    /** Getter for the previous rocket pad visited
    * \returns pointer to the rocket pad. */
    CTileRocketPad* PrevRocketTile() { return mPrevRocketPad; }

    /** Finds which pad has the rocket
    * \param city The city we are located in
    * \returns pointer to the pad with the rocket */
    CTileRocketPad* FindRocket(CCity* city) { city->Accept(this); return mRocketTile; }

    virtual void VisitRocketPad(CTileRocketPad* pad) override;
    virtual void VisitBuilding(CTileBuilding* building) override;
    virtual void VisitCoalmine(CTileCoalmine* coalmine) override;
    virtual void VisitLandscape(CTileLandscape* landscape) override;
    virtual void VisitRoad(CTileRoad* road) override;
    virtual void VisitGarden(CTileGarden* garden) override;

private:
    /// RocketPads counter
    int mNumRocketPads = 0;
    /// Determines if tile is a RocketPad
    bool mIsRocketPad = false;
    /// Tile containing the rocket
    CTileRocketPad* mRocketTile = nullptr;
    /// Previous RocketPad tile visited
    CTileRocketPad* mPrevRocketPad = nullptr;
};

