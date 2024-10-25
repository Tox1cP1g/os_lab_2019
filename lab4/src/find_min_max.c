#include "find_min_max.h"

#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (unsigned int i = begin; i < end; i++) {
    int a = i[array];
    if (a > min_max.max) min_max.max = a;
    if (a < min_max.min) min_max.min = a;
  }

  return min_max;
}
