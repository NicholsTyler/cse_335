/**
 * \file BuildingCounter.h
 *
 * \author Charles B. Owen
 *
 * Derived from Tile visitor base class.
 */

#pragma once

#include "TileVisitor.h"

 /**
  *  Implements a visitor to count the number of buildings
  */
class CBuildingCounter : public CTileVisitor
{
public:
    /** Get the number of buildings
    * \returns Number of buildings */
    int GetNumBuildings() const { return mNumBuildings; }

    void VisitBuilding(CTileBuilding* building);

private:
    /// Buildings counter
    int mNumBuildings = 0;
};

