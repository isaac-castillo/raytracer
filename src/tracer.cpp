#include <memory>

#include "tracer.hpp"
#include "intersect_result.hpp"
#include "shape.hpp"
#include "ray.hpp"
#include "gl_typedef.hpp"
#include "util.hpp"
#include "lighting.hpp"

namespace raytracer

{

    tracer::tracer(int max_depth, std::shared_ptr<scene> scene) : _max_depth(max_depth), _scene(scene)
    {
    }

    vec3 tracer::trace(const ray & _ray) const
    {

        return _trace_reflected(_ray, 0);
    }

    vec3 tracer::_trace_reflected(const ray & _ray, int counter) const
    {

        if (counter >= _max_depth)
        {
            return vec4(0, 0, 0, 0);
        }

        auto min_dist = _closest_shape(_ray);

        if (!min_dist.intersect)
        {
            return vec4(0, 0, 0, 0);
        }

        vec3 color = _compute_color(min_dist, _ray);

        //reflected light
        ray reflected_ray = util::reflected_ray(_ray, min_dist.shape_ptr->normal());
        return color + vec3(min_dist.shape_ptr->get_material().specular) * _trace_reflected(reflected_ray, ++counter);
        
    }

    intersect_result tracer::_closest_shape(const ray & ray) const
    {
        intersect_result min_intersection;
        for (auto const &shape : _scene->get_shapes())
        {

            intersect_result curr_result = shape->inside(ray);
            if (curr_result.intersect && curr_result.distance < min_intersection.distance)
            {
                min_intersection = curr_result;
            }
        }
        return min_intersection;
    }

    vec3 tracer::_compute_color(intersect_result &intersection_result, const ray & _ray) const
    {

        vec3 finalcolor(0.0, 0.0, 0.0);
        const auto [shape, distance, _, point] = intersection_result;


        vec4 dehomgenized_pos = util::dehomogenize(point);  
        vec3 eyedirn = glm::normalize(_ray.position - dehomgenized_pos);

        for (auto const &light : _scene->get_lights())
        {

            const auto [light_type, light_position, light_color] = light;
            vec3 dir, halfv;
            vec4 col;

            float d = glm::distance(light_position, dehomgenized_pos);
            auto attenuation = _scene->get_attenuation();
            float denom = 1.0f / (attenuation.x + d * attenuation.y + pow(d, 2) * attenuation.z);

            switch (light_type)
            {

            // Directional lights have no attenuation (denom = 1)
            case (light_type::direction):
                dir = glm::normalize(vec3(light_position));
                halfv = normalize(dir + eyedirn);
                denom = 1;
                break;

            case (light_type::point):
                vec4 pos = light_position;
                dir = glm::normalize(pos - dehomgenized_pos);
                halfv = normalize(dir + eyedirn);
                break;
            }

            ray _ray;
            _ray.direction = light_position - dehomgenized_pos;
            _ray.position = dehomgenized_pos + _ray.direction * vec4(0.001);

            auto closest_shadow = _closest_shape(_ray);
            if (!closest_shadow.intersect)
            {

                finalcolor += denom * vec3(algorithm::lighting(vec4(dir, 0), shape.get(), light, vec4(halfv, 0)));
            }
            else
            {
                finalcolor += vec3(0, 0, 0);
            }
        }

        vec3 res = vec3(shape->get_material().emission + shape->get_material().ambient) + finalcolor;
        return res;
    }
} // namespace raytracer
