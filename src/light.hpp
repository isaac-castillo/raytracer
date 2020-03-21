#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "gl_typedef.hpp"
#include "shape.hpp"

namespace raytracer {

    enum light_type { direction, point};

    class light {


        private:
            light_type _type;
            vec4 _color;
            vec3 _position;

        public:
            light(light_type type, const vec3 & color, const vec3 & position);
            void set_position();
            vec3 get_color() const;
            vec3 get_position() const ;
            light_type get_light_type() const;

            vec3 lighting(const vec3 &initial, const vec3 &direction, const shape *shape) const;
    };
}

#endif