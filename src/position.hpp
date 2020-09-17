#ifndef POSITION_HPP
#define POSITION_HPP
#include "gl_typedef.hpp"
namespace raytracer
{
    /* A position is actually implemented as a vec4 */
    class position
    {

    private:
        vec4 _position;

    public:

        explicit position(vec3 position): _position(vec4(position, 1))   {
            
        }
        inline vec4 get_position() const {
            return _position;
        }

    };

    inline position operator*(mat4 & transform, const position & pos){
        return position(transform * pos.get_position());
    }

    inline position operator+(position & left, const position & right){
        return position(left.get_position() + right.get_position());
    }
} // namespace raytracer

#endif