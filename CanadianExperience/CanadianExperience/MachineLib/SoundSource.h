/**
 * \file SoundSource.h
 *
 * \author Tyler Nichols
 *
 * An interface for all sound sources
 *
 */

#pragma once

#include <memory>
#include "WavChannel.h"

 /**
  * An interface for sound sources
  */
class ISoundSource
{
public:
	/**
	* Sets the audio channel for this component
	* \param channel The audio channel for this component
	*/
	virtual void SetAudioChannel(std::shared_ptr<CWavChannel> channel) = 0;
};

