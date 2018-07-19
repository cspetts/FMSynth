//
//  FrequencyParams.cpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#include "FrequencyParams.hpp"

/** FrequencyParams Constructor */
FrequencyParams::FrequencyParams()
{
    
    s_Ratio.setSliderStyle(Slider::LinearBarVertical);
    s_Ratio.setComponentID("s_Ratio");
    s_Ratio.setValue(1.0);
    s_Ratio.setRange(0.0, 64.0, 0.0001);
    s_Ratio.setVelocityBasedMode(true);
    s_Ratio.setSkewFactorFromMidPoint(8.0);
    s_Ratio.addListener(this);
    addAndMakeVisible(s_Ratio);
    
    s_Offset.setSliderStyle(Slider::LinearBarVertical);
    s_Offset.setComponentID("s_Offset");
    s_Offset.setRange(-10000.0, 10000.0, 0.0001);
    s_Offset.setVelocityBasedMode(true);
    s_Offset.addListener(this);
    addAndMakeVisible(s_Offset);
    
    s_Output.setSliderStyle(Slider::LinearBarVertical);
    s_Output.setComponentID("s_Output");
    s_Output.setRange(-144.0, 0.0, 0.1);
    s_Output.setSkewFactorFromMidPoint(-36.0);
    s_Output.setVelocityBasedMode(true);
    s_Output.addListener(this);
    addAndMakeVisible(s_Output);
    
    c_Waveforms.addItemList(CurrentWaveformList, 1);
    c_Waveforms.setComponentID("c_Wforms");
    c_Waveforms.addListener(this);
    c_Waveforms.setText("Sine");
    addAndMakeVisible(c_Waveforms);
    
    ratioLbl.attachToComponent(&s_Ratio, false);
    ratioLbl.setText("ratio", dontSendNotification);
    
    offsetLbl.attachToComponent(&s_Offset, false);
    offsetLbl.setText("offset", dontSendNotification);
    
    wformLbl.attachToComponent(&c_Waveforms, false);
    wformLbl.setText("waveform", dontSendNotification);
    
    outputLbl.attachToComponent(&s_Output, false);
    outputLbl.setText("out (dB)", dontSendNotification);
    
}

/** FrequencyParams Destructor */
FrequencyParams::~FrequencyParams()
{
}


/** Called when a waveform is selected */
void  FrequencyParams::comboBoxChanged(ComboBox* wf_menu)
{
    sendChangeMessage();
}

/** Called when the ratio/offset values are selected */
void  FrequencyParams::sliderValueChanged(Slider* slider)
{
    sendChangeMessage();
}



void  FrequencyParams::paint(Graphics& x)
{
}

/** Set + position child components */
void  FrequencyParams::resized()
{
    s_Ratio.setBounds(10, 20, 60, 20);
    s_Offset.setBounds(75, 20, 60, 20);
    c_Waveforms.setBounds(140, 20, 80, 20);
    s_Output.setBounds(225,20,50,20);
}
