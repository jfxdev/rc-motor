#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

struct Gear {
  bool automatic;
  bool direction;
  int speed;
  int max_speed;
  byte level;
  byte acceleration;
  bool breaked;
};

struct Shift {
  int acceleration;
  int max_speed;
  bool direction;
};

class Motor
{
  public:
    Motor();
    void Setup(byte motorAPin, byte motorBPin, byte directionAPin, byte directionBPin, bool automatic);
    void Print();
    void Accelerate();
    void Upshift();
    void Downshift();
    void Break();
  private:
    byte _motorAPin;
    byte _motorBPin;
    byte _directionAPin;
    byte _directionBPin;
    Gear _gear;
};

#endif
