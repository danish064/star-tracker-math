#include <AccelStepper.h>

#define motorPin1 8   // IN1 on the ULN2003 driver 1
#define motorPin2 10   // IN2 on the ULN2003 driver 1
#define motorPin3 9  // IN3 on the ULN2003 driver 1
#define motorPin4 11  // IN4 on the ULN2003 driver 1

#define FULLSTEP 4
#define HALFSTEP 8

const int operationMode = FULLSTEP;
long stepsPerRev = 2048 ;  //steps per stepper motor revolution
const float rpm =3;

float rps = (stepsPerRev * rpm) / 60;

AccelStepper myStepper(operationMode, motorPin1, motorPin2, motorPin3, motorPin4);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
long totalSteps = 0;

void runMotor() {
  // Serial.println(myStepper.currentPosition());
  if (myStepper.currentPosition() % stepsPerRev == 0) {
    Serial.println("Completed " + String(myStepper.currentPosition() / stepsPerRev) + " revolutions");
  }
}
void checkSerial() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();

    Serial.print("I received: ");
    Serial.println(incomingByte);
  }
}
void setup() {
  Serial.begin(9600);
  if (operationMode == HALFSTEP) {
    stepsPerRev = stepsPerRev + stepsPerRev;
    rps = rps + rps;
  }
  Serial.print("Total Steps: ");
  Serial.println(stepsPerRev);
  Serial.println(rps);
  myStepper.setMaxSpeed(stepsPerRev);  // this limits the value of setSpeed(). Raise it if you like.
  myStepper.setSpeed(rps);             // runSpeed() will run the motor at this speed - steps per second
  // myStepper.setAcceleration(100);
}


void loop() {
  myStepper.runSpeed();
  runMotor();
  // myStepper.runSpeed();
  // Serial.println(myStepper.currentPosition());
  // if (myStepper.run()) {
  //   Serial.println("Still moving");
  // } else {
  //   Serial.println("1 rev complete");
  // }
}
