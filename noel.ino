// noel.ino
// Requires C++17 (build with std=c++17)
// Arduino Nano (ATmega328P)

#include "noel.hpp"
#include "cpp4arduino.hpp"

using namespace Noel;
using namespace cpp4arduino;

//=============================================================================

void setup()
{
  BotParameters parameters
  {
    .movement_speed  = 5,
    .start_state     = Idle,
    .legs_left_pin   = 11,
    .legs_middle_pin = 9,
    .legs_right_pin  = 6
  };
  Bot::getInstance().setup(move(parameters));

  Serial.begin(9600);
}

//-----------------------------------------------------------------------------

void loop()
{ 
  Bot::getInstance().loop();
}

//=============================================================================
