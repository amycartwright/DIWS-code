//////////////////////////      Dancers In White, Standing  ///////////////////////////
//////////////////////              Amy Cartwright             ///////////////////////

// Class for the gui

#include "GUI.h"

GUI::GUI(){
    
}
//--------------------------------------------------------------
void GUI::init(){
    //Set up for the gui
    gui.setup();
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(trackHs.set("Track Hue/Saturation", true));
 
    threshold = 40.8;
    targetColor = (ofColor::crimson);
}
//--------------------------------------------------------------
void GUI::run(){
    //Draw Gui
    ofPushMatrix();
    gui.draw();
    ofTranslate(8, 75);
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(-3, -3, 64 + 6, 64 + 6);
    ofSetColor(targetColor);
    ofDrawRectangle(0, 0, 64, 64);
    ofPopMatrix();
}
