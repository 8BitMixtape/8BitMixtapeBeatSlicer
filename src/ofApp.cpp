#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    //ofEnableAlphaBlending();
    //ofEnableAntiAliasing();

    ofBackground(0,0,0);

    receiver.setup(9090);


    pot1 = 0;
    pot2 = 0;
    pot3 = 0;

    window_width = 0;

    gui0 = new ofxUISuperCanvas("8BitMixtapeBeatSlicer");

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

    loop_start = 0;
    loop_t = 0;
    loop = false;
    loop_play = false;

    paused = false;
    saveX = 0;
    dragX = 0;

}


void ofApp::guiEvent(ofxUIEventArgs &e)
{
    sample_preview.setPot(pot1, pot2, pot3);
    sample_preview.setZoom(zoom);
    // sample_preview.update();
}

void ofApp::audioOut(float *output, int bufferSize, int nChannels)
{
    //if(paused) return;

    unsigned long time_t;
    unsigned char snd;

    for (int i = 0; i < bufferSize; i++)
        {

            if (loop)
                {

                if(loop_play)
                {

                    if(loop_t > (loop_start+range1.getRangeMax(8000)))
                        {
                            loop_play = !loop_play;
                            loop_t = loop_start + range1.getRangeMin(8000);
                        }

                    loop_t++;
                    time_t = loop_t;

                }
                }else{
                t++;
                time_t = t;
            }


            snd = sample_preview.genSound(time_t>>2);


            lAudio[i] = output[i*nChannels    ] = (float) snd/255.0f * volume;
            rAudio[i] = output[i*nChannels + 1] = (float) snd/255.0f * volume;
        }
}

//--------------------------------------------------------------
void ofApp::update()
{

    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);

        // check for mouse moved message
        if(m.getAddress() == "/seq"){
            // both the arguments are int32's

            pot1 = m.getArgAsInt32(0);
            pot2 = m.getArgAsInt32(1);
            sample_preview.setPot(pot1, pot2, pot3);

            //mouseX = m.getArgAsInt32(0);
            //mouseY = m.getArgAsInt32(1);
            loop_play = !loop_play;
        }

    }


    if(paused) return;
    sample_preview.update(t >> 2);
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0,0,0);

    // ofDrawBitmapString("dragX: " + ofToString(dragX), 100,100);

    ofDrawBitmapString("time: " + ofToString(t) + " loop_start:" + ofToString(loop_start) + " loop_t:" + ofToString(loop_t) + " loop_end:" + ofToString(loop_start + range1.getRangeMax(8000))  , 200,200);

    // ofGetWidth()/8000.0f

    // ofRect();

    //ofDrawBitmapString("8BitMixtapeSampleViewer 0.1", 50,50);
    sample_preview.draw(0,300, window_width);
    range1.draw();
}

//--------------------------------------------------------------
void ofApp::updateLoopStart()
{
    loop_start = t + range1.getRangeMin(8000);
    loop_t = loop_start;
}

void ofApp::keyPressed(int key)
{
    if (key == 'f')
        {
            ofToggleFullscreen();
            return;
        }

    if  (key == 'l')
        {
        loop = !loop;

            if (loop)
            {
                updateLoopStart();
                //paused = true;
            }
            return;
        }

    if (key == 'p')
    {
        loop_play = !loop_play;
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
    if (key== ' ')
        {
            paused = !paused;
            if (paused)
            {
                soundStream.stop();
            }else{
                soundStream.start();
        }
            return;
        };

    sample_preview.setFormula(songs);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

    if (y > 555)
        {
            dragX = (saveX - x)*100;

            sample_preview.update(t+(dragX));
            //dragX = 0;
        }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if ( y > 555)
        {
            saveX = x;
        }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    // t += dragX;
    if ( y > 555)
        {
            t = (t+dragX);
            dragX = 0;
        }

    updateLoopStart();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
