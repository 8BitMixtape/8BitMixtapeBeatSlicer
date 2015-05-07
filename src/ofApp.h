#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOsc.h"

#include "range_manager.h"
#include "sample_window.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        sample_window sample_preview;


        ofxUISuperCanvas *gui0;
        ofxOscReceiver receiver;

        int pot1, pot2, pot3, zoom;
//        unsigned char zoom
        float window_width;

        void guiEvent(ofxUIEventArgs &e);

        void audioOut(float * input, int bufferSize, int nChannels);


        ofSoundStream soundStream;


        float 	pan;
        int		sampleRate;
        bool 	bNoise;
        float 	volume;
        vector <float> lAudio;
        vector <float> rAudio;

        unsigned long t;
        unsigned long loop_start;
        unsigned long loop_t;

        RangeManager range1;

        bool paused;
        bool loop;
        bool loop_play;

        int saveX;
        int dragX;


        void updateLoopStart();
};
