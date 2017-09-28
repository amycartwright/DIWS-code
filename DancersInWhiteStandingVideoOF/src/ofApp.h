////////////////////////// Dancers In White, Standing  ///////////////////////////
/////////////////////          Amy Cartwright     ///////////////////////


#pragma once

#include "ofMain.h"
#include "FaceTracker.h"
#include "Message.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber video; //webcam
    ofVideoPlayer film; //The film that is played underneith the movement
    ofxDLib::FaceTracker ft;
    Message message;
    
    int tDetect;
    int sec;
};
