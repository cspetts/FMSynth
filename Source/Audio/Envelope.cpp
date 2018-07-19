//
//  Envelope.cpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 06/12/2017.
//
//

#include "Envelope.hpp"

/** Envelope Constructor */
Envelope::Envelope()
{
    reset();
}

/** Envelope Destructor */
Envelope::~Envelope()
{
}

/** Resets the envelope parameters. */
void Envelope::reset()
{
    atk = 0.0;
    dec = 0.0;
    sus = 0.0;
    rel = 0.0;
    pos = 0;
}

/** Returns the value of the envelope at the position. */
double Envelope::renderEnvelope(int state)
{
    float out = 0;
    pos++;
    
    switch(state) // 0 = active, 1 = release, 2 = inactive
    {
        case 0 :
            if(pos<=atk)            {  out = pos / atk;  }                                               // Attack State
            else if(pos<=dec)       {  out = 1.0 - ( ( (pos - atk) / (dec - atk) ) * (1 - sus) ); }      // Decay State
            else                    {  out = sus; pos--; }                                               // Sustain State
            lastValue = out;
            break;
        case 1 :
            if(pos<=rel)
            {
                out = lastValue - ( lastValue * pos / rel );                                                              // Release state.
            }
            else
            {
                out = 0;
                envActive = false;
            }
            break;
        case 2 :
            out = 0;
            break;
    }
    return out;
}


// ====================================================================================






