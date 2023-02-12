#include <AccelStepper.h>
#define FULLSTEP 4
#define HALFSTEP 8

const int operationMode = FULLSTEP;

long stepsPerRev = 2038;  //steps per stepper motor revolution
const float rpm = 10;
const float rps = (stepsPerRev * rpm) / 60;

#define motorPin1 8   // IN1 on the ULN2003 driver 1
#define motorPin2 9   // IN2 on the ULN2003 driver 1
#define motorPin3 10  // IN3 on the ULN2003 driver 1
#define motorPin4 11  // IN4 on the ULN2003 driver 1

AccelStepper myStepper(operationMode, motorPin1, motorPin3, motorPin2, motorPin4);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
long totalSteps = 0;

void runMotor() {
  if (myStepper.runSpeed() && totalSteps <= stepsPerRev) {  // This will run the motor forever.
    totalSteps++;
    Serial.println(totalSteps);
    // Serial.println("Stepping");
  }
}
void checkSerial() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
  }
}
void setup() {
  Serial.begin(9600);
  if (operationMode == HALFSTEP)
    stepsPerRev = stepsPerRev + stepsPerRev;
  Serial.print("Total Steps: ");
  Serial.println(stepsPerRev);

  myStepper.setMaxSpeed(stepsPerRev);  // this limits the value of setSpeed(). Raise it if you like.
  myStepper.setSpeed(rps);             // runSpeed() will run the motor at this speed - steps per second
}


void loop() {

  runMotor();
}
