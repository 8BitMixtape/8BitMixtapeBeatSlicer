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
        ofDrawBitmapString("Start " + ofToString(range1.position.x), range1.position);
        ofDrawBitmapString("Stop " + ofToString(range2.position.x), range2.position);

        ofPushStyle();
        ofSetColor(255,255,255,50);
        ofFill();
        ofRect(range1.position.x, range1.position.y, range2.position.x - range1.position.x, range1.height );
        ofPopStyle();
    }

    float getRangeMax()
    {
        return range2.position.x;
    }


    float getRangeMin()
    {
        return range1.position.x;
    }

private:
    RangeSlider range1;
    RangeSlider range2;

};




#endif // RANGE_MANAGER



