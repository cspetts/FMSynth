//
//  OscillatorModifiers.hpp
//  JuceBasicWindow
//
//  Created by Charles Spettigue on 29/10/2017.
//
//

#ifndef synth_h
#define synth_h


#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveForms.h"
#include "Envelope.hpp"




/** Generates waveforms for FMSynth */
class Operator
{
public:
    
    Operator();
    ~Operator() {};
    
    
/** Sets the ratio for the operator */
    void   setRatio(double newRatio)    { d_ratio = newRatio; };
/** Retrieves current ratio for the operator */
    double getRatio()                   { return d_ratio; };

/** Sets the offset for the operator */
    void   setOffset(double newOffset)  { d_offset = newOffset; };
/** Retrieves current offset for the operator */
    double getOffset()                  { return d_offset; };
  
/** Sets the frequency for the operator */
    void   setFrequency(double noteFreq)    { d_frequency = noteFreq; }
/** Retrieves current frequency for the operator */
    double getFrequency()                   { return d_frequency; }
 
/** Sets the amplitude for the operator */
    void   setAmplitude(double newAmp)      { d_amplitude = newAmp; };
/** Retrieves current amplitude for the operator */
    double getAmplitude()                   { return d_amplitude; };

/** Sets the waveform for the operator */
    void setWaveform(int newWaveform)       { defineOscillator(newWaveform); }
/** Retrieves current waveform for the operator */
    int  getWaveform()                      { return  currentWaveForm; }
    
/** Sets waveform for the oscillator*/
    void defineOscillator(int oscillatorValue);
    
/** Oscillator (Inherits from different waveform classes & actually generates the waveform) */
    ScopedPointer<Oscillator> oscillator;
    
private:

    double d_ratio = 1.0;
    double d_offset = 0.0;
    double d_frequency = 0.0;
    double d_amplitude = 1.0;
    int currentWaveForm = 0;
    
};



/** Generates the waveform for a single voice */
class FMSynth
{
public:
    
/* FMSynth Constructor/Destructor */
        /** FMSynth Constructor */
    FMSynth();
        /** FMSynth Destructor */
    ~FMSynth();
    
        /** Used to initialise the voice frequency, velocity, and envelope positions/states. */
    void voiceReset(double freq, int vel)
    {
        setFrequency(freq);
        setVelocity(vel);
        state = active;
        resetEnvelopes();
    }
    
        /** Used to reset the envelopes on note start. */
    void resetEnvelopes() { for(int i = 0; i<noOfEnvelopes; i++) { envelopes[i].resetPos(); envelopes[i].envActive = true; }}
    
        /** Used by parent to check if it is okay to destroy this voice now. */
    enum State {
        active = 0,
        released = 1,
        inactive = 2
    };
    State state = active;
    
        /** Called by parent to enter release */
    void noteReleased();
    
/* Velocity Set/Get */
        /** Sets the note velocity for this voice */
    void   setVelocity(double newVelo) { velocity = newVelo; }
        /** Returns the note velocity for this voice */
    double getVelocity()             { return velocity; }
 
/* Frequency Set/Get */
        /** Sets the note frequency for this voice */
    void   setFrequency(double newFreq);
        /** Returns the note frequency for this voice */
    double getFrequency()             { return frequency; }
    
/* Envelope Setting Accessors */
        /** Sets the envelope Attack for the specified envelope */
    static void setEnvA(int envNo, double val) { envSettings[envNo].atk = val; }
        /** Sets the envelope Decay for the specified envelope */
    static void setEnvD(int envNo, double val) { envSettings[envNo].dec = val; }
        /** Sets the envelope Sustain for the specified envelope */
    static void setEnvS(int envNo, double val) { envSettings[envNo].sus = val; }
        /** Sets the envelope Release for the specified envelope */
    static void setEnvR(int envNo, double val) { envSettings[envNo].rel = val; }

        /** Returns the envelope Attack for the specified envelope */
    static double getEnvA(int envNo) { return envSettings[envNo].atk; }
        /** Returns the envelope Decay for the specified envelope */
    static double getEnvD(int envNo) { return envSettings[envNo].dec; }
        /** Returns the envelope Sustain for the specified envelope */
    static double getEnvS(int envNo) { return envSettings[envNo].sus; }
        /** Returns the envelope Release for the specified envelope */
    static double getEnvR(int envNo) { return envSettings[envNo].rel; }
    
/* Operator Setting Accessors */
        /** Sets the Frequency for the specified Operator */
    static void setOpFreq     (int opNo, double val) { opSettings[opNo].freq = val; }
        /** Sets the Ratio for the specified Operator */
    static void setOpRatio    (int opNo, double val) { opSettings[opNo].ratio = val; }
        /** Sets the Offset for the specified Operator */
    static void setOpOffset   (int opNo, double val) { opSettings[opNo].offset = val; }
        /** Sets the Amplitude for the specified Operator */
    static void setOpAmplitude(int opNo, double val) { opSettings[opNo].amplitude = val; }
        /** Sets the Waveform for the specified Operator */
    static void setOpWaveform (int opNo, double val) { opSettings[opNo].wform = val; }
    
        /** Returns the Frequency for the specified Operator */
    static double getOpFreq     (int opNo) { return opSettings[opNo].freq; }
        /** Returns the Ratio for the specified Operator */
    static double getOpRatio    (int opNo) { return opSettings[opNo].ratio; }
        /** Returns the Offset for the specified Operator */
    static double getOpOffset   (int opNo) { return opSettings[opNo].offset; }
        /** Returns the Amplitude for the specified Operator */
    static double getOpAmplitude(int opNo) { return opSettings[opNo].amplitude; }
        /** Returns the Waveform for the specified Operator */
    static double getOpWaveform (int opNo) { return opSettings[opNo].wform; }
    
/** Operator Variables */
    static const int noOfOperators = 4;
    Operator operators[noOfOperators];
    
/** Envelope Variables */
    static const int noOfEnvelopes = 5;
    Envelope envelopes[noOfEnvelopes];
    
/** Function for updating Modulation Indexes */
    static void setModulationIndex(int car, int mod, double value) { modulationIndexs[car][mod] = value; };
    
/** Automation Parameter Accessors */
    static void setAutomation(int env, int oper, int param, float value) { autoParams[env][oper][param] = value; };
    
/** Generate the waveform */
    double RenderWaveForms();

private:
    
/** non-static freq / vel values */
    double frequency = 0;
    int velocity = 0;
    
    
/** Modulation Indexs (static) */
    static double modulationIndexs[noOfOperators][noOfOperators];
    
/** Operator/Envelope Variables */
    double opOut[noOfOperators];
    double envOut[noOfEnvelopes];      
    
/** Env Settings */
    struct envParameters
    {
        double atk;
        double dec;
        double sus;
        double rel;
    };
    static envParameters envSettings[noOfEnvelopes];
    
/** Op Settings */
    struct operatorParameters
    {
        double freq;
        double ratio;
        double offset;
        double amplitude;
        double wform;
    };
    static operatorParameters opSettings[noOfOperators];
    
// Holds level of automation for each parameter
/** Per envelope, the third dimension of the array will hold automation data for each envelope:
  * Ratio @ [1], Offset @ [2], Amplitude @ [3], then ModIndex @ [4 to noOfOperators+3];
  * This allows for self-feedback in a later expansion.
  */
    static double autoParams[noOfEnvelopes][noOfOperators][noOfOperators + 3];
   
/** Method for summing the automation for all envelopes on a particular parameter*/
    double getEnvAutomation(int opNumber, int paramNumber);

    double dbtoa(double in);
};

#endif
