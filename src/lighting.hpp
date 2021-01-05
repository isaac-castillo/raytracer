#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "gl_typedef.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "shape.hpp"

namespace raytracer::algorithm {

  /* The Blinn-Phong lighting algorithm: */
  inline vec3 lighting(const vec3 &light_direction, const Shape *shape,
                       const Light &light, const vec3 normal,
                       const vec3 &halfvec) {

    // std::cout << "light_direction: ";
    // util::print_vector(light_direction);

    // std::cout << "normal: ";;
    // util::print_vector(normal);

    // std::cout << "halfvec: ";
    // util::print_vector(halfvec);

    // std::cout << "light pos: ";
    // util::print_vector(light.position);

    // Build up some variables for us to use.
    const auto [light_type, light_color, light_position] = light;
    const auto [emission, ambient, specular, shininess, diffuse] =
        shape->get_material();

    vec3 color = light_color * emission;
    vec3 ambient_final = color * ambient;

    // The Blinn-Phong Lighting Algorithm
    float nDotL = glm::dot(normal, light_direction);
    vec3 lambert = diffuse * color * std::max(nDotL, 0.0f);

    float nDotH = glm::dot(normal, halfvec);
    vec3 phong =
        specular * light_color * std::pow(std::max(nDotH, 0.0f), shininess);
    vec3 retval = lambert + phong + ambient_final;

    // std::cout << "retval: ";
    // util::print_vector(retval);
    return retval;
  }

  inline vec4 phong(const vec4 &dir, const Shape *shape, const Light &light) {
    return vec4();
  }
} // namespace raytracer::algorithm
#endif
