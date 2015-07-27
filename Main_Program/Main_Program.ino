/*
Rx_Handling 

Controls In:
Drive 4
Right 13
Left 12
FWD 7
REV 8
ClawOpen 14
ClawClose 15

Servos Out:
RightShoulder 9
LeftShoulder 10
RightElbow 5
LeftElbow 6
ClawOpen 11

Drive Out:
LeftA 0
LeftB 1
RightA 2
RightB 3
*/

#include <Servo.h>

// Assign Controls Input Pins
#define drivePin 4
#define rightPin 13
#define leftPin 12
#define fwdPin 7
#define revPin 8
#define clawOpen 14
#define clawClose 15

// Assign motor drive pins
#define leftA 0
#define leftB 1
#define rightA 2
#define rightB 3

boolean drive, right, left, fwd, rev, clawO, clawC;

// Declare servos
Servo leftShoulder;
Servo rightShoulder;
Servo leftElbow;
Servo rightElbow;
Servo claw;

// Define Arm Lengths
//const L1 = 1; // 1 ft (Lower arm)
//const L2 = 1; // 1 ft (Upper arm)

int shoulderMax = 2200; // Max PWM
int shoulderMin = 800; // Min PWM
int shoulderPos = shoulderMin; // Start with arm down
int shoulderStep = 1; // Shoulder position increment

int elbowMax = 2150;
int elbowMin = 800;
int elbowPos = elbowMin;
int elbowStep = 1;

int clawMax = 2000;
int clawMin = 1000;
int clawPos = clawMin;
int clawStep = 1;

void setup()
{  
  // Assign Control Input Pins as Inputs
  pinMode(drivePin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(fwdPin, INPUT);
  pinMode(revPin, INPUT);
  pinMode(clawOpen, INPUT);
  pinMode(clawClose, INPUT);
  
  // Assign Motor Pins
  pinMode(leftA, OUTPUT);
  pinMode(leftB, OUTPUT);
  pinMode(rightA, OUTPUT);
  pinMode(rightB, OUTPUT);
  
  //Assign servo pins
  rightShoulder.attach(9);
  leftShoulder.attach(10);
  rightElbow.attach(5);
  leftElbow.attach(6);
  claw.attach(11);
  
  // Lower arm
  rightShoulder.writeMicroseconds(shoulderMin);
  leftShoulder.writeMicroseconds(3050 - shoulderMin);
  rightElbow.writeMicroseconds(elbowMin);
  leftElbow.writeMicroseconds(3050 - elbowMin);
}

void motorControl(int a, int b, int c, int d) // Motor h-bridge control
{
   digitalWrite(leftA, a);
   digitalWrite(leftB, b);
   digitalWrite(rightA, c);
   digitalWrite(rightB, d);
   return;
}

void shoulderMove(int dir)
{
  if(dir == 1) // Move shoulder up
  {
    shoulderPos = shoulderPos + shoulderStep; // Determine new position
    
    if(shoulderPos > shoulderMax) // Prevent over extension
    {
      shoulderPos = shoulderMax;
    }

    // Move servos
    rightShoulder.writeMicroseconds(shoulderPos);
    leftShoulder.writeMicroseconds(2950 - shoulderPos);
  }
  
  else
  {
    shoulderPos = shoulderPos - shoulderStep; // Determine new position
    
    if(shoulderPos < shoulderMin) // Prevent over extension
    {
      shoulderPos = shoulderMin;
    }
      
    // Move servos
    rightShoulder.writeMicroseconds(shoulderPos);
    leftShoulder.writeMicroseconds(2950 - shoulderPos);
  }
  
  delay(5);
  return;
}

void elbowMove(int dir)
{
  if(dir == 1) // Move shoulder up
  {
    elbowPos = elbowPos + elbowStep; // Determine new position
    
    if(elbowPos > elbowMax) // Prevent over extension
    {
      elbowPos = elbowMax;
    }

    // Move servos
    rightElbow.writeMicroseconds(elbowPos);
    leftElbow.writeMicroseconds(2950 - elbowPos);
  }
  
  else
  {
    elbowPos = elbowPos - elbowStep; // Determine new position
    
    if(elbowPos < elbowMin) // Prevent over extension
    {
      elbowPos = elbowMin;
    }
      
    // Move servos
    rightElbow.writeMicroseconds(elbowPos);
    leftElbow.writeMicroseconds(2950 - elbowPos);
  }
  
  delay(5);
  return;
}

void clawMove(int dir)
{
  if(dir == 1) // Close claw
  {
    clawPos = clawPos - clawStep; // Determine new position
    
    if(clawPos < clawMin) // Prevent over extension
    {
      clawPos = clawMin;
    }

    // Move servos
    claw.writeMicroseconds(clawPos);
  }
  
  else
  {
    clawPos = clawPos + clawStep; // Determine new position
    
    if(clawPos > clawMax) // Prevent over extension
    {
      clawPos = clawMax;
    }
      
    // Move servos
    claw.writeMicroseconds(clawPos);
  }
  
  delay(5);
  return;
}

/*
void xMove()

void yMove(int dir)
{
  if (dir == 1)
  {
    
    
    if (shoulderPos >= shoulderMax || shoulderPos <= shoulderMin || elbowPos >= elbowMax || elbowPos <= elbowMin)
    {
      return;
    }
    
    
}
*/
void loop()
{  
  drive = digitalRead(drivePin);
  right = digitalRead(rightPin);
  left = digitalRead(leftPin);
  fwd = digitalRead(fwdPin);
  rev = digitalRead(revPin);
  clawO = digitalRead(clawOpen);
  clawC = digitalRead(clawClose);
  
  if(fwd == true && drive == true) //Drive FWD
  {
    if(right == true) // Half left
    {
      motorControl(0, 1, 0, 0);
    }
    else if(left == true) // Half right
    {
      motorControl(0, 0, 0, 1);
    }
    else
    {    
      motorControl(0, 1, 0, 1);
    }
  }
    
  else if(rev == true && drive == true) //Drive REV
  {
    if(right == true) // Half left
    {
      motorControl(1, 0, 0, 0);
    }
    else if(left == true) // Half right
    {
      motorControl(0, 0, 1, 0);
    }
    else
    {    
      motorControl(1, 0, 1, 0);
    }
  }  
  
  else if(right == true && drive == true) // Full right
  {
    motorControl(0, 1, 1, 0);
  }

  else if(left == true && drive == true) // Full left
  {
    motorControl(1, 0, 0, 1);
  }
  
  else
  {
    motorControl(0, 0, 0, 0);
  }

  if(fwd == true && drive == false) // Move shoulder up
  {
    shoulderMove(1);
  }
  
  else if(rev == true && drive == false) // Move shoulder down
  {
    shoulderMove(0);
  }
  
  if(right == true && drive == false) // Move elbow up
  {
    elbowMove(1);
  }
  
  else if(left == true && drive == false) // Move elbow down
  {
    elbowMove(0);
  }
  
  if(clawO == true) // Open Claw
  {
    clawMove(0);
  }
  
  if(clawC == true) // Close Claw
  {
    clawMove(1);
  } 
}
