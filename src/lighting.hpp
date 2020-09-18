#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "gl_typedef.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "light.hpp"

namespace raytracer::algorithm {


    /* The Blinn-Phong lighting algorithm: */
    inline vec4 lighting(const vec4 & dir, const shape const * shape, const light const * light, const vec4 & halfvec)
    {

        //Build up some variables for us to use. 
        const auto [_, light_color, light_position] = *light;
        const auto [_, _, specular, shininess, diffuse] = shape->get_material();
        auto normal = shape->normal();

        // The Blinn-Phong Lighting Algorithm 
        float nDotL = glm::dot(normal, dir);
        vec4 lambert = shape->get_material().diffuse * light_color * std::max(nDotL, 0.0f);

        float nDotH = glm::dot(normal, halfvec);
        vec4 phong = specular * light_color * std::pow(std::max(nDotH, 0.0f), shininess);
        vec4 retval = lambert + phong;

        return vec4(retval);
    }
}
#endif
