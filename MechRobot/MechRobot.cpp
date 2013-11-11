// This is a simple "robot" class to make controlling your Mechatrons robot a little easier
// for the novice programmer

//
// It is really just a utility class which wraps some functions of AFMotor, NewPing and Servo into a higher level interface
// It has utility functions for the Ultimate robot kit (sensor types as per kit, connections as per build manual)

// For the adventurous, it exposes all the lower level classes via member functions, so you can poke about with them directly
// However if you do that, you risk confusing the "Robot" class a little (it will not know what speed is set, for instance)
//

// It is also not done yet, as we are not finished refining it in real world experiments
// Feel free to contribute suggestions to this code, as we refine it further
// Please issue a pull request, if you do this on github, so that everyone can benefit
//
// Still ToDo:
// * Need to add support for other sensors (opto rotation sensors look fairly essential for accurate navigation)
// * Some more examples would be nice

// CoderDojo Bray
// This code is in the public domain

#include "MechRobot.h"

MechRobot::MechRobot(void) : leftWheel(MECHATRONS_LEFT_WHEEL), rightWheel(MECHATRONS_RIGHT_WHEEL), sonar(14, 14, 300), scanServo()
{
    leftSpeed = rightSpeed = 0;
    servoPos = 90;
    
    // Setup a bunch of the constants
    sonarMaxDistance = 300;
    
    bumperSwitch = 9;

    irRangePin = A1;

    leftLineFollow = A2;
    rightLineFollow = A3;

    leftLightPin = A4;
    rightLightPin = A5;           

}

// Called inside your "setup" routine generally
// Sets up the motors and pins required for the sensors
void MechRobot::init(void)
{
    
    // Set them both up, stopped
    leftWheel.setSpeed(leftSpeed);
    rightWheel.setSpeed(rightSpeed);
    leftWheel.run(RELEASE);
    rightWheel.run(RELEASE);
    
    // Centre the servo
    scanServo.attach(MECHATRONS_SCAN_SERVO);
    scanServo.write(servoPos);
    
    
    // Setup the bump switch, digital input
    // Notice that we need to specify use the internal pullup resistor.
    pinMode(bumperSwitch, INPUT_PULLUP);
    
    // Setup the line following sensors as digital inputs
    // They only return digital values anyway (0/1): if you read them as analog sensors you will
    // just get ~0 and ~1023 back as readings.
    pinMode(leftLineFollow, INPUT);
    pinMode(rightLineFollow, INPUT);
    digitalWrite(leftLineFollow, HIGH);
    digitalWrite(rightLineFollow, HIGH);
    
    // Now setup some defaults
    // We might allow these to be changed later
    
    // This we use to compute angle to turn
    // You can apply a "trim" factor to it
    mSecFullRotation = 1080;
    
    // Don't drive the servo all the way to the ends .. can damage it
    minServoPos = 5;
    maxServoPos = 175;
   
}

// Wheel motor control

// Set both in one function
void MechRobot::setSpeed(int left, int right)  
{   
    setLeftSpeed(left);
    setRightSpeed(right);
}

void MechRobot::setLeftSpeed(int speed)
{
    // Just ignore invalid requests
    if( (0 <= speed) && (speed <= 255))
    {
        leftSpeed = speed;
        leftWheel.setSpeed(leftSpeed);
    }
}

void MechRobot::setRightSpeed(int speed)
{
    // Just ignore invalid requests
    if( (0 <= speed) && (speed <= 255))
    {
        rightSpeed = speed;
        rightWheel.setSpeed(rightSpeed);
    }
}

int MechRobot::getRightSpeed(void)
{
    return rightSpeed;
}    

int MechRobot::getLeftSpeed(void)
{
    return leftSpeed;
}

void MechRobot::forward(void)
{
    leftWheel.run(FORWARD);
    rightWheel.run(FORWARD);
}

void MechRobot::backward(void)
{
    leftWheel.run(BACKWARD);
    rightWheel.run(BACKWARD);
}

void MechRobot::turnLeft(void)
{
    turnLeft(90);
}

void MechRobot::turnRight(void)
{
    turnRight(90);
}

void MechRobot::turnLeft(int degrees)
{
    int curLeftSpeed;
    int curRightSpeed;
    int waitTime;
    
    // Stop, remember current speed, set full speed, turn, halt, reset old speed
    halt();
    
    curLeftSpeed = getLeftSpeed();
    curRightSpeed = getRightSpeed();
    
    setSpeed(255,255);
    
    waitTime = (int)(((float)mSecFullRotation * (float)degrees)/360.0);
    
    leftWheel.run(BACKWARD);
    rightWheel.run(FORWARD);
      
    delay( waitTime );
    
    halt();
    
    setSpeed(curLeftSpeed, curRightSpeed);
       
}

void MechRobot::turnRight(int degrees)
{
    int curLeftSpeed;
    int curRightSpeed;
    int waitTime;
    
    // Stop, remember current speed, set full speed, turn, halt, reset old speed
    halt();
    
    curLeftSpeed = getLeftSpeed();
    curRightSpeed = getRightSpeed();
    
    setSpeed(255,255);

    waitTime = (int)(((float)mSecFullRotation * (float)degrees)/360.0);
    
    leftWheel.run(FORWARD);
    rightWheel.run(BACKWARD);
    
    delay(waitTime);
    halt();
    
    setSpeed(curLeftSpeed, curRightSpeed);
    
}
        
void MechRobot::backup()
{
    halt();
    leftWheel.run(BACKWARD);
    rightWheel.run(BACKWARD);
    delay(500);
    halt();
}
    
void MechRobot::backup(int speed)
{
    int curLeftSpeed, curRightSpeed;
    
    halt();
    
    curLeftSpeed = getLeftSpeed();
    curRightSpeed = getRightSpeed();
    
    if( (0 <= speed) and (speed <= 255))
    {
        setSpeed(speed, speed);
    }
    
    leftWheel.run(BACKWARD);
    rightWheel.run(BACKWARD);
    delay(500);
    halt();
    
    setSpeed(curLeftSpeed, curRightSpeed);
}
    
void MechRobot::halt()
{
    leftWheel.run(RELEASE);
    rightWheel.run(RELEASE);
}

int MechRobot::getRotateTime(void)
{
    return mSecFullRotation;
}

void MechRobot::trimRotationAngle(float trim)
{
    mSecFullRotation = (int)(mSecFullRotation * trim);
}
       
void MechRobot::lookAhead()
{
    setServoPos(90);
}
        
void MechRobot::lookLeft()
{
    setServoPos(minServoPos);
}

void MechRobot::lookLeft(int degrees)
{
    int desiredPos;
    // This is degrees from straight ahead
    // Otherwise ignore odd request
    if ( (0 <= degrees) && (degrees <= 90))
    {
        desiredPos = 90 - degrees;
        if (desiredPos < minServoPos) desiredPos = minServoPos;
        
        setServoPos(desiredPos);
    }
     
}

        
void MechRobot::lookRight()
{
    setServoPos(maxServoPos);
}

void MechRobot::lookRight(int degrees)
{
    int desiredPos;
    // This is degrees right from straight ahead
    // Otherwise ignore odd request
    if ( (0 <= degrees) && (degrees <= 90))
    {
        desiredPos = 90 + degrees;
        if (desiredPos > maxServoPos) desiredPos = maxServoPos;
        
        setServoPos(desiredPos);
    }
}
        
void MechRobot::setLookDirection(int direction)
{
    if( (minServoPos <= direction) && (direction <= maxServoPos))
    {
        setServoPos(direction);       
    }
}

int MechRobot::getLookDirection(void)
{
    return servoPos;
}
        
// Sensor functions
int MechRobot::sonarDistance(void)
{
    int sonarDistance;
    sonarDistance = sonar.ping_cm();
    if( sonarDistance == 0 ) sonarDistance = sonarMaxDistance;
    
    return sonarDistance;
}

int MechRobot::irDistance(void)
{
    return (28 * pow(analogRead(irRangePin)*0.0048828125,-1.1));     // converted to cm but accuracy depends on colour material detected
}
        
bool MechRobot::bump(void)
{
    return !digitalRead(bumperSwitch);
}
        
bool MechRobot::isLeftLine(void)
{
    return digitalRead(leftLineFollow);
}

bool MechRobot::isRightLine(void)
{
    return digitalRead(rightLineFollow);
}
        
int MechRobot::leftLightLevel(void)
{
    return analogRead(leftLightPin);
}
        
int MechRobot::rightLightLevel(void)
{
    return analogRead(rightLightPin);
}

// Private functions
void MechRobot::setServoPos(int pos)
{
    servoPos = pos;
    scanServo.write(servoPos);
    delay(300);
}
