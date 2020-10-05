#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "gl_typedef.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "light.hpp"

namespace raytracer::algorithm {


    /* The Blinn-Phong lighting algorithm: */
    inline vec4 lighting(const vec4 & dir, const shape * shape, const light & light, const vec4 & halfvec)
    {
        std::cout << "dir: ";
        util::print_vector(dir);

        std::cout << "normal: ";;
        // util::print_vector(shape->normal());

        std::cout << "halfvec: ";
        util::print_vector(halfvec);

        std::cout << "light pos: ";
        util::print_vector(light.position);

                //Build up some variables for us to use. 
        const auto [light_type, light_color, light_position] = light;
        const auto [emission, ambient, specular, shininess, diffuse] = shape->get_material();
        auto normal = shape->normal(dir);

        // The Blinn-Phong Lighting Algorithm 
        float nDotL = glm::dot(normal, dir);
        vec4 lambert = shape->get_material().diffuse * light_color * std::max(nDotL, 0.0f);

        float nDotH = glm::dot(normal, halfvec);
        vec4 phong = specular * light_color * std::pow(std::max(nDotH, 0.0f), shininess);
        vec4 retval = lambert + phong;

        std::cout << "retval: ";
        util::print_vector(retval);
        return vec4(retval);
    }
}
#endif
