//
//  EnvelopeControls.cpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#include "EnvelopeControls.hpp"

FMSynth::envParameters FMSynth::envSettings[FMSynth::noOfEnvelopes];

/** EnvelopeControls Constructor */
EnvelopeControls::EnvelopeControls()
{
    String paramNames[4] = { "atkDial", "decDial", "susDial", "relDial" };
    
    auto lblAlign = new Justification(juce::Justification::centred);
    
    char tags[5] = "ADSR";
    
    for(int i=0;i<4;i++) // Sets AD_R ranges 0-10000ms, and __S_ 0-1.
    {
        auto* dial = new MatrixSlider();
        
        dial->setRange(0, i != 2? 10000 : 1);
        dial->setValue(i != 2? 0 : 1);
        dial->setSkewFactorFromMidPoint(i != 2 ? 2000.0 : 0.5);
        dial->setComponentID(paramNames[i]);
        dial->setBounds(60 * i, 20, 50, 50);
        dial->addListener(this);
        addAndMakeVisible(dial);
        dials.add(dial);
        
        // A / D / S / R Labels
        auto* tagLbl = new Label();
        tagLbl->attachToComponent(dial, false);
        tagLbl->setText(juce::String::charToString(tags[i]), dontSendNotification);
        tagLbl->setJustificationType(*lblAlign);
        tagLabels.add(tagLbl);
        
        // Display current values
        auto* lbl = new Label();
        lbl->setSize( dial->getWidth(), dial->getHeight() );
        lbl->setTopLeftPosition(dial->getPosition());
        lbl->setComponentID(paramNames[i] << "_lbl");
        lbl->setText("", dontSendNotification);
        lbl->setJustificationType(*lblAlign);
        addAndMakeVisible(lbl);
        lbl->setVisible(false);
        labels.add(lbl);
    }
    
    envSelection.setComponentID("envSelect");
    envSelection.setBounds(0, 80, 60, 20);
    
    for(int i=0;i<FMSynth::noOfEnvelopes;i++) // Adds the options to the "Envelope Selection" ComboBox for each envelope
    {
        envSelection.addItem(std::to_string(i + 1), i + 1);
    }
    envSelection.setSelectedId(1);
    envSelection.addListener(this);
    addAndMakeVisible(envSelection);
}

/** EnvelopeControls Destructor */
EnvelopeControls::~EnvelopeControls()
{
    
}

/** Updates the properties of the envelope when a slider is adjusted */
void EnvelopeControls::sliderValueChanged(Slider* slider)
{
    int i = -1;
    
    String newText = slider->getTextFromValue(slider->getValue());
    
    if(slider->getComponentID()=="atkDial")
    {
        i = 0;
        FMSynth::setEnvA(envSelection.getSelectedId() - 1, slider->getValue());
    }
    else if(slider->getComponentID()=="decDial")
    {
        i = 1;
        FMSynth::setEnvD(envSelection.getSelectedId() - 1, slider->getValue());
    }
    else if(slider->getComponentID()=="susDial")
    {
        i = 2;
        FMSynth::setEnvS(envSelection.getSelectedId() - 1, slider->getValue());
    }
    else if(slider->getComponentID()=="relDial")
    {
        i = 3;
        FMSynth::setEnvR(envSelection.getSelectedId() - 1, slider->getValue());
    }
    
    if(i==2) // Don't truncate the Sustain label: truncate the others at decimal point.
    {
        labels[i]->setText(dials[i]->getTextFromValue( dials[i]->getValue() ), dontSendNotification);
    }
    else
    {
        labels[i]->setText(dials[i]->getTextFromValue( dials[i]->getValue()).substring(0, dials[i]->getTextFromValue(dials[i]->getValue()).lastIndexOfChar('.')), dontSendNotification);
    }
}

void EnvelopeControls::sliderDragStarted(Slider* slider)
{
    findChildWithID(slider->getComponentID() + "_lbl")->setVisible(true);
}

void EnvelopeControls::sliderDragEnded(Slider* slider)
{
    findChildWithID(slider->getComponentID() + "_lbl")->setVisible(false);
}

/** Updates the values of sliders when a different envelope is selected */
void EnvelopeControls::comboBoxChanged(ComboBox* combo)
{
    dials[0]->setValue(FMSynth::getEnvA( combo->getSelectedItemIndex() ));
    dials[1]->setValue(FMSynth::getEnvD( combo->getSelectedItemIndex() ));
    dials[2]->setValue(FMSynth::getEnvS( combo->getSelectedItemIndex() ));
    dials[3]->setValue(FMSynth::getEnvR( combo->getSelectedItemIndex() ));
}
