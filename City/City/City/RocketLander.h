/**
 * \file RocketLander.h
 *
 * \author Tyler Nichols
 *
 * Class that prevents crashes when deleting a pad
 *	while the rocket is in the air.
 */

#pragma once

#include "TileVisitor.h"
#include "Rocket.h"

 /**
  *  Implements a visitor to handle deletion of a rocket pad
  */
class CRocketLander : public CTileVisitor
{
public:
	CTileRocketPad* GiveRocket(std::shared_ptr<CRocket> rocket, CTileRocketPad* deletedPad, CCity* city);

	virtual void CRocketLander::VisitRocketPad(CTileRocketPad* pad) override;

private:
	/// The pad that originally held the rocket
	CTileRocketPad* initialPad = nullptr;

	/// The pad to give the rocket to
	CTileRocketPad* targetPad = nullptr;
};

