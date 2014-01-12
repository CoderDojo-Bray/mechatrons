// Test the motors on your newly built Mechatrons Ultimate Robot
// First test the wheel motors
// Then test the servo used for the range scanners
//
// CoderDojo Bray
//
// This code is in the public domain.
//

// Note, of course, that if you actually run this code while your robot is sitting on the desk
// and attached to your computer via USB, the robot will drive around, attempt to jump off the desk, and
// commit roboticide

// Therefore for initial testing, make sure the robot's wheels are off the ground ...

#include <AFMotor.h>
#include <Servo.h>

#define MECHATRONS_LEFT_WHEEL   2      // Motor shield M2 is the left wheel
#define MECHATRONS_RIGHT_WHEEL  3      // Motor shield M3 is the right wheel

#define MECHATRONS_SCAN_SERVO   10      // Scan servo is connected to Servo1, which is Arduino Pin 10
                                        // In several online forums is says Servo1 is pin 9. This is incorrect.

AF_DCMotor leftWheel(MECHATRONS_LEFT_WHEEL);
AF_DCMotor rightWheel(MECHATRONS_RIGHT_WHEEL);
Servo scanServo;

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("Motor test!");

  // Initialise the two motor controllers
  leftWheel.setSpeed(10);
  rightWheel.setSpeed(10);
 
  leftWheel.run(RELEASE);
  rightWheel.run(RELEASE);
  
  // Initialise the Servo controller and center the servo
  scanServo.attach(MECHATRONS_SCAN_SERVO);
  scanServo.write(90);
}

// Run a little wheel test
// Run the wheel from stopped to full speed forwards, then do the same backwards
void wheelTest( AF_DCMotor thisWheel, char *wheelName) {

  uint8_t i;
  
  Serial.print(wheelName);
  Serial.print(" wheel: forward ");
  
  Serial.print(" ... getting faster ... ");
  thisWheel.run(FORWARD);
  for (i=0; i<255; i++) {
    thisWheel.setSpeed(i);  
    delay(10);
 }
 
 Serial.print("and slower ...");
  for (i=255; i!=0; i--) {
    thisWheel.setSpeed(i);  
    delay(10);
 }
 
  Serial.print(wheelName);
  Serial.print(" wheel: backwards ... ");

  Serial.print(" ... getting faster ... ");
  
  thisWheel.run(BACKWARD);
  for (i=0; i<255; i++) {
    thisWheel.setSpeed(i);  
    delay(10);
 }

  Serial.print("and slower ..."); 
  for (i=255; i!=0; i--) {
    thisWheel.setSpeed(i);  
    delay(10);
 }
  
 Serial.println("done");
 thisWheel.run(RELEASE);
 
}

// There is only one servo: no need for a parameter
// Good to check that the servo position is more or less correct
// Since you are going to be relying on this for navigation later
void servoTest() {  
  uint8_t angle;
  
  Serial.println("Servo test ... ");
  
  for( angle = 0; angle < 180; angle++ )
  {
      scanServo.write(angle);
      Serial.println(angle);
      delay(100);
  }
  Serial.println();
  
  for( angle = 180; angle > 1; angle-- )
  {
      scanServo.write(angle);
      Serial.println(angle);
      delay(100);
  }
  Serial.println();
  
}

// Just run about more or less on the spot ...
void loop() {

  // Drive around a bit
  wheelTest( leftWheel, "Left");
  delay(1000);
  wheelTest( rightWheel, "Right");
  delay(1000);
  
  // Now test the servo
  servoTest();
  
}
