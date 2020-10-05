#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "gl_typedef.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include "util.hpp"
namespace raytracer
{

    enum class light_type
    {
        direction,
        point
    };

    struct light
    {

        light(light_type _type, const vec4 & _color, const vec4 & _position) :
        type(_type), color(_color), position(_position)  {
            
        }

        light_type type;
        vec4 color;
        vec4 position;

        inline void print() const{
            std::cout << "type: " << (type == light_type::direction ? "direction" : "point");
            std::cout << "color: ";
            util::print_vector( color);
            std::cout << "position: ";
            util::print_vector(position);
        }
    };
} // namespace raytracer

#endif