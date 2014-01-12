// Test the sensors on your newly built Mechatrons Ultimate Robot
// This is just a sensor test: the robot won't move!
// So it's safe to do on a desk

// Run this code with the robot connected over USB
// If you like, you can remove the jumper between 5v and PWR on the shield (don't lose it though!) which stops power going to the wheels

//
// CoderDojo Bray
//
// This code is in the public domain.
//
//  Modified by Peter Redmond 27/10/13 
//  I added a conversion for the IR sensor to CM and corrected the pullup settings for the bumper switches.
//  Note the bumper switch should be connected to the minus pin rather than the plus pin as shown in the V1.0 instructions.

#include <NewPing.h>

// If you have followed the instructions, then the sensor pins are as used below

const int bumperSwitch = 9;

const int sonarPin = A0;
const int irRangePin = A1;

const int leftLineFollow = A2;
const int rightLineFollow = A3;

const int leftLightPin = A4;
const int rightLightPin = A5;

const int maxDistance = 300;  // In cm

NewPing sonar = NewPing( sonarPin, sonarPin, maxDistance);

  int sonarDistance;
  int irProximity;
  
  int leftLightLevel;
  int rightLightLevel;

  int leftLine;
  int rightLine;
  
  int bump;

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 bps
  Serial.println("Sensor test!");

  // Set this up as a digital input
  // Notice that we need to specify use the internal pullup resistor.
  pinMode(bumperSwitch, INPUT_PULLUP);

  // Setup the line following sensors as digital inputs
  // They only return digital values anyway (0/1): if you read them as analog sensors you will
  // just get ~0 and ~1023 back as readings.
  pinMode(leftLineFollow, INPUT);
  pinMode(rightLineFollow, INPUT);
  digitalWrite(leftLineFollow, HIGH);
  digitalWrite(rightLineFollow, HIGH);

}

// Test out all the sensors
// Print out some data about the readings taken
// Then experiment with the sensors to see how they react to distance, light, and so on

void loop() {

  
  // This is the sonar distance sensor
  // The sonar distance sensor does what you think it should
  // It sends out an ultrasonic pulse which bounces off an obstacle and allows you to calclualte the distance to that object
  // since we know the speed of sound.
  // This function will return the distance, in centimeters, to the object the sensor is facing
  sonarDistance = sonar.ping_cm();
  if( sonarDistance == 0 ) sonarDistance = maxDistance;

  // The IR sensor is an alternative to the sonar but does the same job (albeit in a slightly different way.  
  // Sonar does not work well with fabrics (or other surface that absorb sound) while IR does not work well with dark surfaces (or glass).  
  // If you have a dark fabric surface then you have to rely on the bumpers.
  
  irProximity = 28 * pow(analogRead(irRangePin)*0.0048828125,-1.1);     // converted to cm but accuracy depends on colour material detected
 
  // The left and right light level sensor readings return a number between 0 and 1023 which indicates the level of light
  // falling on the sensor: the *lower* the number, the *more* light is falling on the sensor
  leftLightLevel = analogRead(leftLightPin);
  rightLightLevel = analogRead(rightLightPin);
  
  // The bumper switch : we read 1 if the switch is closed (we have bumped into something) and 0 if not  
  bump = digitalRead(bumperSwitch);
  
  if( !bump )
  {
    // Add your code here for bumps
  }
  
  // Check what we are getting from the line followers
  // The line following sensors will return 0 if there is no dark colour directly underneath the sensor, and 1 if
  // there *is* a dark colour directly under the sensor (or if there is nothing at all under the sensor: hold the robot up
  // in the air and it will also return 1)
  leftLine = digitalRead(leftLineFollow);
  rightLine = digitalRead(rightLineFollow);
  
  // Now print out a message detailing our sensor inputs
  // You should look at the output and use this to see that all your sensors are working
  
  Serial.println("**************************************");
  Serial.print("Sonar Distance (cm): ");
  Serial.println(sonarDistance);
  Serial.print("IR Proximity (cm): ");
  Serial.println(irProximity);
  Serial.print("Left Light Level: ");
  Serial.println(leftLightLevel);  
  Serial.print("Right Light Level: ");
  Serial.println(rightLightLevel);
  Serial.print("Bump: ");
  Serial.println(bump);
  Serial.print("Left Line: ");
  Serial.println(leftLine);
  Serial.print("Right Line: ");
  Serial.println(rightLine);
  
  if( !bump )
  { 
    Serial.println("** Bump!! ** ");
  }
  
  delay(200);
}
