#ifndef _NOEL_HPP
#define _NOEL_HPP

#include "point.hpp"
#include "inttypes.h"
#include <Servo.h>
#include "ArxContainer.hpp"

namespace Noel
{

enum State : uint8_t
{
  Idle            = 0,
  Rotate_Left     = 1,
  Rotate_Right    = 2,
  Move_Forwards   = 3,
  Move_Backwards  = 4,
  Jump            = 5,
  Demo            = 6,
  Strafe_Left     = 7,
  Strafe_Right    = 8,
  None
};

struct BotParameters
{
  uint32_t movement_speed  = 0;
  State    start_state     = Idle;
  int      legs_left_pin   = 6;
  int      legs_middle_pin = 9;
  int      legs_right_pin  = 11;
};

class Bot
{
public:
  static Bot & getInstance() { return s_bot; }
  void setup(BotParameters && parameters);
  void loop();

private:
  static Bot s_bot;
  Bot() = default;

  void demo();
  void updateState();
  void execute(State & new_state);
  void setPosition(const Point & p);
  void resetLegs(const int value = 90);
  void moveBot(arx::vector<int, 4> && values);

  void moveForwards(const int speedup = 0);
  void moveBackwards(const int speedup = 0);
  void turnLeft(const int speedup = 0);
  void turnRight(const int speedup = 0);
  void jump();
  void strafeLeft(const int speedup = 0);
  void strafeRight(const int speedup = 0);

  void clampTheta() { m_theta %= 360; }

  BotParameters       m_parameters;
  Point               m_position       = {0, 0};
  int                 m_theta          = 0;
  Point               m_new_position   = {0, 0};
  State               m_state          = Idle;
  int                 m_speed          = 0;

  class Legs
  {
    /*
     * Brown  - Ground wire connected to the ground of system
     * Red    - Powers the motor typically +5V is used
     * Orange - PWM signal is given in through this wire to drive the motor
     */
  public:
    Servo          m_servo;
    uint32_t       m_pin = 9;
    int            m_last_value = 90;
  };

  Legs             m_legs[3];
  Legs           & m_legs_left   = m_legs[0];
  Legs           & m_legs_middle = m_legs[1];
  Legs           & m_legs_right  = m_legs[2];
};

}  // namespace Noel

#endif // _NOEL_HPP
