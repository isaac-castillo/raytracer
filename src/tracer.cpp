
#include <memory>

#include "tracer.hpp"
#include "ray_distance.hpp"
#include "shape.hpp"
#include "color.hpp"
#include "direction.hpp"
namespace raytracer

{


    tracer::tracer(int max_depth, scene *scene) : _max_depth(max_depth), _scene(scene)
    {
    }

    color tracer::trace(const position &initial, const direction &direction) const
    {

        return _trace_reflected(initial, direction, 0);
    }

    color tracer::_trace_reflected(const position &initial, const direction &direction, int counter) const
    {

        if (counter >= _max_depth)
        {
            return color(0, 0, 0);
        }

        auto min_dist = _closest_shape(initial, direction);

        if (!min_dist.intersect)
        {
            return color(0, 0, 0);
        }

        return _compute_lighting(min_dist, initial, direction);
    }

    ray_distance tracer::_closest_shape(const position &initial, const direction &direction) const
    {
        ray_distance min_rd;
        for (auto const &s : _scene->get_shapes())
        {

            ray_distance rd = s->inside(initial, direction);
            if (rd.intersect && rd.dist < min_rd.dist)
            {
                min_rd = rd;
            }
        }
        return min_rd;
    }

    color tracer::_compute_lighting(ray_distance &rd, const position &initial, const direction &direct) const
    {

        vec3 finalcolor(0.0, 0.0, 0.0);
        vec4 transInt = rd.shape_ptr->get_transform() * vec4(rd.pp, 1.0f);
        vec3 homogPosTransf = vec3(transInt.x / transInt.w, transInt.y / transInt.w, transInt.z / transInt.w);
        vec3 eyedirn = glm::normalize(initial.get_position() - homogPosTransf);

        vec3 normal = rd.shape_ptr->normal();

        normal = normalize(mat3(glm::transpose(glm::inverse(rd.shape_ptr->get_transform()))) * rd.shape_ptr->normal());

        normal = normalize(normal);

        for (auto const &l : _scene->get_lights())
        {
            vec3 dir, halfv;
            vec4 col;
            float d = glm::distance(l.get_position().get_position(), homogPosTransf);

            auto attenuation = _scene->get_attenuation();
            float denom = 1.0f / (attenuation.x + d * attenuation.y + pow(d, 2) * attenuation.z);

            switch (l.get_light_type())
            {
            case (light_type::direction):
                dir = glm::normalize(vec3(l.get_position().get_position()));
                halfv = normalize(dir + eyedirn);
                denom = 1;
                break;
            case (light_type::point):
                vec3 pos = l.get_position().get_position();
                dir = glm::normalize(pos - homogPosTransf);
                halfv = normalize(dir + eyedirn);
                break;
            }

            vec3 sDirection = l.get_position().get_position() - homogPosTransf;
            vec3 sInitial = homogPosTransf + sDirection * vec3(0.001);

            auto closest_shadow = _closest_shape(position(sInitial), direction(sDirection));
            if (!closest_shadow.intersect)
            {

                finalcolor += denom * l.lighting(initial, dir, rd.shape_ptr).as_vector();
            }
            else
            {
                finalcolor += vec3(0, 0, 0);
            }
        }

        vec3 res = vec3(rd.shape_ptr->get_material().emission + rd.shape_ptr->get_material().ambient) + finalcolor;
        return color(res);
    }
} // namespace raytracer
