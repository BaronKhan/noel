// noel.cpp

#include "noel.hpp"
#include "Arduino.h"

//=============================================================================

namespace Noel
{

//=============================================================================

Bot Bot::s_bot;

//=============================================================================

void Bot::setup(BotParameters && parameters)
{
  m_parameters        = parameters;
  m_legs_left.m_pin   = m_parameters.legs_left_pin;
  m_legs_middle.m_pin = m_parameters.legs_middle_pin;
  m_legs_right.m_pin  = m_parameters.legs_right_pin;
  resetLegs();

//  demo();
}

//-----------------------------------------------------------------------------

void Bot::demo()
{
  for (int i=0; i<6; ++i)
    moveForwards();

  delay(1000);

  for (int i=0; i<4; ++i)
    moveBackwards();

  delay(1000);

  for (int i=0; i<3; ++i)
    turnLeft();

  delay(1000);

  for (int i=0; i<6; ++i)
    turnRight();

  delay(1000);

  for (int i=0; i<2; ++i)
    turnLeft();

  resetLegs();
}

//-----------------------------------------------------------------------------

void Bot::loop()
{

  clampTheta();
}

//-----------------------------------------------------------------------------

void Bot::updateState()
{
}

//-----------------------------------------------------------------------------

void Bot::setPosition(const Point & p)
{
}

//-----------------------------------------------------------------------------

void Bot::resetLegs(const int value)
{
  for (int i = 0; i < 3; ++i)
  {
    auto & legs = m_legs[i];
    legs.m_servo.attach(legs.m_pin);
    legs.m_servo.write(value);
    legs.m_last_value = value;
  }
  delay(1000);
  for (auto & legs : m_legs)
    legs.m_servo.detach();
}

//-----------------------------------------------------------------------------

void Bot::moveBot(arx::vector<int, 4> && values)
{
  // ~800ms from 0-180
  unsigned long delay_time = 0;
  for (int i = 0; i < 3; ++i)
  {
    const int value = values[i];
    auto & legs = m_legs[i];
    const unsigned diff = abs(legs.m_last_value - value);
    if (value >= 0 && diff)
    {
      delay_time = max(delay_time, (diff * 800) / 180);
      legs.m_servo.attach(legs.m_pin);
      legs.m_servo.write(value);
      legs.m_last_value = value;
    }
  }
  delay(delay_time);
  for (auto & legs : m_legs)
    legs.m_servo.detach();

//  delay(1000);  // TODO: REMOVE
}

//-----------------------------------------------------------------------------

void Bot::moveForwards(const int speedup)
{
  moveBot({-1, 105, -1});
  moveBot({105+speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({75-speedup, -1, 90-speedup});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::moveBackwards(const int speedup)
{
  moveBot({-1, 105, -1});
  moveBot({75-speedup, -1, 90-speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({105+speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::turnLeft(const int speedup)  // ?
{
  moveBot({-1, 105, -1});
  moveBot({75-speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({105+speedup, -1, 75-speedup});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::turnRight(const int speedup)  // ?
{
  moveBot({-1, 105, -1});
  moveBot({105+speedup, -1, 75-speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({75-speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
}


//=============================================================================

}  // namespace Noel

//=============================================================================
