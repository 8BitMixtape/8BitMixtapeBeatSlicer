#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    //ofEnableAlphaBlending();
    //ofEnableAntiAliasing();

    ofBackground(0,0,0);

    pot1 = 0;
    pot2 = 0;
    pot3 = 0;

    window_width = 0;

    gui0 = new ofxUISuperCanvas("8BitMixtapeSampleViewer");

    gui0->addIntSlider("pot1", 0, 255, &pot1);
    gui0->addIntSlider("pot2", 0, 255, &pot2);
    gui0->addIntSlider("pot3", 0, 255, &pot3);
    gui0->addIntSlider("zoom", 0, 10, &zoom);
    gui0->addSlider("width", 1, 1000, &window_width);

    ofAddListener(gui0->newGUIEvent, this, &ofApp::guiEvent);

    //sound setup

    int bufferSize		= 512;
    sampleRate 			= 44100;
    volume				= 0.1f;
    bNoise 				= false;

    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);

    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    t = 0;

    paused = false;


}


void ofApp::guiEvent(ofxUIEventArgs &e)
{
    sample_preview.setPot(pot1, pot2, pot3);
    sample_preview.setZoom(zoom);
   // sample_preview.update();
}

void ofApp::audioOut(float *output, int bufferSize, int nChannels)
{
    if(paused) return;
    for (int i = 0; i < bufferSize; i++){
        t++;
        unsigned char snd = sample_preview.genSound(t>>2);


        lAudio[i] = output[i*nChannels    ] = (float) snd/255.0f * volume;
        rAudio[i] = output[i*nChannels + 1] = (float) snd/255.0f * volume;
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    if(paused) return;
    sample_preview.update(t >> 2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);


    //ofDrawBitmapString("time: " + ofToString(65525 - (t>>2)), 200,200);

   // ofGetWidth()/8000.0f

   // ofRect();

    //ofDrawBitmapString("8BitMixtapeSampleViewer 0.1", 50,50);
    sample_preview.draw(0,300, window_width);
    range1.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
        return;
    }

    unsigned char songs = 0;

    if (key== '0') songs = 0;
    if (key== '1') songs = 1;
    if (key== '2') songs = 2;
    if (key== '3') songs = 3;
    if (key== '4') songs = 4;
    if (key== '5') songs = 5;
    if (key== '6') songs = 6;
    if (key== '7') songs = 7;
    if (key== '8') songs = 8;
    if (key== '9') songs = 9;
    if (key== ' ') {paused = !paused; return;};

    sample_preview.setFormula(songs);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
