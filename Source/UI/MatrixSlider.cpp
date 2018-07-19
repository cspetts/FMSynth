//
//  MatrixSlider.cpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#include "MatrixSlider.hpp"

#define PI 3.141592654

/* ======================== */
/* MATRIXSLIDER FUNCTIONS */

/* MatrixSlider Creator */
MatrixSlider::MatrixSlider()
{
    setValue(0);
    setRange(0, 10);
    setSliderStyle(juce::Slider::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    setRotaryParameters(0, 2*PI, true);
}


/* MatrixSlider Destructor */
MatrixSlider::~MatrixSlider()
{
    DBG("MatrixSlider Destructor Called");
}
