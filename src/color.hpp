#ifndef COLOR_HPP
#define COLOR_HPP
#include "gl_typedef.hpp"

namespace raytracer
{
    class color
    {

    private:
        vec4 _color;
        int _alpha{1};

    public:
        color(int r, int g, int b) : _color(r, g, b, 1)
        {
        }

        color(vec3 color) : _color(vec4(color, 1))
        {
        }

        color(vec4 color) : _color(color)
        {
        }

        inline vec3 get_color() const
        {
            return vec3(_color);
        }
        inline int get_alpha() const
        {
            return _alpha;
        }
        inline vec4 as_vector() const
        {
            return _color;
        }
    };
} // namespace raytracer
#endif