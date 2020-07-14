// point.cpp

#include "point.hpp"
#include <math.h>

//=============================================================================

namespace Noel
{

//=============================================================================

inline int Point::distanceTo(const Point & p) const noexcept
{
  const auto dist_squared = distanceToSquared(p);
  return (dist_squared > -1) ? sqrt(dist_squared) : -1;
}

//-----------------------------------------------------------------------------

inline int Point::distanceToSquared(const Point & p) const noexcept
{
  return pow(x - p.x, 2) + pow(y - p.y, 2);
}

//-----------------------------------------------------------------------------

inline int Point::angleTo(const Point & p, const int theta) const noexcept
{
  return ((atan2(p.y - y, p.x - x)*360)/(2*pi)) - theta;
}

//-----------------------------------------------------------------------------

inline Point & Point::operator+(const Point & p) noexcept
{
  x += p.x;
  y += p.y;

  return *this;
}

//-----------------------------------------------------------------------------

inline Point & Point::operator-(const Point & p) noexcept
{
  x -= p.x;
  y -= p.y;

  return *this;
}

//=============================================================================

}  // namespace Noel

//=============================================================================
