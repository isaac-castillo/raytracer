#ifndef RAY_HPP
#define RAY_HPP

#include "gl_typedef.hpp"
namespace raytracer
{
    struct ray
    {
        vec4 position;
        vec4 direction;

        inline vec4 at(float t){
            return position + t * direction;
    }
    };
} // namespace raytracer
#endif