// New using the MechRobot framewoork
// Wander about a bit, trying to avoid bumping into stuff

#include <Servo.h>
#include <AFMotor.h>
#include <NewPing.h>

#include <MechRobot.h>

MechRobot myRobot;

void setup() {
  myRobot.init();
  myRobot.setSpeed(255,255);
}

void loop() {
  
  int distance;
  int leftDist, rightDist;
  int i;
  

    distance = myRobot.sonarDistance();
  
    if (distance < 15 || myRobot.bump() )
    {
      myRobot.halt();
      myRobot.backup();
    
      myRobot.lookLeft();
      leftDist = myRobot.sonarDistance();
    
      myRobot.lookRight();
      rightDist = myRobot.sonarDistance();
      myRobot.lookAhead();
    
      if( rightDist > leftDist )
      {
        myRobot.turnRight();
      }
      else {
        myRobot.turnLeft();
      }
    }
  
    myRobot.forward();
 
}
