/*
 *  SinOscillator.cpp
 *  sdaAudioMidi
 *
 *  Created by tjmitche on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "WaveForms.h"

#define PI 3.141529654

/* ====================== */
     /** Sine Class */
/* ====================== */


SinOscillator::SinOscillator()
{
	reset();
}

SinOscillator::~SinOscillator()
{

}

    /** Sine wave generator */
float SinOscillator::renderWaveShape (const float currentPhase)
{
    float out = sin(currentPhase);
    return out;
}

/* ======================= */
     /** Square Class */
/* ======================= */

SquareOscillator::SquareOscillator()
{
    reset();
}

SquareOscillator::~SquareOscillator()
{
    
}

    /** Returns a square wave (50% Pulse width) */
float SquareOscillator::renderWaveShape (const float currentPhase)
{
    float out = currentPhase > PI ? 1.0 : -1.0;
    return out;
}

/* ======================= */
      /** Saw Class */
/* ======================= */

SawOscillator::SawOscillator()
{
    reset();
}

SawOscillator::~SawOscillator()
{
    
}

    /** Returns a saw wave */
float SawOscillator::renderWaveShape (const float currentPhase)
{
    return ( currentPhase / PI ) - 1.0;
}

/* ======================= */
    /** Triangle Class */
/* ======================= */

TriOscillator::TriOscillator()
{
    reset();
}

TriOscillator::~TriOscillator()
{
    
}

    /** Returns a triangle wave */
float TriOscillator::renderWaveShape (const float currentPhase)
{
    if (currentPhase < PI / 2.0)
        return 2.0 * currentPhase / PI;
    else if (currentPhase > 3.0 * PI / 2.0)
        return (2.0 * currentPhase / PI) - 4.0;
    else
        return 2.0 - (2.0 * currentPhase / PI);
    
    
    return ( currentPhase / PI ) - 1.0;
}

/* ========================================== */
    /** 123 Saw Class [ NOT YET IMPLEMENTED ] */
/* ========================================== */

Saw123Oscillator::Saw123Oscillator()
{
    reset();
}

Saw123Oscillator::~Saw123Oscillator()
{
    
}

    /** Returns a saw wave comprised of the first three harmonics */
float Saw123Oscillator::renderWaveShape (const float currentPhase)
{
    float out = 0.0;
    
    for(int x=0;x<3;x++)
    {
        out += sin( ( (x + 1.0) * currentPhase) / (2.0*PI) ) / (x + 1.0) ;
    }
    
    return out;
}


