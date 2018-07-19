//
//  MatrixSlider.hpp
//  SDA-TEST
//
//  Created by Charles Spettigue on 25/01/2018.
//
//

#ifndef MatrixSlider_hpp
#define MatrixSlider_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

/** Sliders to place inside the Matrix, with values & ranges already set.  */
class MatrixSlider : public Slider
{
public:
    /** Matrix Slider Constructor */
    MatrixSlider();
    
    /** Matrix Slider Destructor */
    ~MatrixSlider();
    
private:
    //  void paint (Graphics&) override;
    
};
#endif /* MatrixSlider_hpp */
