#ifndef intersect_result_hpp
#define intersect_result_hpp

#include "gl_typedef.hpp"
#include <limits>

namespace raytracer {
  class Shape;

  struct IntersectResult {

    // A pointer to the object that intersected
    std::shared_ptr<Shape> shape_ptr = nullptr;

    // The distance to the object intersected
    float distance = std::numeric_limits<float>().max();

    // The point of intersection
    vec3 point = vec3(0, 0, 0);
  };

} // namespace raytracer
#endif