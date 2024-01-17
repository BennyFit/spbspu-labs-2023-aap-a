#ifndef SHAPE_H
#define SHAPE_H
#include "base-types.hpp"
namespace strelyaev
{
  class Shape
  {
    public:
    virtual ~Shape() = default;
     virtual double getArea() const = 0;
     virtual rectangle_t getFrameRect() const = 0;
     virtual void move(point_t) = 0;
     virtual void move(double, double) = 0;
     virtual void scale(double) = 0;
  };
}
#endif
