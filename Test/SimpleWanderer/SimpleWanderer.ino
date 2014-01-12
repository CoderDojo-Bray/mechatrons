// This is a simple program to run the robot up to an obstacle and stop
//
// CoderDojo Bray
//
// This code is in the public domain.
//

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define MECHATRONS_LEFT_WHEEL   2      // Motor shield M2 is the left wheel
#define MECHATRONS_RIGHT_WHEEL  3      // Motor shield M3 is the right wheel

#define MECHATRONS_SCAN_SERVO   10      // Scan servo is connected to Servo1, which is Arduino Pin 10
                                        // In several online forums is says Servo1 is pin 9. This is incorrect.

AF_DCMotor leftWheel(MECHATRONS_LEFT_WHEEL);
AF_DCMotor rightWheel(MECHATRONS_RIGHT_WHEEL);
Servo scanServo;
const int sonarPin = A0;
NewPing sonar = NewPing( sonarPin, sonarPin, 300);

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("Motor test!");

  // Initialise the two motor controllers, full speed setting
  leftWheel.setSpeed(150);
  rightWheel.setSpeed(150);
 
  leftWheel.run(RELEASE);
  rightWheel.run(RELEASE);
  
  // Initialise the Servo controller and center the servo
  scanServo.attach(MECHATRONS_SCAN_SERVO);
  scanServo.write(90);  
  
}

void forward() {
  rightWheel.run(FORWARD);
  leftWheel.run(FORWARD);
}

void backup() {
  rightWheel.run(BACKWARD);
  leftWheel.run(BACKWARD);
  delay(500);
  halt();
}

void halt() {
  rightWheel.run(RELEASE);
  leftWheel.run(RELEASE);
}

// The "turn" functions are guesses: they would be more accurate if we added optical sensors to read
// axle turns
void turnLeft() {
  rightWheel.run(BACKWARD);
  leftWheel.run(FORWARD);
  delay(400);
  halt();
}


void turnRight() {
  rightWheel.run(FORWARD);
  leftWheel.run(BACKWARD);
  delay(400);
  halt();
}

void lookLeft() {
  scanServo.write(160);
  delay(300);
}

void lookRight() {
  scanServo.write(20);
  delay(300);
}

void lookAhead() {
    scanServo.write(90);
    delay(300);
}

int sonarRange() {
  int distance;
  
  distance = sonar.ping_cm();
  if( distance == 0 ) distance = 300;

  return distance;  
}

// Just run about more or less on the spot ...
void loop() {
  int distance;
  int leftDist, rightDist;
  
  distance = sonarRange();
  
  if (distance < 20 )
  {
    halt();
    backup();
    
    lookLeft();
    leftDist = sonarRange();
    
    lookRight();
    rightDist = sonarRange();
    lookAhead();
    
    if( rightDist > leftDist )
    {
      turnRight();
    }
    else {
      turnLeft();
    }
  }
  
  forward();  
}
