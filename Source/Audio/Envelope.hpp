//
//  Envelope.hpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 06/12/2017.
//
//

#ifndef Envelope_hpp
#define Envelope_hpp

#include <stdio.h>

#include "../JuceLibraryCode/JuceHeader.h"

class Envelope {
public:
    //==============================================================================
    /**
     Envelope constructor
     */
    Envelope();
    
    /**
     Envelope destructor
     */
    ~Envelope();
    
        /** Sets the attack time in samples (input in ms) */
    void setAttack(float attack) { atk = 0.001 * attack * sampleRate; };
        /** Returns the attack time in ms */
    float getAttack() { return atk / (sampleRate * 0.001); };
    
        /** Sets the decay time in samples (input in ms) */
    void setDecay(float decay) { dec = atk + (0.001 * decay * sampleRate); };
        /** Returns the decay time in ms */
    float getDecay() { return ( dec - atk ) / (sampleRate * 0.001); };
    
        /** Sets the sustain value (0-1) */
    void setSustain(float sustain) { sus = sustain; };
        /* Returns the sustain value */
    float getSustain() { return sus; };
    
        /** Sets the release time in samples (input in ms) */
    void setRelease(float release) { rel = 0.001 * release * sampleRate; };
        /** Returns the release time in samples (input in ms) */
    float getRelease() { return rel; }
    
/** Resets the value of */
    void resetPos() { pos = 0; }
    
    void setSampleRate(float sr) { sampleRate = sr; };
    
/** Function to reset the envelope parameters */
    void reset();
    
/** Function that return the envelope value */
    double renderEnvelope(int state);
   
    bool envActive = true;
    
private:
    float lastValue;
    float atk, dec, sus, rel;
    int pos = 0;
    float sampleRate = 44100;
    
};

// ====================================================================================


#endif /* Envelope_hpp */






