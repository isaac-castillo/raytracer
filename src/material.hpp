#ifndef MATERIAL_HPP
#define MATEIRAL_HPP

#include "gl_typedef.hpp"

namespace raytracer {


    struct material {
        vec4 emission;
        vec4 ambient;
        vec4 specular;
        float shininess;
        vec4 diffuse;
    };


}

#endif