#ifndef RANGE_MANAGER
#define RANGE_MANAGER

#include "ofxMSAInteractiveObject.h"
#include "range_slider.h"

class RangeManager {
public:
    RangeManager()
    {
        range1.setPosition(0,300);
        range2.setPosition(400,300);
    }

    void update()
    {

    }

    void draw()
    {
        ofDrawBitmapString("Start " + ofToString(this->getRangeMin(8000)), range1.position);
        ofDrawBitmapString("Stop " +  ofToString(this->getRangeMax(8000)), range2.position);

        ofPushStyle();
        ofSetColor(255,255,255,50);
        ofFill();
        ofRect(range1.position.x, range1.position.y, range2.position.x - range1.position.x, range1.height );
        ofPopStyle();
    }

    float getRangeMax(float scale = 1.0f)
    {
        return (range2.position.x/ofGetWidth()) * scale ;
    }


    float getRangeMin(float scale = 1.0f)
    {
        return (range1.position.x/ofGetWidth()) * scale;
    }

private:
    RangeSlider range1;
    RangeSlider range2;

};




#endif // RANGE_MANAGER



