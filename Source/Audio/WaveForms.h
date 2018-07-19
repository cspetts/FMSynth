/*
 *  SinOscillator.h
 *  sdaAudioMidi
 *
 *  Created by tjmitche on 11/11/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


/*
 * Extended to provide more than just a SinOscillator.
 *
 */

#ifndef H_SINOSCILLATOR
#define H_SINOSCILLATOR

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"
#include <cmath>


/**
 Class for a sinewave oscillator
 */

class SinOscillator : public Oscillator
{
public:
	//==============================================================================
	/**
	 SinOscillator constructor
	 */
	SinOscillator();
	
	/**
	 SinOscillator destructor
	 */
	~SinOscillator();

	/**
	 function that provides the execution of the waveshape
	 */
	float renderWaveShape (const float currentPhase) override ;
	
private:

};

class SquareOscillator : public Oscillator
{
public:
    //==============================================================================
    /**
     SquareOscillator constructor
     */
    SquareOscillator();
    
    /**
     SquareOscillator destructor
     */
    ~SquareOscillator();
    
    /**
     function that provides the execution of the waveshape
     */
    float renderWaveShape (const float currentPhase) override;
    
private:
    
};

class SawOscillator : public Oscillator
{
public:
    //==============================================================================
    /**
     SquareOscillator constructor
     */
    SawOscillator();
    
    /**
     SquareOscillator destructor
     */
    ~SawOscillator();
    
    /**
     function that provides the execution of the waveshape
     */
    float renderWaveShape (const float currentPhase) override;
    
private:
    
};

class TriOscillator : public Oscillator
{
public:
    //==============================================================================
    /**
     SquareOscillator constructor
     */
    TriOscillator();
    
    /**
     SquareOscillator destructor
     */
    ~TriOscillator();
    
    /**
     function that provides the execution of the waveshape
     */
    float renderWaveShape (const float currentPhase) override;
    
private:
    
};

class Saw123Oscillator : public Oscillator
{
public:
    //==============================================================================
    /**
     SquareOscillator constructor
     */
    Saw123Oscillator();
    
    /**
     SquareOscillator destructor
     */
    ~Saw123Oscillator();
    
    /**
     function that provides the execution of the waveshape
     */
    float renderWaveShape (const float currentPhase) override;
    
private:
    
};

#endif //H_SINOSCILLATOR
