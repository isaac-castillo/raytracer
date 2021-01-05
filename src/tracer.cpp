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

    tracer::tracer(int max_depth, std::shared_ptr<Scene> scene) : _max_depth(max_depth), _scene(scene)
    {
    }

    vec3 tracer::trace(const Ray &_ray) const
    {

        return _trace_reflected(_ray, 0);
    }

    vec3 tracer::_trace_reflected(const Ray &_ray, int counter) const
    {

        if (counter >= _max_depth)
        {
            return vec4(0, 0, 0, 0);
        }

        auto min_dist = _closest_shape(_ray);

        if (!min_dist)
        {
            return vec3(0, 0, 0);
        }

        vec3 color = _compute_color(min_dist.value(), _ray);
        // std::cout << "color: " << std::endl;
        // util::print_vector(color);

        //reflected light
        Ray reflected_ray = util::reflected_ray(_ray, min_dist.value().shape_ptr->normal());
        // util::print_vector(reflected_ray.position);
        // util::print_vector(reflected_ray.direction);

        return color + vec3(min_dist.value().shape_ptr->get_material().specular) * _trace_reflected(reflected_ray, ++counter);
    }

    std::optional<IntersectResult> tracer::_closest_shape(const Ray &ray) const
    {
        std::optional<IntersectResult> min_intersection;
        for (auto const &shape : _scene->get_shapes())
        {

            std::optional<IntersectResult> curr_result = shape->inside(ray);

            if((curr_result && !min_intersection) || (curr_result && curr_result.value().distance < min_intersection.value().distance)){
                min_intersection = curr_result;
            }
        }

        return min_intersection;
    }

    vec3 tracer::_compute_color(IntersectResult &intersection_result, const Ray &ray) const
    {

        vec3 finalcolor(0, 0, 0);
        const auto &[shape, distance, point] = intersection_result;
        vec3 eye_direction = glm::normalize(ray.position - point);

        for (auto const &light : _scene->get_lights())
        {

            const auto [light_type, light_color, light_position] = light;
            vec3 light_direction;
            vec3 halfv;

            float d = glm::distance(light_position, point);
            auto attenuation = _scene->get_attenuation();
            float denom = 1.0f / (attenuation.x + d * attenuation.y + pow(d, 2) * attenuation.z);

            switch (light_type)
            {

            // Directional lights have no attenuation (denom = 1)
            case (LightType::direction):

                light_direction = glm::normalize(vec3(light_position));
                halfv = normalize(light_direction + eye_direction);
                break;

            case (LightType::point):
                vec3 pos = light_position;
                light_direction = glm::normalize(pos - point);
                halfv = normalize(light_direction + eye_direction);
                break;
            }
            Ray shadow_ray;
            shadow_ray.direction = light_position - point;
            shadow_ray.position = point + shadow_ray.direction * vec3(0.001);

            vec3 normal = shape->normal(point);
            auto closest_shadow = _closest_shape(shadow_ray);

            if (!closest_shadow){
                finalcolor += algorithm::lighting(light_direction, shape.get(), light, normal, halfv);
            }            
            else
            {
                finalcolor += vec3(0, 0, 0);
            }
        }

        return finalcolor;
    }
} // namespace raytracer
