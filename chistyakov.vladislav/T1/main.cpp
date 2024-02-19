#include <iostream>
#include "rectangle.hpp"
#include "complexquad.hpp"
#include "shape.hpp"
#include "inputShapes.hpp"
#include "isotropScale.hpp"
#include "outputShape.hpp"

int main()
{
  using namespace chistyakov;
  double scaleInfo[3]{};
  Shape * shapes[1000]{};
  size_t size = 0;

  for (size_t i = 0; i < 1000; ++i)
  {
    shapes[i] = nullptr;
  }

  try
  {
    inputShapes(std::cin, shapes, scaleInfo, size);
    outputShape(std::cout, shapes, size);
    isotropScale(shapes, {scaleInfo[0], scaleInfo[1]}, scaleInfo[2], size);
    outputShape(std::cout, shapes, size);
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << "Achtung " << e.what() << "\n";
    freeArray(shapes, 1000);
    return 1;
  }
  catch (const std::logic_error & e)
  {
    std::cout << "Error: " << e.what() << "\n";
    freeArray(shapes, 1000);
    return 2;
  }

  freeArray(shapes, 1000);

  return 0;
};
