//
//  AutomationPanel.cpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#include "AutomationPanel.hpp"

/** autoCtrlPanel Constructor */
autoCtrlPanel::autoCtrlPanel()
{
    char opIDs[15] = "ABCDEFGHIJKLM";
    
    envSelect.addSectionHeading("Env");
    for(int i=0;i<FMSynth::noOfEnvelopes;i++)
    {
        envSelect.addItem(static_cast<String>(i+1), i+1);
    }
    envSelect.setSelectedId(1);
    
    opSelect.setComponentID("opSelect");
    opSelect.addSectionHeading("Operator");
    
    for(int i=0;i<FMSynth::noOfOperators;i++)
    {
        opSelect.addItem(juce::String::charToString(opIDs[i]), i+1);
    }
    opSelect.setSelectedId(1);
    
    paramSelect.addItem("Ratio", 1);
    paramSelect.addItem("Offset", 2);
    paramSelect.addItem("Amplitude", 3);
    for(int i=0;i<FMSynth::noOfOperators;i++)
    {
        paramSelect.addItem("Mod " + static_cast<String>(i+1) + "->" + "1", i+4);
    }
    paramSelect.setSelectedId(1);
    
    btnEdit.setButtonText("Add");
    
    opSelect   .addListener(this);
    envSelect  .addListener(this);
    paramSelect.addListener(this);
    btnEdit    .addListener(this);
    
    envSelect  .setBounds(0,   0,  50,  20);
    opSelect   .setBounds(50,  0,  50,  20);
    paramSelect.setBounds(100, 0,  80,  20);
    btnEdit    .setBounds(60, 40,  50,  20);
    autoList   .setBounds(0,  60, 300, 200);
    autoListPanel   .setBounds(0,  60, 300, 200);
    
    
    auto justTest = new Justification(juce::Justification::topLeft);
    autoList.setJustificationType(*justTest);
    
    addAndMakeVisible(envSelect);
    addAndMakeVisible(opSelect);
    addAndMakeVisible(paramSelect);
    addAndMakeVisible(btnEdit);
    addAndMakeVisible(autoList);
    addAndMakeVisible(autoListPanel);
    
}

/** autoCtrlPanel Destructor */
autoCtrlPanel::~autoCtrlPanel()
{
    
}

/** Updates the string that will be added/removed from the automation display. Makes the "Add" button invisible if there is already automation on the track. */
void autoCtrlPanel::comboBoxChanged(ComboBox* combo)
{
    char opIDs[15] = "ABCDEFGHIJKLM";
    
    btnEdit.setVisible(true);
    if(combo->getComponentID()=="opSelect")
    {
        for(int i=0;i<FMSynth::noOfOperators;i++)
        {
            int x = paramSelect.getSelectedItemIndex();
            paramSelect.changeItemText(4+i, "Mod " + juce::String::charToString(opIDs[i]) + "->" + combo->getText());
            paramSelect.setSelectedItemIndex(x);
        }
    }
    
    textToChange.clear();
    textToChange << "Envelope " << envSelect.getText() << " : Operator " << opSelect.getText() << " : " << paramSelect.getText() << "\n";
    
    if(isAutomated(envSelect.getSelectedItemIndex(), opSelect.getSelectedItemIndex(), paramSelect.getSelectedItemIndex()) == true )
    {
        btnEdit.setVisible(false);
    }

}

/** Listens for whether the add/remove button has been clicked, and calls the function within autoListPanel to create a new automation. */
void autoCtrlPanel::buttonClicked(Button* button)
{
    autoListPanel.createNewAutomation( textToChange,
                                       envSelect.getSelectedItemIndex(),
                                       opSelect.getSelectedItemIndex(),
                                       paramSelect.getSelectedItemIndex(),
                                       1
                                     );
    btnEdit.setVisible(false);
}

/** Checks whether the current op/env/param settings have automation applied */
bool autoCtrlPanel::isAutomated(int op, int env, int param)
{
    for(int i=0;i<autoListPanel.parameters.size();i++)
    {
        if( (env   == autoListPanel.parameters[i]->envNo) &&
            (op    == autoListPanel.parameters[i]->opNo ) &&
            (param == autoListPanel.parameters[i]->paramNo))
        {
            return true;
        }
    }
    return false;
}
