/**
 * \file Cylinder.h
 *
 * \author Tyler Nichols
 *
 * A class for creating the Cylinder
 *
 */

#pragma once

#include "AirSinkDestination.h"
#include "Component.h"
#include <gdiplus.h>
#include "Polygon.h"
#include "AirSink.h"
#include "Chime.h"
#include "MotionSource.h"
#include "MotionSinkDestination.h"

 /**
  * A class to create the cylinder
  *
  * Derived from CComponent
  */
class CCylinder : public CComponent, public IAirSinkDestination
{
public:
	/// Constructor
	CCylinder();

	/// Destructor
	virtual ~CCylinder() {}

	/// Copy constructor/disabled
	CCylinder(const CCylinder&) = delete;

	/// Assignment operator/disabled
	void operator=(const CCylinder&) = delete;

	/**
	 * Get this cylinder's air sink
	 * @return Pointer to CAirSink object.
	*/
	CAirSink* GetSink() { return &mSink; }

	/**
	* Sets the maximum extension of the ram
	* \param ext The extension to set the ram to
	*/
	void SetMaxExtent(double ext) { mExtensionDistance *= ext; }

	/**
	* Sets the motion sink for this cylinder
	* \param moSink The motion sink component of the motion sink
	*/
	void SetMotionSink(std::shared_ptr<IMotionSinkDestination> moSink) { mSource->SetSink(moSink->GetSink()); }

	/**
	* Extends the ram
	* \param pressure The amount of pressure to extend with
	*/
	void ExtendRam(double pressure) { mRamPos = pressure; }

	/**
	* Sends the air to the air sink
	* \param air The amount of air to receive
	*/
	void RetrieveAir(double air) { mSink.ReceiveAir(air); }

	void SetRotation(double rot);

	virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos) override;
	virtual void SetPressure(double pressure) override;
	virtual void SetPosition(int x, int y) override;

private:
	double DegreeToRadian(double degree);

	CPolygon mMount;		///< The Cylinder mount
	CPolygon mCylinder;		///< The Cylinder base
	CPolygon mRam;			///< The Cylinder ram
	double mRamPos = 0;		///< The current position of the Ram
	double mRot    = 0;		///< The rotation of the cylinder
	double mExtensionDistance = 44;	///< The maximum extension of the ram
	double mExtensionLength   = 0;	///< The extension length of the ram
	CAirSink mSink;			///< The air sink for this component
	std::shared_ptr<CMotionSource> mSource;	///< The motion source for this component
};

