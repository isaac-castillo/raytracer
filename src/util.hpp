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


    inline ray reflected_ray(const ray & _ray, const vec3 normal){

        ray r = _ray;
        auto new_direction = vec3(r.direction) - 2 * glm::dot(vec3(r.direction), normal) * normal;
        r.direction = vec4(new_direction, 0);
        r.position = _ray.position + r.direction * 0.001f;
        return r;
    }
    
} // namespace raytracer::util

#endif