//////////////////////////      Dancers In White, Standing  ///////////////////////////
//////////////////////              Amy Cartwright             ///////////////////////

////Best compiled in release mode due to the use of the ofxDLib addon which does not run effectively in debug

/*
 A program used in erformance that collects movement data, manipulates and sends across to the arduino IDE where it is used to control 3 non-human dancers.
 */

//Elements of the program areinspired by http://www.creativeapplications.net/tutorials/arduino-servo-opencv-tutorial-openframeworks/

#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//---------------------------------------------------------------------------------------------
void ofApp::setup(){
    
    //Kinect setup
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    //Start playing the music score as soon as the program starts
    soundScore.load("Granular.mp3");
    
    //Setup for Message class which send serial data
    message.setup();
    
    //Allows for fine tuning of the blob detection
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(150);
    
    //Setup for GUI class
    gui.init();
   
}
//---------------------------------------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    
    if (kinect.isFrameNew()){
        contourFinder.setTargetColor(gui.targetColor, gui.trackHs ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinder.setThreshold(gui.threshold);
        contourFinder.findContours(kinect);
        
        //Update the cv image used for depth
        grayImg.flagImageChanged();
    }
    
    //End the program at the end of the music
    if (soundScore.getPosition() >= 0.96) {
        kinectExit();
        ofExit();
    }
}
//---------------------------------------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    kinect.draw(0, 0);

    ofSetLineWidth(2);
    contourFinder.draw();
    
    //Loop through the blobs and find their central point. Draw circle at central point
    int numOfBlobs = contourFinder.size();
    for(int i = 0; i < numOfBlobs; i++) {
        ofVec3f centroid = toOf(contourFinder.getCentroid(i));
        ofFill();
        ofSetColor(255);
        ofDrawCircle(centroid, 10);
        
        //Get the depth of the centroid by finding the greyscale colour at that point
        grayImg.setFromPixels(kinect.getDepthPixels());
        ofPixels pix = kinect.getDepthPixels();
        ofColor colorAtXY = pix.getColor(centroid.x, centroid.y);
        closestColorZ = colorAtXY.r;
        

        //callibrate the points collected from kinect based on kinect setup in particular space
        ofVec3f xyz = ofVec3f(centroid.x, centroid.y, closestColorZ);
        ofVec3f center = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 255/2);
        
        //translate to centre Point
        xyz.y -= center.y;
        xyz.z -= center.z;
        //rotate 45 degree - edit here for different spaces
        xyz.y = xyz.y*cos(PI/4) - xyz.z * sin(PI/4);
        xyz.z = xyz.z*cos(PI/4) + xyz.y * sin(PI/4);
        //translate back
        xyz.y += center.y;
        xyz.z += center.z;
        
        
        //Smooth the data before sending to reduce noise - this is important as the dancer can not be completely stationary
        
        //add the xyz positions of the current color to a deque
        currentPos.push_back(ofVec3f(xyz));
        
        //calculate average of the current and the previous xyz using a low pass filter
        if (currentPos.size() > 1){
            float f = 0.5; //adapt this to adjust the proportions between current and prev
            avg = f * currentPos[1] + (1-f) * currentPos[0]; //low pass filter for additional smoothing add more points to average ensuring that the coefficient always equal to 1
        }
        
        //Check what data is being sent in comparison to the raw data
        if(ofGetFrameNum() % 60 == 0){
            ofLog() << "curx " << currentPos[1];
            ofLog() << "avg " << avg;
            ofLog() << "prevx " << currentPos[0];
            ofLog() << " ";
        }
        
        //Remove the foremost ofVec3f to make space for another. Only need to keep two in at a time
        if(currentPos.size() > 2){
            currentPos.pop_front();
        }
    }
    
    //A new ofVec3f that mutates the data sent across to the arms a little.
    ofVec3f dataWithRandom = ofVec3f((avg.x + ofRandom(0, 50)),(avg.y + ofRandom(0,50)), avg.z);
    
//sending data via serial----------------------------------------------------------------------
       
        //Begin sending data to arduino at 1min into music, stop at 2min
        if (soundScore.getPosition() > 0.18 && soundScore.getPosition() < 0.28){
            message.sceneOne(avg);
        }
            //Send the data to the arduino
           else if (soundScore.getPosition() > 0.28 && soundScore.getPosition() < 0.36){
                message.sceneThree(avg);
            }
                //Store the data that is collected from movement during this time
               else if(soundScore.getPosition() > 0.36 && soundScore.getPosition() < 0.50){
                    storedData.push_back(avg);
                }
                    //Send the stored data to the arduino
                    else if (soundScore.getPosition() > 0.50 && soundScore.getPosition() < 0.69){
                        count++;
                        message.sceneTwo(storedData[count % storedData.size()]);
                    }
                        //Send the stored data that has randomness interjected
                        else if(soundScore.getPosition() > 0.69 && soundScore.getPosition() < 0.81){
                            message.sceneFour(dataWithRandom);
                        }
                            //Begin sending data to arduino at 4:01 and run until tae end
                            else if (soundScore.getPosition() > 0.92 && soundScore.getPosition() < 0.94){
                                message.sceneOne(avg);
                            }

    //draws the gui
    gui.run();

    //Function that displays useful information for debuging/rehearsing.
    debug();
}
//---------------------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    //Allows the colour being tracked to be changed
    gui.targetColor = kinect.getPixels().getColor(x, y);
    
}
//---------------------------------------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        //Adjust the angle of the kinect
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
        //Start sound score when letter 'p' is pressed
        case 'p':
            soundScore.play();
            break;
            
    }
}
//----------------------------------------------------------------------------------------------
void ofApp::kinectExit() {
    
    kinect.close();
    
}
//----------------------------------------------------------------------------------------------
void ofApp::debug(){
    //Function to display useful information for debugging
    ofPushStyle();
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()/2, ofGetHeight()/2);
    ofDrawBitmapString(ofToString(soundScore.getPosition()), ofGetWidth()/2, ofGetHeight()/2 + 20);
    ofPopStyle();
}
//----------------------------------------------------------------------------------------------
void ofApp::calibrate(ofVec3f xyz){
    
//    ofVec3f center = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 255/2);
//    
//    //translate to centre Point
//    xyz.y -= center.y;
//    xyz.z -= center.z;
//    //rotate 45 degree - edit here to calibrate
//    xyz.y = xyz.y*cos(PI/4) - xyz.z * sin(PI/4);
//    xyz.z = xyz.z*cos(PI/4) + xyz.y * sin(PI/4);
//    //translate back
//    xyz.y += center.y;
//    xyz.z += center.z;
//    
//    //Normalise xyz to 0-1;
//    xyz /= ofVec3f(ofGetWidth(), ofGetHeight(), 255);
//    
//    return calibratedXYZ;
    
    
}


