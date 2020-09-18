#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "gl_typedef.hpp"

namespace raytracer
{

    enum class light_type
    {
        direction,
        point
    };

    class light
    {

    public:
        light(light_type type, const vec4 &color, const vec4 &position);
        light_type _type;
        vec4 _color;
        vec4 _position;

    };
} // namespace raytracer

#endif