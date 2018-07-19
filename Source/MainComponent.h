/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParentComponents.hpp"
#include "Audio/Synth.hpp"
#include "Audio/Envelope.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class MainComponent   : public Component,
                        public MidiInputCallback,
                        public AudioIODeviceCallback,
                        public ChangeListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();
    
// "Parent Components" (UI Panels)
    
/** UI Component: Envelope Control Panel (Contains ADSR Dials & Envelope Selector) */
    EnvelopeControls envCtrlPanel;
/** UI Component: Modulation Matrix (Contains the modulation selection buttons & Modulation Index Dials)  */
    Matrix modMatrix;
/** UI Component: Operator Panel (Contains Ratio/Offset/Waveform/Output Sliders) */
    FrequencyParams freqModifiers;
/** UI Component: Automation Panel (Contains the ) */
    autoCtrlPanel automationCtrl;
    
/** Function for handling change messages */
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
/** Storing data required by multiple classes in one place (for future) */
  //  static const int noOfOperators = 4;
  //  static const int noOfEnvelopes = 4;
    
/** Note to frequency function */
    double mtof(int note);
    
/** Array of FMSynth voices */
    OwnedArray<FMSynth> synthVoices;
    
   // static int noOfVoices;
/** Array of FMSynth voices [was used in static model] */
 //   FMSynth voices[12];
    
private:
    
/** Handles screen resize functions */
    void resized() override;
/** Overridden from MidiInputCallback, handles incoming MIDI */
    void handleIncomingMidiMessage (MidiInput*, const MidiMessage&) override;
    
    
/** Audio & MIDI Functionality provided here */
    AudioDeviceManager audioDeviceManager;
/** Overridden from AudioIODeviceCallback, handles synthesis function calls and audio output. */
    virtual void audioDeviceIOCallback(const float ** 	inputChannelData,
                                       int      numInputChannels,
                                       float ** outputChannelData,
                                       int      numOutputChannels,
                                       int      numSamples ) override;
    
/** Overridden from AudioIODeviceCallback, . */
    virtual void audioDeviceAboutToStart(AudioIODevice *device) override;
/** Overridden from AudioIODeviceCallback, handles synthesis function calls and audio output. */
    virtual void audioDeviceStopped() override;
    
    
    CriticalSection voiceLock;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
