//
//  Matrix.hpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Audio/Synth.hpp"

#include "MatrixSlider.hpp"

/* Matrix Class (A Frame for aligning the MatrixSliders and Buttons) */
class Matrix : public Component,
public Slider::Listener,
public Button::Listener,
public ChangeBroadcaster
{
public:
    
    /** Matrix Constructor */
    Matrix ();
    
    /** Matrix Destructor */
    ~Matrix();
    
    /** Places child component within the Matrix */
    void setMatrixLayout(Component*, const String&, int, const Point<int>&);
    
    /** Identifies which button is clicked and calls functions to update slider/synth variables */
    void buttonClicked(Button*) override;
    
    /** Defines size of the matrix panel */
    static const int matrixSize = 300;
    
    /** Keeps track of the current Operator */
    int currentOperator = 0;
    
private:
    
    /** Matrix Painting override */
    void paint (Graphics&) override;
    
    /**  To change Text inside Matrix Labels */
    String currentLabel;
    int sliderCounter;
    
    /** Makes Label Visible on Click */
    void sliderDragStarted(Slider*) override;
    
    /** Updates Label Value as rotary slider is dragged */
    void sliderValueChanged(Slider*) override;
    
    /** Makes Label Invisible when slider is released */
    void sliderDragEnded(Slider*) override;
    
    /** All Labels, Sliders and Buttons within Matrix() Construction are assigned to these to prevent *the dreaded* leak */
    OwnedArray<Label> labels;
    OwnedArray<MatrixSlider> sliders;
    OwnedArray<TextButton> buttons;
};


#endif /* Matrix_hpp */
