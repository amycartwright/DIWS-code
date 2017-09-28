//////////////////////////      Dancers In White, Standing  ///////////////////////////
//////////////////////              Amy Cartwright             ///////////////////////

#ifndef GUI_h
#define GUI_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"


#endif /* GUI_h */

class GUI{
    
public:
    
    GUI();
    
    ofxPanel gui;
    ofParameter<float> threshold; //Parameter for GUI threshold for blob tracking
    ofParameter<bool> trackHs; //Parameter for GUI tracking HSB true/false

    ofColor targetColor;
    
    void init();
    void run();
};
