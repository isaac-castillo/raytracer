#ifndef MATERIAL_HPP
#define MATEIRAL_HPP

#include "gl_typedef.hpp"

namespace raytracer {


    struct material {
        vec4 emission = vec4(0);
        vec4 ambient = vec4(0);
        vec4 specular = vec4(0);
        float shininess = 0;
        vec4 diffuse = vec4(0);
    };


}

#endif