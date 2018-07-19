//
//  AutomationDisplay.hpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#ifndef AutomationDisplay_hpp
#define AutomationDisplay_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Audio/Synth.hpp"

class autoListPanel : public Component,
public Button::Listener
{
public:
/** autoListPanel Constructor */
    autoListPanel();
/** autoListPanel Destructor */
    ~autoListPanel();
    
/** Creates a new automation panel & calls the SetAutomation() in FMSynth */
    void createNewAutomation(String lblText,
                             int envelopeNumber,
                             int operatorNumber,
                             int parameterNumber,
                             double autoAmount);
    
/** Removes the automation associated with the button clicked and destroys associated components */
    void removeAutomation(int i);
    
/** Button listener override */
    void buttonClicked(Button*) override;
    
    struct AutoValues {
        int envNo;
        int opNo;
        int paramNo;
    };
    
    OwnedArray<AutoValues> parameters;
    
private:
    
    OwnedArray<Label> automationLabels;
    OwnedArray<Button> deleteButtons;
};



#endif /* AutomationDisplay_hpp */
