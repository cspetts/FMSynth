//
//  EnvelopeControls.hpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#ifndef EnvelopeControls_hpp
#define EnvelopeControls_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Audio/Synth.hpp"

#include "MatrixSlider.hpp"

class EnvelopeControls : public Component,
public Slider::Listener,
public ComboBox::Listener,
public ChangeBroadcaster
{
public:
    
    /** EnvelopeControls Constructor */
    EnvelopeControls();
    
    /** EnvelopeControls Destructor */
    ~EnvelopeControls();
    
private:
    
    /** Envelope controls & selection */
    ComboBox envSelection;
    
    /** Prevents leak of MatrixSlider dials */
    OwnedArray<MatrixSlider> dials;
    OwnedArray<Label> labels;
    OwnedArray<Label> tagLabels;
    
    /** "Component Listener" function overrides */
    void sliderDragStarted(Slider*) override;
    void sliderDragEnded(Slider*) override;
    void sliderValueChanged(Slider*) override;
    void comboBoxChanged(ComboBox*) override;
    
};



#endif /* EnvelopeControls_hpp */
