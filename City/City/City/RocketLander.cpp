/**
 * \file RocketLander.cpp
 *
 * \author Tyler Nichols
 */

#include "pch.h"
#include "RocketLander.h"
#include "TileRocketPad.h"
#include "City.h"

 /** Finds a new rocket pad to give the rocket to in an emergency
 * \param rocket A pointer to the rocket
 * \param deletedPad The pad which is going to be deleted
 * \param city A pointer to the city this tile is located in
 * \returns pointer to the new pad */
CTileRocketPad* CRocketLander::GiveRocket(std::shared_ptr<CRocket> rocket, CTileRocketPad* deletedPad, CCity* city)
{
	initialPad = deletedPad;
	city->Accept(this);
	targetPad->SetRocket(rocket);
	return targetPad;
}

/** Visit a Rocket object
* \param pad The pad we are visiting */
void CRocketLander::VisitRocketPad(CTileRocketPad* pad)
{
	if (pad->HasRocket() && pad != initialPad)
		targetPad = pad;
}