//
//  Matrix.cpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#include "Matrix.hpp"

/* Matrix Creator */
Matrix::Matrix () //: synth (s)
{
    
    char operators[13] = "ABCDEFGHIJKL";
    
    String componentId;                  // Child Component Identifiers
    
    auto lblAlign = new Justification(juce::Justification::centred);
    
    for(int x=0;x<FMSynth::noOfOperators;x++)                    // Create & ID Mod-Matrix Buttons
    {
        for(int y=0;y<FMSynth::noOfOperators;y++)
        {
            if(x==y)        // Creates buttons for operators & aligns diagonally
            {
                componentId << "btnOperator" << operators[x];
                
                auto* btn = new TextButton();
                setMatrixLayout(btn, componentId, matrixSize/FMSynth::noOfOperators,
                                {matrixSize*x/FMSynth::noOfOperators, matrixSize*y/FMSynth::noOfOperators});
                btn->addListener(this);
                btn->setButtonText(juce::String::charToString(operators[x]));
                buttons.add (btn);
                
            }
            else            // Creates Matrix Sliders [rotary dials] to allow all operators to modulate all others
            {
                componentId << "matrixSlider" << x << "," << y;
                
                auto* sldr = new MatrixSlider();
                setMatrixLayout (sldr, componentId, matrixSize/FMSynth::noOfOperators,
                                 {matrixSize*x/FMSynth::noOfOperators, matrixSize*y/FMSynth::noOfOperators});
                sldr->addListener(this);
                sliders.add (sldr);
                
                componentId.clear();
                componentId << "matrixLabel" << x << "," << y;
                
                auto* lbl = new Label();
                setMatrixLayout (lbl, componentId, matrixSize/FMSynth::noOfOperators,
                                 {matrixSize*x/
                                     FMSynth::noOfOperators, matrixSize*y/FMSynth::noOfOperators});
                lbl->setText("0",juce::NotificationType::dontSendNotification);
                lbl->setVisible(false);
                lbl->setJustificationType(*lblAlign);
                labels.add(lbl);
            }
            componentId.clear();
        }
    }
}

/** Matrix Destructor */
Matrix::~Matrix()
{
    DBG("Matrix Destructor Called");
}

/** Places child components on array grid and gives the correct size) */
void  Matrix::setMatrixLayout (Component* component, const String& componentId, int size, const Point<int>& position)
{
    component->setComponentID (componentId);
    component->setSize (size, size);
    component->setTopLeftPosition (position);
    addAndMakeVisible(component);
}



/* Matrix Paint */
void  Matrix::paint(Graphics& tst)
{
    //DBG("Matrix Paint Called X");
    // tst.fillAll(Colours::gold);
}

/* Called when a slider is first clicked (overwridden from Slider::Listener) */
void  Matrix::sliderDragStarted(Slider* slider)
{
    currentLabel = slider->getComponentID().replace("matrixSlider", "matrixLabel", false);
    findChildWithID(currentLabel)->setVisible(true);
    
    sliderCounter=0;
    while(labels[sliderCounter]->getComponentID()!=currentLabel)
    {
        sliderCounter++;
    }
    
    DBG(sliderCounter);
    
    DBG("sDS Called.");
}

/* Called when slider is being dragged. */
void  Matrix::sliderValueChanged(Slider* slider)
{
    int i = sliderCounter;
    
    int mod = i / (FMSynth::noOfOperators - 1);
    int car = i % (FMSynth::noOfOperators - 1);
    
    if(car >= mod) // Correction for updating the appropriate modulation index in below function
    {
        car++;
    }
    
    FMSynth::setModulationIndex(car, mod, slider->getValue());
    
    labels[i]->setText(sliders[i]->getTextFromValue(sliders[i]->getValue()).substring(0,
                                                                                      sliders[i]->getTextFromValue(sliders[i]->getValue()).lastIndexOfChar('.')), dontSendNotification);
}

/* Called when a slider is no longer being interacted with (overridden from Slider::Listener) */
void  Matrix::sliderDragEnded(Slider* slider)
{
    findChildWithID(currentLabel)->setVisible(false);
}

/* Used to decide which operators are currently being used by freqModifiers */
void  Matrix::buttonClicked (Button* button)
{
    int btnCounter = 0;
    
    while(buttons[btnCounter]!=button)
    {
        btnCounter++;
    }
    currentOperator = btnCounter;
    sendChangeMessage();
}
