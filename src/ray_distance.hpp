#ifndef ray_distance_hpp
#define ray_distance_hpp

#include <limits>
#include "gl_typedef.hpp"

namespace raytracer
{
    class shape;

    struct ray_distance
    {

        shape *shape_ptr = nullptr;
        float dist = std::numeric_limits<float>().max();
        float intersect = false;
        vec3 pp = vec3(0, 0, 0);
    };

} // namespace raytracer
#endif