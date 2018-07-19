//
//  OscillatorModifiers.cpp
//  JuceBasicWindow
//
//  Created by Charles Spettigue on 29/10/2017.
//
//

#include "Synth.hpp"
//#include "ModMatrix.hpp"

double FMSynth::autoParams[FMSynth::noOfEnvelopes][FMSynth::noOfOperators][FMSynth::noOfOperators + 3];

/** Operator Constructor */
Operator::Operator()
{
    oscillator = new SinOscillator();
}

/** Called when a waveform is selected for this operator */
void Operator::defineOscillator(int newWaveform)
{

    if(newWaveform!=currentWaveForm)
    {
        switch(newWaveform)
        {
            case 1 :
                oscillator = new SinOscillator();       //Sine
                break;
            case 2 :
                oscillator = new SquareOscillator();   //Square
                break;
            case 3 :
                oscillator = new SawOscillator();       //Saw
                break;
            case 4 :
                oscillator = new TriOscillator();       //Tri
                break;
            default:
                oscillator = new SinOscillator();   // This should never happen
                break;
        }
        currentWaveForm = newWaveform;
    }
}


/** Constructor Function */
FMSynth::FMSynth()
{
    state = active;
    for (int i=0; i<noOfEnvelopes; i++) { envOut[i] = 0.0; }
    for (int i=0; i<noOfOperators; i++) { opOut[i] = 0.0; }
    
    for(int i=0;i<noOfEnvelopes;i++)
    {
        envelopes[i].setAttack (envSettings[i].atk);
        envelopes[i].setDecay  (envSettings[i].dec);
        envelopes[i].setSustain(envSettings[i].sus);
        envelopes[i].setRelease(envSettings[i].rel);
    }
    
    for(int i=0;i<noOfOperators;i++)
    {
        operators[i].setFrequency(opSettings[i].freq);
        operators[i].setRatio    (opSettings[i].ratio);
        operators[i].setOffset   (opSettings[i].offset);
        operators[i].setWaveform (opSettings[i].wform);
        operators[i].setAmplitude(opSettings[i].amplitude);
    }
    
}

/** Destructor Function */
FMSynth::~FMSynth()
{
}

void FMSynth::setFrequency(double newFreq)
{
    frequency = newFreq;
    
    for(int i=0;i<noOfOperators;i++)
    {
        operators[i].setFrequency(frequency);
    }
}
 
/** Function for finding total amount of automation on a parameter across all envelopes. */
double FMSynth::getEnvAutomation(int opNumber, int paramNumber)
{
    double out = 1.0;
    for(int envNumber=0;envNumber<noOfEnvelopes;envNumber++)
    {
        out *= 1.0 - autoParams[envNumber][opNumber][paramNumber] + (autoParams[envNumber][opNumber][paramNumber] * envOut[envNumber]) ;
    }
    return out;
}

void FMSynth::noteReleased()
{
    state = released;
    for(int i=0;i<noOfEnvelopes;i++)
    {
        envelopes[i].resetPos();
    }
}



/** Renders waveforms for Operators and calculates the new frequencies. Function is split into three parts: Local variable setting,
 *  Envelope manipulation, and synthesis.
 */
double FMSynth::RenderWaveForms()
{
    // ENVELOPE TICKING/VALIDATION & VARIABLE MANIPULATION
        int inactiveEnvs = 0;
        if(state!=inactive)
        {
            for(int i=0;i<noOfEnvelopes;i++)
            {
                if(envelopes[i].envActive==true)
                {
                    envOut[i] = envelopes[i].renderEnvelope(state);
                }
                else
                {
                    inactiveEnvs++;
                }
            }
            
            if(inactiveEnvs==noOfEnvelopes)
            {
               state = inactive;
            }
        }
    
    // Local variables to enable envelope manipulation on ALL parameters & get values
        double  localFrequency[noOfOperators], localRatio[noOfOperators], localOffset[noOfOperators], localAmplitude[noOfOperators];
        
        if(state != inactive)
        {
            for(int i=0;i<noOfOperators;i++)
            {
                localFrequency[i]   = operators[i].getFrequency();
                localRatio[i]       = operators[i].getRatio() * getEnvAutomation(i, 0);
                localOffset[i]      = operators[i].getOffset() * getEnvAutomation(i, 1);
                localAmplitude[i]   = dbtoa(operators[i].getAmplitude()) * getEnvAutomation(i, 2);
            }
        
        
    // THE SYNTHESIS
        double output = 0;
        for(int car=0;car<noOfOperators;car++)
        {
            double modulation = 0;
            for(int mod=0;mod<noOfOperators;mod++)
            {
                if(mod!=car)
                {
                    modulation += opOut[mod]                                            // Operator Output (depth)
                                * ( localFrequency[mod] * modulationIndexs[car][mod] )  // Modulation Index for this Modulator
                                *  getEnvAutomation(car, mod+3);                        // Envelope Automation for this Index
                }
            }
            double newFreq = ( localFrequency[car] * localRatio[car] ) + localOffset[car] + modulation; // Ratio/Offset/Modulation applied to carrier
            operators[car].oscillator->setFrequency(newFreq);
            opOut[car] = operators[car].oscillator->nextSample();
            
            output += opOut[car] * localAmplitude[car];
        }
        
    // OUTPUT
        return output;
    }
    else
    {
        return 0;
    }
}

double FMSynth::dbtoa(double dB)
{
    return pow(2, dB/6.0);
}

