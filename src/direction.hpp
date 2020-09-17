#ifndef DIRECTION_HPP
#define DIRECTION_HPP
#include "gl_typedef.hpp"

namespace raytracer
{
    class direction
    {

    private:
        vec3 _direction;

    public:
        direction(vec3 direction) : _direction(direction)
        {
        }
        inline vec3 get_direction() const
        {
            return _direction;
        }
    };


    inline direction operator*(mat4 & transform, const direction & dir){
        // upcasts the vec3 to a vec4 with 0 in the fourth field.
        return direction(transform * dir.get_direction());
    }

    template <typename T>
    inline position operator*(const direction &dir, T type){
        return position(dir * type);
    }
} // namespace raytracer
#endif