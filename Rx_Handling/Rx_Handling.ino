/*
Rx_Handling 

RC In:
2, 3, 4, 5

Controls Out:
Drive 4
Right 6 //these do not match pins, but thats because I think the ranges are backwards... (fix them next time...) double check this..
Left 5
FWD 7
REV 8
ClawOpen 9
ClawClose 10
*/

// Assign Rx Input Pins
#define r1 0 //Left Horizontal
#define r2 1 //Right Vertical
#define r3 2 //Left Vertical
#define r4 3 //Right Horizontal

// Assign Controls Output Pins
#define drive 4
#define right 5
#define left 6
#define fwd 7
#define rev 8
#define clawOpen 9
#define clawClose 10

// Store Rx Values
int r1val = 0;
int r2val = 0;
int r3val = 0;
int r4val = 0;

// Store Rx Calibration Values
int r1cal, r2cal, r3cal, r4cal;

// Rx Stick Zero Range
int r1range = 150;
int r2range = 150;
int r3range = 300;
int r4range = 150;


void setup() {
  // Assign Rx Input Pins as Inputs
  pinMode(r1, INPUT);
  pinMode(r2, INPUT);
  pinMode(r3, INPUT);
  pinMode(r4, INPUT);
  
  // Assign Control Output Pins as Outputs
  pinMode(drive, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(fwd, OUTPUT);
  pinMode(rev, OUTPUT);
  pinMode(clawOpen, OUTPUT);
  pinMode(clawClose, OUTPUT);
}

void loop() {
  // Wait for Tx/Rx Communication to Begin/Restart
  if(r1val < 15000)
  {
    while(pulseIn(r1, INPUT) < 15000)
    {
      delay(10);
    }
    delay(10);
    
    // Calibrate Rx Signal
    r1cal = pulseIn(r1, INPUT);
    r2cal = pulseIn(r2, INPUT);
    r3cal = pulseIn(r3, INPUT);
    r4cal = pulseIn(r4, INPUT);
  }
  
  // Receive and Store Rx Values
  r1val = pulseIn(r1, INPUT);
  r2val = pulseIn(r2, INPUT);
  r3val = pulseIn(r3, INPUT);
  r4val = pulseIn(r4, INPUT);
  
  if(r3val < (r3cal - r3range)) // Engange drive
  {
    digitalWrite(drive, HIGH);
  }
  
  else // Disengange drive
  {
    digitalWrite(drive, LOW);
  }
  
  if(r2val > (r2cal + r2range)) // Fwd
  {
    digitalWrite(rev, LOW);
    digitalWrite(fwd, HIGH);
  }
  
  else if(r2val < (r2cal - r2range)) // Rev
  {
    digitalWrite(fwd, LOW);
    digitalWrite(rev, HIGH);
  }
  
  else
  {
    digitalWrite(fwd, LOW);
    digitalWrite(rev, LOW);
  }
  
  if(r4val > (r4cal + r4range)) // Right
  {
    digitalWrite(left, LOW);
    digitalWrite(right, HIGH);
  }
  
  else if(r4val < (r4cal - r4range)) // Left
  {
    digitalWrite(right, LOW);
    digitalWrite(left, HIGH);
  }
  
  else
  {
    digitalWrite(left, LOW);
    digitalWrite(right, LOW);
  }
  
  if(r1val > (r1cal + r1range)) // Close
  {
    digitalWrite(clawOpen, LOW);
    digitalWrite(clawClose, HIGH);
  }
  
  else if(r1val < (r1cal - r1range)) // Open
  {
    digitalWrite(clawClose, LOW);
    digitalWrite(clawOpen, HIGH);
  }
  
  else
  {
    digitalWrite(clawClose, LOW);
    digitalWrite(clawOpen, LOW);
  }
}
