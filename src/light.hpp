#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "gl_typedef.hpp"
#include "color.hpp"
#include "position.hpp"

namespace raytracer
{

    enum class light_type
    {
        direction,
        point
    };

    class direction;
    class shape;
    class light
    {

    private:
        light_type _type;
        color _color;
        position _position;

    public:
        light(light_type type, const color &color, const position &position);
        void set_position();
        color get_color() const;
        position get_position() const;
        light_type get_light_type() const;

        color lighting(const position &initial, const direction &direction, const shape *shape) const;
    };
} // namespace raytracer

#endif