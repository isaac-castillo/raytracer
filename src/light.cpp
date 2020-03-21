#include "light.hpp"
#include <cmath>

namespace raytracer {

    light::light(light_type type, const vec3 &color, const vec3 &position){

    }
    void light::set_position()
    {

    }
    vec3 light::get_color() const
    {
        return _color;
    }
    vec3 light::get_position() const
    {
        return _position;
    }
    light_type light::get_light_type() const
    {
        return _type;
    }

    vec3 light::lighting(const vec3 &initial, const vec3 &direction, const shape *shape) const {

        // if( lightcolor.x >= 0.8 )
        //  normal2 =  vec3(normal.x + rand() % 2, normal.y + rand() % 2 , normal.z + rand() % 2);
        //vec3 normal2 = vec3( ((double) rand() / (RAND_MAX) + 0.5)  * normal.x, ((double) rand() / (RAND_MAX) + 0.5)  * normal.y, ((double) rand() / (RAND_MAX) + 0.5)  * normal.z);

        vec4 transInt = shape->get_transform() * vec4(direction, 1.0f);
        vec3 homogPosTransf = vec3(transInt.x / transInt.w, transInt.y / transInt.w, transInt.z / transInt.w);
        vec3 eyedirn = glm::normalize(initial - homogPosTransf);
        vec3 normal = shape->normal();

        float nDotL = glm::dot(normal, direction);
        vec4 lambert = shape->get_material().diffuse * _color * std::max(nDotL, 0.0f);

        vec3 halfvec = normalize(direction + eyedirn);
        float nDotH = glm::dot(normal, halfvec);
        vec4 phong = shape->get_material().diffuse * _color * vec4(pow(std::max(nDotH, 0.0f), shape->get_material().shininess));
        vec4 retval = lambert + phong;

        return vec3(retval);
    }
}
