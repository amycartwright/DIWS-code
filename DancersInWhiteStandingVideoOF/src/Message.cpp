//////////////////////////  Dancers In White, Staning  ///////////////////////////
/////////////////////          Amy Cartwright     ///////////////////////


//  Class that sends serial messages to the arduino IDE

#include "Message.h"
Message::Message(){
}
//--------------------------------------------------------------
void Message::setup(){
    //setup for the serial connection to the arduino. Device num and serial port num
    serial.setup(0, 9600);
}

//--------------------------------------------------------------
void Message::send(){
    //reduce the framerate when sending message to ensure the arduino is not overwhelmed
    if(ofGetFrameNum() % 40 == 0){
        serial.writeByte(char('a'));
    }
}
//--------------------------------------------------------------
void Message::dontSend(){
    
    if(ofGetFrameNum() % 40 == 0){
        serial.writeByte(char('b'));
    }
}
