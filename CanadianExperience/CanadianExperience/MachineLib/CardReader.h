/**
 * \file CardReader.h
 *
 * \author Tyler Nichols
 *
 * A class for creating the Card Reader
 *
 */

#pragma once

#include "AirSinkDestination.h"
#include "Component.h"
#include <gdiplus.h>
#include <string>
#include "Polygon.h"
#include "AirSource.h"
#include "MachineActor.h"

 /**
  * A class to create the card reader
  *
  * Derived from CComponent
  */
class CCardReader : public CComponent, public IAirSinkDestination
{
public:
	/// Constructor
	CCardReader();

	/// Destructor
	virtual ~CCardReader() {}

	/// Copy constructor/disabled
	CCardReader(const CCardReader&) = delete;

	/// Assignment operator/disabled
	void operator=(const CCardReader&) = delete;

	/**
	* Set the card image
	* \param filename Where the image is stored
	*/
	void SetCard(std::wstring filename) { mCard.SetImage(filename); }

	/**
	 * Get an air source.
	 * @param i Source index 0-9
	 * @return Pointer to CAirSource object.
	*/
	std::shared_ptr<CAirSource> GetSource(int i) { return mSources[i]; }

	bool IsPunched(int column, int row);
	void SetTime(double time);

	/**
	* Generate Air Pressure for the column
	* \param column The column
	* \param pressure The amount of pressure
	*/
	void GenerateAirPressure(int column, int pressure) {}

	virtual void SetPressure(double pressure) override;
	virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos) override;
	virtual void SetPosition(int x, int y) override;

private:
	CPolygon mBackground;		///< The image for the back of the card reader
	CPolygon mForeground;		///< The image for the front of the card reader
	CPolygon mCard;				///< The image of the card to read
	int mBeatsPerMinute = 180;	///< The number of beats per minute
	int mColumn = 1;			///< The positon of the current row and column of card
	std::vector<std::shared_ptr<CAirSource>> mSources;	///< The air sources to drive things
};

