// This is a simple "robot" class to make controlling your Mechatrons robot a little easier
// for the novice programmer

//
// It is really just a utility class which wraps some functions of AFMotor, NewPing and Servo into a higher level interface
// It has utility functions for the Ultimate robot kit (sensor types as per kit, connections as per build manual)

// CoderDojo Bray
// This code is in the public domain

#ifndef _MechRobot_h_
#define _MechRobot_h_

#include <inttypes.h>
#include "../AFMotor/AFMotor.h"
#include "../NewPing/NewPing.h"
#include "../Servo/Servo.h"

#define MECHATRONS_LEFT_WHEEL   2      // Motor shield M2 is the left wheel
#define MECHATRONS_RIGHT_WHEEL  3      // Motor shield M3 is the right wheel

#define MECHATRONS_SCAN_SERVO   10      // Scan servo is connected to Servo1, which is Arduino Pin 10
                                        // In several online forums is says Servo1 is pin 9. This is incorrect.
                                     
class MechRobot
{

    private:
        AF_DCMotor leftWheel;
        AF_DCMotor rightWheel;
        NewPing sonar;
        Servo scanServo;

    
        int leftSpeed;
        int rightSpeed;
        int servoPos;
        
        void setServoPos(int pos);
        
        int sonarMaxDistance;       // in CMs
        
        int sonarPin;
        int bumperSwitch;

        int irRangePin;

        int leftLineFollow;
        int rightLineFollow;

        int leftLightPin;
        int rightLightPin;   
        
        // Don't drive the servo all the way to the ends .. can damage it
        int minServoPos;
        int maxServoPos;
        
        // Time at full speed to rotate on the spot, one wheel in each direction
        int mSecFullRotation;
        
        
    public:
        MechRobot(void);
        
        void init(void);                     // Initialise the class, setup all defaut options
        
        // Various motor control functions
        void setSpeed(int left, int right);  // Right and left wheel speed
        void setLeftSpeed(int speed);        // .. or set each independently
        void setRightSpeed(int speed);
        
        int getRightSpeed(void);
        int getLeftSpeed(void);
    
        void forward();
        void backward();
        
        void turnLeft();
        void turnRight();

        void turnLeft(int degrees);
        void turnRight(int degrees);
        
        void veerLeft();
        void veerRight();
        
        void backup();
        void backup(int speed);
        
        void halt();
        
        int  getRotateTime(void);
        void trimRotationAngle(float trim);
        
        // Various servo functions: some overlap as you can do the same thing in different ways
        // Which is generally a bad idea but this is just a fun little class
        void lookAhead();
        
        void lookLeft();
        void lookLeft(int degrees);
        
        void lookRight();
        void lookRight(int degrees);
        
        void setLookDirection(int direction);
        int  getLookDirection(void);
        
        // Sensor functions
        int sonarDistance(void);
        int irDistance(void);
        
        bool bump(void);
        
        bool isLeftLine(void);
        bool isRightLine(void);
        
        int leftLightLevel(void);
        int rightLightLevel(void);
        
        
};


#endif