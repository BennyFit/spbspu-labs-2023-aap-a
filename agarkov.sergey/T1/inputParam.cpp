#include "inputparam.hpp"
#include <istream>
#include <cstddef>

void agarkov::inputArray(std::istream& input, double* parameters, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    input >> parameters[i];
  }
}
