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

} // namespace raytracer
#endif