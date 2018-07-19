//
//  AutomationDisplay.cpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#include "AutomationDisplay.hpp"

/** autoListPanel Constructor */
autoListPanel::autoListPanel()
{
    
}

/** autoListPanel Destructor */
autoListPanel::~autoListPanel()
{
    
}

/** Creates components for the automation & calls the setAutomation function in FMSynth */
void autoListPanel::createNewAutomation(String lblText, int envelopeNumber, int operatorNumber, int parameterNumber, double value)
{
    
    auto* lbl = new Label();
    
    lbl->setText(lblText, dontSendNotification);
    lbl->setSize(250, 20);
    lbl->setTopLeftPosition(10, automationLabels.size() * 20);
    addAndMakeVisible(lbl);
    automationLabels.add(lbl);
    
    auto* btn = new TextButton();
    
    btn->setButtonText("x");
    btn->setBounds(lbl->getX() + 250, lbl->getY(), 20, 20);
    btn->addListener(this);
    addAndMakeVisible(btn);
    deleteButtons.add(btn);
    
    auto* vals = new AutoValues;
    vals->envNo  = envelopeNumber;
    vals->opNo   = operatorNumber;
    vals->paramNo= parameterNumber;
    parameters.add(vals);
    
    FMSynth::setAutomation(vals->envNo, vals->opNo, vals->paramNo, 1.0);
}

/** Removes the automation, relevant components and moves all further indexes up */
void autoListPanel::removeAutomation(int indexToRemove)
{
    AutoValues* vals = parameters[indexToRemove];
    FMSynth::setAutomation(vals->envNo, vals->opNo, vals->paramNo, 0.0);
    
    parameters.remove(indexToRemove);
    automationLabels.remove(indexToRemove);
    deleteButtons.remove(indexToRemove);
    
    for(int i=indexToRemove; i<automationLabels.size(); i++)
    {
        automationLabels[i]->setTopLeftPosition(automationLabels[i]->getX(), automationLabels[i]->getY()-20);
        deleteButtons[i]->setTopLeftPosition(deleteButtons[i]->getX(), deleteButtons[i]->getY()-20);
    }
}

/** Listener for the 'delete' buttons, finds which button was pressed and sends index to the "removeAutomation" function */
void autoListPanel::buttonClicked(Button* button)
{
    int i = 0;
    for(i=0;i<deleteButtons.size();i++)
    {
        if(button==deleteButtons[i])
        {
            break;
        }
    }
    removeAutomation(i);
}
