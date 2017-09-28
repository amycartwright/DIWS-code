////////////////////////// Dancers In White, Standing ///////////////////////////
/////////////////////          Amy Cartwright     ///////////////////////

// Class that sends serial messages to the arduino IDE which in turn powers the arduino and activates the lights

#ifndef Message_h
#define Message_h

#include <stdio.h>
#include "ofMain.h"

#endif /* Message_h */

class Message{
    
public:
    
    Message();
    
    ofSerial serial; //set up a serial object
    
    void setup();
    void send();
    void dontSend();
};
