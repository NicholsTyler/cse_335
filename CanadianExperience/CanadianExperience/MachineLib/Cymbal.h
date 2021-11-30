/**
 * \file Cymbal.h
 *
 * \author Tyler Nichols
 *
 * A class for creating a cymbal
 *
 */

#pragma once

#include "Shape.h"

 /**
  * A class to create cymbals
  */
class CCymbal : public CShape
{
public:
	/// Constructor
	CCymbal();

	/// Destructor
	virtual ~CCymbal() {}

	/// Copy constructor/disabled
	CCymbal(const CCymbal&) = delete;

	/// Assignment operator/disabled
	void operator=(const CCymbal&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos) override;
	virtual void SetMotion(double pressure) override;

private:
	CPolygon mStand;		///< The Cymbal Stand
	CPolygon mCymbal;		///< The Cymbal
	double mRockTimeRem;	///< The Rocking Time Remaining
};

