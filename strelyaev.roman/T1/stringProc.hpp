#ifndef STRING_PROCESSING_HPP
#define STRING_PROCESSING_HPP
#include "shape.hpp"
#include "base-types.hpp"
#include <iostream>
namespace strelyaev
{
  char * inputString(std::istream & in);
  Shape * getShape(const char string[]);
  void isotrScale(Shape * shape, const point_t point, const double k);
  void scaleShapes(Shape ** list, size_t current_index, const double arguments[3], std::ostream & out);
  void printErrors(const char ** errors, size_t maxshapes, std::ostream&);
  void outputShapes(std::ostream & out, Shape ** list, size_t current_index);
}
#endif
