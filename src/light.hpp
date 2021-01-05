#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "gl_typedef.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include "util.hpp"
namespace raytracer
{

    enum class LightType
    {
        direction,
        point
    };

    struct Light
    {

        explicit Light(LightType _type, const vec3 &_color, const vec3 &_position) : type(_type), color(_color), position(_position)
        {
        }

        LightType type{LightType::direction};
        vec3 color{0, 0, 0};
        vec3 position{0, 0, 0};

        inline void print() const
        {
            std::cout << "type: " << (type == LightType::direction ? "direction" : "point");
            std::cout << "color: ";
            util::print_vector(color);
            std::cout << "position: ";
            util::print_vector(position);
        }
    };
} // namespace raytracer

#endif