//
//  AutomationPanel.hpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#ifndef AutomationPanel_hpp
#define AutomationPanel_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

#include "../Audio/Synth.hpp"

#include "AutomationDisplay.hpp"

class autoCtrlPanel : public Component,
public Button::Listener,
public ComboBox::Listener

{
public:
    
    /** EnvelopeControls Constructor */
    autoCtrlPanel();
    
    /** EnvelopeControls Destructor */
    ~autoCtrlPanel();
    
    /* Child Components */
    /** Button to add/remove automation */
    TextButton btnEdit;
    /** Combo Boxes to select the parameter to automate, and envelope to automate with */
    ComboBox envSelect, opSelect, paramSelect;
    /** Label to display the list of current automations */
    Label autoList;
    
    /** Actually Changes Automation */
  //  void changeAutomation(double value);
    
private:
    
    //    void paint (Graphics&) override;
    bool isAutomated(int,int,int);
    
    autoListPanel autoListPanel;
    
    /* Button Listener functions */
    
/** Used to add/remove automation */
    void buttonClicked(Button*) override;
/** Used to identify the target envelope/parameter for automation */
    void comboBoxChanged(ComboBox*) override;
    
/** Stores the string for adding/removing automation to the label*/
    String textToChange;
    
};


#endif /* AutomationPanel_hpp */
