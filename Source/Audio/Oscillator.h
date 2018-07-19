/*
 *  Oscillator.h
 *  sdaAudioMidi
 *
 *  Created by tjmitche on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef H_Oscillator
#define H_Oscillator

#include "../JuceLibraryCode/JuceHeader.h"
#include <cmath>

/**
 Generic Oscillator Class.
 */

class Oscillator
{
public:
	//==============================================================================
	/**
	 Oscillator constructor
	 */
	Oscillator();
	
	/**
	 Oscillator destructor
	 */
	virtual ~Oscillator();
	
	/**
	 sets the frequency of the oscillator
	 */
	void setFrequency (float freq);
    float getFrequency () {return frequency;}
	
	/**
	 sets frequency using a midi note number
	 */
	void setNote (int noteNum);
	
	/**
	 sets the amplitude of the oscillator
	 */
	void setAmplitude (float amp);
	
	/**
	 resets the oscillator
	 */
	void reset();
	
	/**
	 sets the sample rate
	 */
	void setSampleRate (float sr);
	
	/**
	 Returns the next sample
	 */
	float nextSample();
	
	/**
	 function that provides the execution of the waveshape
	 */
	virtual float renderWaveShape (const float currentPhase);
	
private:
	float frequency = 440;
    float amplitude = 1.0;
    float sampleRate;
	float phase;
    float phaseInc;

};

#endif //H_Oscillator
