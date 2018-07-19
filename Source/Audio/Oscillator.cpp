/*
 *  Oscillator.cpp
 *  sdaAudioMidi
 *
 *  Created by tjmitche on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Oscillator.h"


Oscillator::Oscillator()
{
	reset();
}

Oscillator::~Oscillator()
{

}

void Oscillator::setFrequency (float freq)
{
    frequency = freq < 0 ? freq * -1.0 : freq;
	phaseInc = (2 * M_PI * frequency ) / sampleRate ;
}

void Oscillator::setNote (int noteNum)
{
	setFrequency (440.f * pow (2, (noteNum - 69) / 12.0));
}

void Oscillator::setAmplitude (float amp)
{
	amplitude = amp;
}

void Oscillator::reset()
{
    phase = 0.f;
    sampleRate = 44100;
    setFrequency (440.f);
	setAmplitude (1.0);
}

void Oscillator::setSampleRate (float sr)
{
	sampleRate = sr;
	phaseInc = (2 * M_PI * frequency ) / sampleRate ; // Just to update the phaseInc
}

float Oscillator::nextSample()
{
	float out = renderWaveShape (phase ) * amplitude;
	phase = phase + phaseInc ;
	if(phase  > (2.f * M_PI))
		phase -= (2.f * M_PI);

	return out;
}

float Oscillator::renderWaveShape (const float currentPhase)
{
    return 0;
}
