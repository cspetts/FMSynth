//
//  FrequencyParams.hpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#ifndef FrequencyParams_hpp
#define FrequencyParams_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

#include "../Audio/Synth.hpp"

class FrequencyParams : public Component,
public Slider::Listener,
public ComboBox::Listener,
public ChangeBroadcaster
{
public:
    
    /** FrequencyParams Constructor */
    FrequencyParams();
    
    /** FrequencyParams Destructor */
    ~FrequencyParams();
    
    /** Repositions frequencyParams above the ModMatrix */
    void resized() override;
    
    /** Child components */
    Slider s_Ratio, s_Offset, s_Output;
    ComboBox c_Waveforms;
    
    StringArray CurrentWaveformList = { "Sine",
        "Square",
        "Saw",
        "Tri"
    };

    
private:
    
    void paint (Graphics&) override;
    
    Label ratioLbl, offsetLbl, wformLbl, outputLbl;
    
    /** Broadcasts Change Message when a slider within frequencyParams is changed */
    void sliderValueChanged(Slider*) override;
    
    /** Broadcasts Change Message when a ComboBox within frequencyParams is changed */
    void comboBoxChanged(ComboBox*) override;
    
};


#endif /* FrequencyParams_hpp */
