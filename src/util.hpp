#ifndef UTIL_HPP
#define UTIL_HPP

#include "gl_typedef.hpp"
#include "ray.hpp"
#include <iomanip>
#include <iostream>
namespace raytracer::util
{

    inline Ray inverse_ray(const mat4 transform, const Ray &_ray)
    {
        mat4 inverse = glm::inverse(transform);

        /* TODO: Rename these variables to make it more generalizable. */
        auto object_position = vec3(inverse * vec4(_ray.position, 1));
        auto object_direction = vec3(inverse * vec4(_ray.direction, 0));

        return Ray(object_position, object_direction);
    }

    inline Ray transform_ray(const mat4 transform, const Ray & _ray){

        auto world_position = vec3(transform * vec4(_ray.position, 1));
        auto world_direction = vec3(transform * vec4(_ray.direction, 0));

        return Ray(world_position, world_direction);

    }

    inline vec4 transform_to_world(const mat4 & transform, const vec3 point){
        return transform * vec4(point, 1);
    }

    inline vec3 dehomogenize(const vec4 v){
        return vec3(v.x/v.w, v.y/v.w, v.z/v.w);
    }


    inline Ray reflected_ray(const Ray & ray, const vec3 normal){

        auto new_direction = ray.direction - 2 * glm::dot (ray.direction, normal) * normal;
        return Ray(new_direction, ray.position + new_direction * 0.001f);

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