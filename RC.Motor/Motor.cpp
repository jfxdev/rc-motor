#include "Motor.h"

Motor::Motor(){}

Shift shifts[] = { { 0, 0, HIGH }, { 15, 70, HIGH }, { 10, 150, HIGH } };

int sizeOfShifts(){
  return sizeof(shifts) / sizeof(shifts[0]);
}

String serialReceived;
char commandChar;

void Motor::Setup(byte motorAPin, byte motorBPin, byte directionAPin, byte directionBPin, bool automatic){
  _motorAPin = motorAPin;
  _motorBPin = motorBPin;
  _directionAPin = directionAPin;
  _directionBPin = directionBPin;

  pinMode(_motorAPin, OUTPUT);
  pinMode(_motorBPin, OUTPUT);
  pinMode(_directionAPin, OUTPUT);
  pinMode(_directionBPin, OUTPUT);
  Serial.begin(9600);

  _gear.automatic = automatic;

  _gear.level = 0;
  _gear.acceleration = shifts[_gear.level].acceleration;
  _gear.max_speed = shifts[_gear.level].max_speed;
}

void Motor::Print(){
  char buffer[40];
  sprintf(buffer, "Level : %d - Acceleration : %d - Speed : %d", _gear.level, _gear.acceleration, _gear.speed);
  Serial.println(buffer);
}

void Motor::Accelerate(){
  if (Serial.available() > 0) {
      serialReceived = Serial.readStringUntil('\n');
      commandChar = serialReceived.charAt(0);
      Serial.println(commandChar);
    switch (commandChar) {
      case 'u':
        Upshift();
        Serial.println("UP");
        break;
      case 'd':
        Downshift();
        Serial.println("DOWN");
        break;
      case 'b':
        _gear.breaked = HIGH;
        Serial.println("BREAK");
        break;
    }
  }
  
  if ((!_gear.breaked) && (_gear.speed < _gear.max_speed)){
    _gear.speed = _gear.speed + _gear.acceleration;
  }

  if ((!_gear.breaked) && (_gear.speed > _gear.max_speed)) {
    _gear.speed =_gear.speed - _gear.acceleration;
  }

  if (_gear.breaked) {
    _gear.acceleration = 0;

    if (_gear.speed > 0) {
      _gear.speed = _gear.speed - 30;
    }
    
    if (_gear.speed < 0) {
       _gear.speed = 0;
    }
  }
}


void Motor::Upshift(){
  if (_gear.level < sizeOfShifts() - 1) {
    _gear.level++;
    _gear.acceleration = shifts[_gear.level].acceleration;
    _gear.max_speed = shifts[_gear.level].max_speed;
  }
}

void Motor::Downshift(){
  if (_gear.level < 0) {
    _gear.level = 0;
    return;
  }
  
  if (_gear.level == 0) {
    return;
  }

   _gear.level--;
   _gear.acceleration = shifts[_gear.level].acceleration;
   _gear.max_speed = shifts[_gear.level].max_speed;

}
