//////////////////////////      Dancers In White, Standing  ///////////////////////////
//////////////////////              Amy Cartwright             ///////////////////////

////Best compiled in release mode due to the use of the ofxDLib addon which does not run effectively in debug

/*
 An interactive program that plays a video and detects when someone is watching.
 
Ceated as a companion to the DancersInWhiteStandingPerformance program. To be used in an exhibition setting this program allows the audience to see the robot arms moving outside of the performance seting
 */

//Elements of the program areinspired by http://www.creativeapplications.net/tutorials/arduino-servo-opencv-tutorial-openframeworks/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //tells the facetracer which file to use to make comparisons
    ft.setup("shape_predictor_68_face_landmarks.dat");
    
    //setup for the webcam
    video.setDeviceID(1);
    video.initGrabber(640, 480);
    video.setDesiredFrameRate(30);
    
    //setup for the video
    film.load("Amy.mp4");
    film.setLoopState(OF_LOOP_NORMAL);
    film.play();
    film.setVolume(10);
    
    //run the setup for the message class - connect to serial port
    message.setup();
    
    sec = 30;
}
//--------------------------------------------------------------
void ofApp::update(){
    
    video.update();
    film.update();
    
    
    if(video.isFrameNew()){ //only run the code within this conditional if the video frame is new.
        //find faces each frame within the webcam pixels
        ft.findFaces(video.getPixels());
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    film.draw(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    //draw facetracker - will turn tracked bool to true (see additions in addon file)
    ft.draw();
    
    //if a face has been detected, begin incrementing tDetect
    if(ft.tracked == true){
        tDetect ++;
        
        if(tDetect < sec*5){
        message.dontSend();
        }

        if (tDetect > sec*5){
            message.send();
        }
    }

   //if a face has not been tracked return tDetect to 0 - allows the program to start again for another user
    
       else if(ft.tracked == false){
        tDetect = 0;
    }
    
    //Uncomment line below to see data for debugging the detection counter
    cout<<tDetect<<endl;
    
    //Uncomment line below to see data for debugging the face tracker, 0 = no face, 1 = face
    cout<<ft.tracked<<endl;
}
