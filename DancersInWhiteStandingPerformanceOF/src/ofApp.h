//////////////////////////      Dancers In White, Standing  ///////////////////////////
//////////////////////              Amy Cartwright             ///////////////////////

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxCv.h"
#include "GUI.h"
#include "Message.h"

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void kinectExit();
    void debug();
    void calibrate(ofVec3f);

    ofxKinect kinect;
    ofxCvGrayscaleImage grayImg; // grayscale depth image
    ofxCv::ContourFinder contourFinder;
    ofSoundPlayer soundScore;
    
    float closestColorZ; //stores the z co-ordinate
    int angle; //used to calibrate the kinect
    int count;
    
    deque <ofVec3f> currentPos;
    vector <ofVec3f> storedData;
    ofVec3f avg;
    
    Message message;
    GUI gui;
    
    
    
    
    
    
};

