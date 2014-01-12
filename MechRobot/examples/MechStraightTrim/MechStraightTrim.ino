// New using the MechRobot framewoork

#include <Servo.h>
#include <AFMotor.h>
#include <NewPing.h>

// Now include the simplifying wrapper class

#include <MechRobot.h>

MechRobot myRobot;

void setup() {
  myRobot.init();
  myRobot.setSpeed(100,100);
}

// This little program allows you to trim the rotation parameters for your robot
void loop() {
  int i;
  
  for( i=0; i < 8; i++ )
  {
    myRobot.turnLeft();
  
    delay(2000);
  }
  
  
  for( i=0; i < 8; i++ )
  {
    myRobot.turnRight();
  
    delay(2000);
  }  
  


}
