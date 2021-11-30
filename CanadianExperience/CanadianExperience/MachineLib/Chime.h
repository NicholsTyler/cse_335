/**
 * \file Chime.h
 *
 * \author Tyler Nichols
 *
 * A class for creating chimes
 *
 */

#pragma once

#include <memory>
#include "Component.h"
#include "Polygon.h"
#include "MotionSink.h"
#include "MotionSinkDestination.h"
#include "WavChannel.h"
#include "SoundSource.h"

 /**
  * A class to create chimes
  */
class CChime : public CComponent, public IMotionSinkDestination, public ISoundSource
{
public:
	/// Constructor
	CChime(int length);

	/// Destructor
	virtual ~CChime() {}

	/// Copy constructor/disabled
	CChime(const CChime&) = delete;

	/// Assignment operator/disabled
	void operator=(const CChime&) = delete;

	/**
	 * Get this chime's motion sink
	 * @return Pointer to CMotionSink object.
	*/
	virtual CMotionSink* GetSink() override { return &mSink; }

	/**
	* Sets the audio channel for this chime
	* \param channel The audio channel for this chime
	*/
	virtual void SetAudioChannel(std::shared_ptr<CWavChannel> channel) override { wC = channel; }

	virtual void SetMotion(double pressure) override;
	virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos) override;

private:
	CPolygon mMountImage;	///< The image for the mount
	CPolygon mBaseImage;	///< The image for the hammer
	CPolygon mChimeImage;	///< The image for the chime
	CMotionSink mSink;		///< The motion sink for this component
	double mRotation;		///< The rotation of the hammer
	double mLastPressure;	///< The last pressure provided
	double length = 0;		///< Length of the chime
	double width = 0;		///< Width of the chime
	std::shared_ptr<CWavChannel> wC;	///< This chime's wav channel
};

