/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

double FMSynth::modulationIndexs[FMSynth::noOfOperators][FMSynth::noOfOperators];
FMSynth::operatorParameters FMSynth::opSettings[noOfOperators];


//==============================================================================
MainComponent::MainComponent() : modMatrix ()
{
    setSize (650, 500);
    
    audioDeviceManager.initialiseWithDefaultDevices(2,2);
    audioDeviceManager.addAudioCallback(this);
    
    StringArray devices = MidiInput::getDevices();
    for(int i=0;i<devices.size();i++)
    {
        audioDeviceManager.setMidiInputEnabled (devices[i], true);
    }
    
    
    audioDeviceManager.addMidiInputCallback (String::empty, this);
    
// Make all parent components visible
    addAndMakeVisible(modMatrix);
    addAndMakeVisible(freqModifiers);
    addAndMakeVisible(envCtrlPanel);
    addAndMakeVisible(automationCtrl);
    
    freqModifiers.setSize(300, 60);
    freqModifiers.setTopLeftPosition(this->getWidth()-modMatrix.getWidth(),this->getHeight()-modMatrix.getHeight()-60);
    freqModifiers.addChangeListener(this);
    
    envCtrlPanel.setSize(300, 120);
    envCtrlPanel.setTopLeftPosition(0,0);
    envCtrlPanel.addChangeListener(this);
    
    automationCtrl.setSize(300, this->getHeight() - 120);
    automationCtrl.setTopLeftPosition(0, 120);
    
    modMatrix.addChangeListener (this);
}

MainComponent::~MainComponent()
{
    audioDeviceManager.removeMidiInputCallback(String::empty, this);
    audioDeviceManager.removeAudioCallback(this);
}


void MainComponent::resized() 
{
    modMatrix.setSize(300,300);
    modMatrix.setTopLeftPosition(
                                 this->getWidth()-modMatrix.getWidth(),
                                 this->getHeight()-modMatrix.getHeight());
    freqModifiers.setSize(300, 60);
    freqModifiers.setTopLeftPosition(
                                 this->getWidth()-modMatrix.getWidth(),
                                 this->getHeight()-modMatrix.getHeight()-60);
    envCtrlPanel.setSize(300, 60);
    envCtrlPanel.setTopLeftPosition(0,0);
    
    modMatrix.setTopLeftPosition(this->getWidth()-modMatrix.getWidth(),
                                 this->getHeight()-modMatrix.getHeight());
    freqModifiers.setTopLeftPosition(this->getWidth()-modMatrix.getWidth(),
                                     this->getHeight()-modMatrix.getHeight()-60);
}

    /** (Overridden from MidiInputCallback) Handles MIDI Data from listed sources */
void MainComponent::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
    
    ScopedLock sl(voiceLock);
    
    int note = message.getNoteNumber();
    int vel = message.getVelocity();
    
    if(message.isNoteOn())
    {
        
        auto* voice = new FMSynth();
        voice->setFrequency(mtof(note));
        voice->setVelocity(vel);
        synthVoices.add(voice);
        voice = NULL;
    }
    
    if(message.isNoteOff())
    {
        for(int i=0;i<synthVoices.size();i++)
        {
            if(synthVoices[i]->getFrequency()==mtof(note) && synthVoices[i]->state==FMSynth::active)
            {
                synthVoices[i]->noteReleased();
                break;
            }
        }
    }
    
    for(int i=0;i<synthVoices.size();i++)
    {
        if(synthVoices[i]->state==FMSynth::inactive)
        {
            synthVoices.remove(i);
        }
    }
    
}

void MainComponent::audioDeviceIOCallback(const float **inputChannelData,
                                          int   numInputChannels,
                                          float **outputChannelData,
                                          int numOutputChannels,
                                          int numSamples)
{
    float out;
    
    const float *inL = inputChannelData[0];
    const float *inR = inputChannelData[1];
    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
    while(numSamples--)
    {
        inL++;
        inR++;
        
        out = 0.0;
    
        ScopedLock sl(voiceLock);
        
        for(int i=0;i<synthVoices.size();i++)
        {
            out += synthVoices[i]->RenderWaveForms();
        }
        
        *outL = out;
        *outR = out;
        
        outL++;
        outR++;
    }
}

    /** Functoin to interpret Change Broadcast Messages */
void MainComponent::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (source == &freqModifiers) // Update the values in the audio engine with the slider value
    {
        FMSynth::setOpRatio     (modMatrix.currentOperator, freqModifiers.s_Ratio.getValue() );
        FMSynth::setOpOffset    (modMatrix.currentOperator, freqModifiers.s_Offset.getValue() );
        FMSynth::setOpWaveform  (modMatrix.currentOperator, freqModifiers.c_Waveforms.getSelectedId() );
        FMSynth::setOpAmplitude (modMatrix.currentOperator, freqModifiers.s_Output.getValue() );
    }
    else if (source == &modMatrix) // Update the slider values to the operator values for this operator
    {
        freqModifiers.s_Ratio.setValue          ( FMSynth::getOpRatio    (modMatrix.currentOperator) );
        freqModifiers.s_Offset.setValue         ( FMSynth::getOpOffset   (modMatrix.currentOperator) );
        freqModifiers.c_Waveforms.setSelectedId ( FMSynth::getOpWaveform (modMatrix.currentOperator) );
        freqModifiers.s_Output.setValue         ( FMSynth::getOpAmplitude(modMatrix.currentOperator) );
    }
    else if (source == 0)
    {
    }
}

    /** Begins the audio device listening when loading */
void MainComponent::audioDeviceAboutToStart(juce::AudioIODevice *audioDeviceManager)
{
}

    /** Stops the audio device listening after termination */
void MainComponent::audioDeviceStopped(void)
{
}

    /** MIDI Note to Frequency (Hz) Converter*/
double MainComponent::mtof(int in)
{
    double out = 440 * pow (2.0, (in - 69) / 12.0);
    return out;
}






