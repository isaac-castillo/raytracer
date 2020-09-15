#ifndef POSITION_HPP
#define POSITION_HPP
#include "gl_typedef.hpp"

namespace raytracer
{
    class position
    {

    private:
        vec3 _position;

    public:

        position(vec3 position): _position(position) {
            
        }
        inline vec3 get_position() const {
            return _position;
        }
    };
} // namespace raytracer

#endif