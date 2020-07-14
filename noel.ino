// noel.ino
// Requires C++17

#include "noel.hpp"
#include "cpp4arduino.hpp"

using namespace Noel;
using namespace cpp4arduino;

//=============================================================================

void setup()
{
  BotParameters parameters
  {
    .movement_speed  = 2,
    .start_state     = Move_Forwards,
    .legs_left_pin   = 6,
    .legs_middle_pin = 9,
    .legs_right_pin  = 11
  };
  Bot::getInstance().setup(move(parameters));
}

//-----------------------------------------------------------------------------

void loop()
{
  Bot::getInstance().loop();
}

//=============================================================================
