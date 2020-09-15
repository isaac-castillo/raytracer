#include "light.hpp"
#include <cmath>
#include "position.hpp"
#include "shape.hpp"
#include "direction.hpp"

namespace raytracer
{

    light::light(light_type type, const color &color, const position &position) : _type(type), _color(color), _position(position)
    {
    }
    void light::set_position()
    {
    }
    color light::get_color() const
    {
        return _color;
    }
    position light::get_position() const
    {
        return _position;
    }
    light_type light::get_light_type() const
    {
        return _type;
    }

    color light::lighting(const position &initial, const direction &direction, const shape *shape) const
    {

        vec4 transInt = shape->get_transform() * vec4(direction.get_direction(), 1.0f);

        vec3 homogPosTransf = vec3(transInt.x / transInt.w, transInt.y / transInt.w, transInt.z / transInt.w);
        vec3 eyedirn = glm::normalize(initial.get_position() - homogPosTransf);
        vec3 normal = shape->normal();

        float nDotL = glm::dot(normal, direction.get_direction());
        vec4 lambert = shape->get_material().diffuse * _color.as_vector() * std::max(nDotL, 0.0f);

        vec3 halfvec = normalize(direction.get_direction() + eyedirn);
        float nDotH = glm::dot(normal, halfvec);
        vec4 phong = shape->get_material().specular * _color.as_vector() * vec4(pow(std::max(nDotH, 0.0f), shape->get_material().shininess));
        vec4 retval = lambert + phong;

        return color(retval.x, retval.y, retval.z);
    }
} // namespace raytracer
