#ifndef RAY_HPP
#define RAY_HPP

#include "gl_typedef.hpp"
namespace raytracer
{
    struct ray
    {
        vec4 position;
        vec4 direction;
    };
} // namespace raytracer
#endif