#ifndef intersect_result_hpp
#define intersect_result_hpp

#include <limits>
#include "gl_typedef.hpp"
namespace raytracer
{
    class shape;

    struct intersect_result
    {


        //A pointer to the object that intersected
        std::shared_ptr<shape> shape_ptr;

        //The distance to the object intersected
        float distance = std::numeric_limits<float>().max();

        //The result pattern 
        float intersect = false;

        //The point of intersection
        vec4 point = vec4(0,0,0,0);
    };

} // namespace raytracer
#endif