/**
 * \file Shape.h
 *
 * \author Tyler Nichols
 *
 * A class for creating shapes
 *
 */

#pragma once

#include <gdiplus.h>
#include "Component.h"
#include "Polygon.h"
#include "SoundSource.h"
#include "MotionSinkDestination.h"
#include "MotionSink.h"

 /**
  * A class to creates shapes using CPolygon.
  * 
  * Derived from CComponent
  */
class CShape : public CComponent, public ISoundSource, public IMotionSinkDestination
{
public:
	/// Constructor
	CShape();

	/// Destructor
	virtual ~CShape() {}

	/// Copy constructor/disabled
	CShape(const CShape&) = delete;

	/// Assignment operator/disabled
	void operator=(const CShape&) = delete;

	/**
	 * Create a rectangle
	 * \param x Left side X
	 * \param y Bottom left Y
	 * \param wid Width of the rectangle. If not supplied, use an image width
	 * \param hit Height of the rectangle. If not supplied, use an image height
	 */
	void Rectangle(int x, int y, int wid = 0, int hit = 0) { mImage.Rectangle(x, y, wid, hit); }

	/**
	 * Set an image we will use as a texture for the polygon
	 * \param filename Image filename
	 */
	void SetImage(std::wstring filename) { mImage.SetImage(filename); }

	/**
	 * Get the width of any set image for this polygon. This may not be
	 * the width we actually draw, but is the size of the polygon itself.
	 * @return Width in pixels
	*/
	int GetImageWidth() { return mImage.GetImageWidth(); }

	/**
	 * Get the height of any set image for this polygon. This may not be
	 * the height we actually draw, but is the size of the polygon itself.
	 * @return Height in pixels
	*/
	int GetImageHeight() { return mImage.GetImageHeight(); }

	/**
	* Set the color of the polygon
	* \param color The color to set polygon to
	*/
	void SetColor(Gdiplus::Color color) { mImage.SetColor(color); }

	/**
	* Sets the audio channel for this shape
	* \param channel The audio channel for this shape
	*/
	virtual void SetAudioChannel(std::shared_ptr<CWavChannel> channel) override { wC = channel; }

	/**
	 * Get this shape's motion sink
	 * @return Pointer to CMotionSink object.
	*/
	virtual CMotionSink* GetSink() override { return &mSink; }

	/**
	 * Get the last pressure
	 * @return The last pressure as a double
	*/
	double GetLastPressure() { return mLastPressure; }

	virtual void Draw(Gdiplus::Graphics* graphics, Gdiplus::Point pos) override;
	virtual void SetMotion(double pressure) override;

private:
	CPolygon mImage;	///< The polygon this class is modifying
	CMotionSink mSink;	///< The motion sink for this component
	double mLastPressure = 0;	///< The last pressure provided
	std::shared_ptr<CWavChannel> wC;	///< The wave channel for this shape
};

