#ifndef UTIL_HPP
#define UTIL_HPP

#include "gl_typedef.hpp"
#include "ray.hpp"

namespace raytracer::util
{

    inline ray inverse_ray(const mat4 transform, const ray &_ray)
    {
        ray r;

        mat4 inverse = glm::inverse(transform);
        r.position = inverse * _ray.position;
        r.direction = inverse * _ray.direction;

        return r;
    }

    inline vec4 dehomogenize(const vec4 v){
        return vec4(v.x/v.w, v.y/v.w, v.z/v.w, 1);
    }
    
} // namespace raytracer::util

#endif