// New using the MechRobot framewoork
// Minimal (and not too useful) program
// It will just drive at top speed, forwards, forever

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
    myRobot.forward();
}