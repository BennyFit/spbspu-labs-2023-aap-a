#include <stdexcept>
#include "scaleOperations.hpp"
#include "inputAndOutputOperations.hpp"

void arakelyan::isoScale(arakelyan::Shape * shapeObj, const point_t scalePoint, const double scaleK)
{
   point_t initialPos = shapeObj->getFrameRect().pos_;
   shapeObj->move(scalePoint);
   point_t modifiedPos = shapeObj->getFrameRect().pos_;
   double dx = (modifiedPos.x_ - initialPos.x_) * scaleK;
   double dy = (modifiedPos.y_ - initialPos.y_) * scaleK;
   shapeObj->scale(scaleK);
   shapeObj->move(-dx, -dy);
}

void arakelyan::scaleFunction(arakelyan::Shape ** shapes, const size_t shapesCount, const point_t scalePoint, const double scaleK)
{
  if (scaleK < 0.0)
  {
    throw std::logic_error("k of scale cannot be less than zero!");
  }
  for (size_t i = 0; i < shapesCount; i++)
  {
    shapeOutput(std::cout, shapes, shapesCount);
    isoScale(shapes[i], scalePoint, scaleK);
    shapeOutput(std::cout, shapes, shapesCount);
  }
}
