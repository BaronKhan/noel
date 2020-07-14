// point.hpp

#ifndef _POINT_HPP
#define _POINT_HPP

namespace Noel
{

constexpr double pi = 3.14159265358979323846;

class Point
{
public:
  int     distanceTo(const Point & p) const noexcept;
  int     distanceToSquared(const Point & p) const noexcept;
  int     angleTo(const Point & p, const int theta = 0) const noexcept;
  Point & operator+(const Point & p) noexcept;
  Point & operator-(const Point & p) noexcept;

  int x;
  int y;
};

}  // namespace Noel

#endif  // _POINT_HPP
