#ifndef RANGE_SLIDER
#define RANGE_SLIDER

/********  Test sample for ofxInteractiveObject									********/
/********  Make sure you open your console to see all the events being output	********/


#pragma once

#include "ofxMSAInteractiveObject.h"

#define		IDLE_COLOR		0xFF0000
#define		OVER_COLOR		0x00FF00
#define		DOWN_COLOR		0x00FF00


class RangeSlider : public ofxMSAInteractiveObject {
protected:
    int saveX, saveY;
public:
    void setup() {

        setSize(20,200);
//        printf("MyTestObject::setup() - hello!\n");
        enableMouseEvents();
        enableKeyEvents();
    }


    void exit() {
//        printf("MyTestObject::exit() - goodbye!\n");
    }


    void update() {
        //		x = ofGetWidth()/2 + cos(ofGetElapsedTimef() * 0.2) * ofGetWidth()/4;
        //		y = ofGetHeight()/2 + sin(ofGetElapsedTimef() * 0.2) * ofGetHeight()/4;
    }


    void draw() {

        ofPushStyle();
        if(isMousePressed()) ofSetHexColor(DOWN_COLOR);
        else if(isMouseOver()) ofSetHexColor(OVER_COLOR);
        else ofSetHexColor(IDLE_COLOR);

        //ofLine(x,y);
        ofRect(x+10, y, 2, height);

        ofPopStyle();
    }

    virtual void onRollOver(int x, int y) {
//        printf("MyTestObject::onRollOver(x: %i, y: %i)\n", x, y);
    }

    virtual void onRollOut() {
//        printf("MyTestObject::onRollOut()\n");
    }

    virtual void onMouseMove(int x, int y){
//        printf("MyTestObject::onMouseMove(x: %i, y: %i)\n", x, y);
    }

    virtual void onDragOver(int x, int y, int button) {
        //printf("MyTestObject::onDragOver(x: %i, y: %i, button: %i)\n", x, y, button);
        this->x = x - saveX;    // update x position
            //this->y = y - saveY;    // update mouse y position
    }

    virtual void onDragOutside(int x, int y, int button) {
//        printf("MyTestObject::onDragOutside(x: %i, y: %i, button: %i)\n", x, y, button);
         this->x = x - saveX;    // update x position
    }

    virtual void onPress(int x, int y, int button) {
        //printf("MyTestObject::onPress(x: %i, y: %i, button: %i)\n", x, y, button);
        saveX = x - this->x;
        //saveY = y - this->y;
    }

    virtual void onRelease(int x, int y, int button) {
//        printf("MyTestObject::onRelease(x: %i, y: %i, button: %i)\n", x, y, button);
    }

    virtual void onReleaseOutside(int x, int y, int button) {
//        printf("MyTestObject::onReleaseOutside(x: %i, y: %i, button: %i)\n", x, y, button);
    }

    virtual void keyPressed(int key) {
//        printf("MyTestObject::keyPressed(key: %i)\n", key);
    }

    virtual void keyReleased(int key) {
//        printf("MyTestObject::keyReleased(key: %i)\n", key);
    }

};

#endif // RANGE_SLIDER

