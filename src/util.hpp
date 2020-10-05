#ifndef UTIL_HPP
#define UTIL_HPP

#include "gl_typedef.hpp"
#include "ray.hpp"
#include <iomanip>
#include <iostream>
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

    inline ray transform_ray(const mat4 transform, const ray & _ray){

        ray return_ray;
        return_ray.position = transform * _ray.position;
        return_ray.direction = transform * _ray.direction;

        return return_ray;
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

    inline void print_vector(vec3 v){
        std::cout << std::setprecision(3) << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl; 
    }

    inline void print_vector(vec4 v){
        std::cout << std::setprecision(3) << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl; 
    }

    inline void print_matrix(mat4 v){

        print_vector(v[0]);        
        print_vector(v[1]);
        print_vector(v[2]);
        print_vector(v[3]);
    }


    
} // namespace raytracer::util

#endif