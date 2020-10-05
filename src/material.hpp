#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "gl_typedef.hpp"

namespace raytracer {


    struct material {
        vec4 emission = vec4(0.9);
        vec4 ambient = vec4(0.1);
        vec4 specular = vec4(0.9);
        float shininess = 200.0;
        vec4 diffuse = vec4(0.9);
    };


}

#endif