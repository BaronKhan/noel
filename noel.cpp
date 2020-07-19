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
  m_speed             = m_parameters.movement_speed;
  resetLegs();

//  demo();
}

//-----------------------------------------------------------------------------

void Bot::loop()
{
  updateState();
  
  clampTheta();
}

//-----------------------------------------------------------------------------

void Bot::updateState()
{
  State new_state = static_cast<uint8_t>(m_state);
  char input = '\0';
  while (Serial.available() > 0)  
    input = Serial.read();
  if (input)
  {
    // NB: remote controller must send index of next state
    Serial.println(input);
    const int state_value = input - '0';
    if (state_value < State::None)
      new_state = state_value;
  }

  execute(new_state);
  m_state = new_state;
}

//-----------------------------------------------------------------------------

void Bot::execute(State & new_state)
{
  switch(new_state)
  {
    case Move_Forwards:
    {
      moveForwards(m_speed);
      break;
    }
    case Move_Backwards:
    {
      moveBackwards(m_speed);
      break;
    }
    case Rotate_Left:
    {
      turnLeft(m_speed);
      break;
    }
    case Rotate_Right:
    {
      turnRight(m_speed);
      break;
    }
    case Idle:
    {
      if (new_state != m_state)
        resetLegs();
      break;
    }
    case Jump:
    {
      jump();
      new_state = Idle;
      break;
    }
    case Demo:
    {
      demo();
      new_state = Idle;
      break;
    }
    case Strafe_Left:
    {
      strafeLeft(m_speed);
      break;
    }
    case Strafe_Right:
    {
      strafeRight(m_speed);
      break;
    }
  }
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
  delay(800);
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
}

//-----------------------------------------------------------------------------

void Bot::moveForwards(const int speedup)
{
  moveBot({-1, 105, -1});
  moveBot({105+speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({50-speedup, -1, 75-speedup});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::moveBackwards(const int speedup)
{
  moveBot({-1, 105, -1});
  moveBot({50-speedup, -1, 75-speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({105+speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::turnLeft(const int speedup)
{
  moveBot({-1, 105, -1});
  moveBot({75-speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({105+speedup, -1, 75-speedup});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::turnRight(const int speedup)
{
  moveBot({-1, 105, -1});
  moveBot({105+speedup, -1, 75-speedup});
  moveBot({-1, 90, -1});
  moveBot({-1, 75, -1});
  moveBot({75-speedup, -1, 105+speedup});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::jump()
{
  moveBot({90, 150, 90});
  moveBot({-1, 30, -1});
  moveBot({-1, 90, -1});
}

//-----------------------------------------------------------------------------

void Bot::strafeLeft(const int speedup)
{
  moveBot({-1, 130, -1});
}

//-----------------------------------------------------------------------------

void Bot::strafeRight(const int speedup)
{
  moveBot({-1, 50, -1});
}

//-----------------------------------------------------------------------------

void Bot::demo()
{
  resetLegs();

  for (int i=0; i<6; ++i)
    moveForwards(m_speed);

  delay(1000);

  for (int i=0; i<4; ++i)
    moveBackwards(m_speed);

  delay(1000);

  for (int i=0; i<3; ++i)
    turnLeft(m_speed);

  delay(1000);

  for (int i=0; i<6; ++i)
    turnRight(m_speed);

  delay(1000);

  for (int i=0; i<2; ++i)
    turnLeft(m_speed);

  resetLegs();
}

//=============================================================================

}  // namespace Noel

//=============================================================================
