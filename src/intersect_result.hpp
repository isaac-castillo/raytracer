#ifndef intersect_result_hpp
#define intersect_result_hpp

#include <limits>
#include "gl_typedef.hpp"
#include "position.hpp"
namespace raytracer
{
    class shape;

    struct intersect_result
    {


        //A pointer to the object that intersected
        std::shared_ptr<shape> shape_ptr;

        //The distance to the object intersected
        float distance = std::numeric_limits<float>().max();

        //The Result
        float intersect = false;

        //
        position point = position(vec4(0));
    };

} // namespace raytracer
#endif