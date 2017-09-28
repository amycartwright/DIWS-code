///////////////////////////////////////////////////////  Dancers In White, Standing - Video  ////////////////////////////////////////////
//////////////////////////////////////////////////////                 Amy Cartwright             ///////////////////////////////////////////

/*Code to accompany the main program in OpenFrameworks. This code is the other half of a serial connection that powers the servo motors used to control three robotic arms through an arduino.
  This is the code used durning exhibition when there is no performance. It demonstrates an example of the arms moving and is triggered via face tracking in openFrameworks*/

#include <Servo.h>
//Identify each servo as an instance of the servo object
//1st Arm
Servo armBase;
Servo armShoulder;
Servo armElbow;
//2nd Arm
Servo arm1Base;
Servo arm1Shoulder;
Servo arm1Elbow;
//3rd Arm
Servo arm2Base;
Servo arm2Shoulder;
Servo arm2Elbow;

void setup() {
  //attach each servo to a pin on the arduino
  armBase.attach(13);
  armShoulder.attach(12);
  armElbow.attach(11);

  arm1Base.attach(9);
  arm1Shoulder.attach(8);
  arm1Elbow.attach(7);

  arm2Base.attach(5);
  arm2Shoulder.attach(4);
  arm2Elbow.attach(3);

  Serial.begin(9600); // start the communication between the oF app and the Arduino
}

void loop() {

  char message;

  //If serial data is available save the sent data to the variable message
  if (Serial.available() > 0) {
    message = Serial.read();
  }

  //If the serial message is 'a' move the arms through three set positions
  if (message == 'a') {
    //Position one
    armBase.write(90);
    armShoulder.write(90);
    armElbow.write(180);

    arm1Base.write(50);
    arm1Shoulder.write(90);
    arm1Elbow.write(100);

    arm2Base.write(150);
    arm2Shoulder.write(90);
    arm2Elbow.write(120);

    delay(1000); 
    //Position two
    armBase.write(50);
    armShoulder.write(90);
    armElbow.write(100);

    arm1Base.write(150);
    arm1Shoulder.write(90);
    arm1Elbow.write(120);

    arm2Base.write(90);
    arm2Shoulder.write(90);
    arm2Elbow.write(180);

    delay(1000); 
    //Position Three
    armBase.write(150);
    armShoulder.write(90);
    armElbow.write(120);

    arm1Base.write(90);
    arm1Shoulder.write(90);
    arm1Elbow.write(180);

    arm2Base.write(50);
    arm2Shoulder.write(90);
    arm2Elbow.write(100);

    delay(1000); 

  }

  //If the serial message is 'b' the arms should be stationary
  if (message == 'b') {
    armBase.write(90);
    armShoulder.write(90);
    armElbow.write(100);

    arm1Base.write(40);
    arm1Shoulder.write(90);
    arm1Elbow.write(100);

    arm2Base.write(10);
    arm2Shoulder.write(90);
    arm2Elbow.write(120);

    delay(1000);
  }
}








