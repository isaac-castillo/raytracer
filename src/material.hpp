#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "gl_typedef.hpp"

namespace raytracer
{

    struct Material
    {
        vec3 emission{0.9f};
        vec3 ambient{0.1f};
        vec3 specular{0.9f};
        float shininess{200.0f};
        vec3 diffuse{0.9f};
    };

} // namespace raytracer

#endif