#include "Motor.h"

Motor motor;

void setup() {
  motor.Setup(5,6,7,8, HIGH);
}

void loop() {
  motor.Accelerate();
  motor.Print();
  delay(500);
}
