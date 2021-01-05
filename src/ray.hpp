#ifndef RAY_HPP
#define RAY_HPP

#include "gl_typedef.hpp"
namespace raytracer {
  struct Ray {

    vec3 position{0, 0, 0};
    vec3 direction{0, 0, 0};

    Ray(vec3 _position, vec3 _direction)
        : position(_position), direction(_direction) {}

    Ray() {}

    inline vec3 at(float t) { return position + t * direction; }
  };
} // namespace raytracer
#endif