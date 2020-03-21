#include "tracer.hpp"
#include <memory>
namespace raytracer

{

tracer::tracer(int max_depth, scene * scene) : _max_depth(max_depth),  _scene(scene) {

}


vec3 tracer::trace(const vec3 &initial, const vec3 &direction) const{

    return _trace_reflected(initial, direction, 0);

}

vec3 tracer::_trace_reflected(const vec3 &initial, const vec3 &direction, int counter) const{

    if ( counter >= _max_depth){
        return vec3(0,0,0);
    }

    auto min_dist = _closest_shape(initial, direction);

    if (!min_dist.intersect)
    {
        return vec3(0,0,0);
    }
}

ray_distance tracer::_closest_shape(const vec3 &initial, const vec3 &direction) const{
    ray_distance min_rd;
    min_rd.dist = std::numeric_limits<float>().max();
    for (auto const &s : _scene->get_shapes())
    {
        auto rd = s->inside(initial, direction);
        if (rd.intersect && rd.dist < min_rd.dist)
        {
            min_rd.dist = rd.dist;
            min_rd.intersect = true;
            min_rd.shape = std::make_unique<shape>(s);
        }
    }
    return min_rd;

}

vec3 tracer::_compute_lighting(std::unique_ptr<shape> shape, const vec3 &initial, const vec3 &direction) const
{

    vec3 finalcolor;
    vec4 transInt = shape->get_transform() * vec4(direction, 1.0f);
    vec3 homogPosTransf = vec3(transInt.x / transInt.w, transInt.y / transInt.w, transInt.z / transInt.w);
    vec3 eyedirn = glm::normalize(initial - homogPosTransf);

    vec3 normal = shape->normal();

    normal = normalize(mat3(glm::transpose(glm::inverse(shape->get_transform()))) * shape->normal());

    normal = normalize(normal);


    for (auto const & l : _scene->get_lights())
    {
        vec3 dir, halfv;
        vec4 col;
        float d = glm::distance(l.get_position(), homogPosTransf);

        float denom = 1.0f / (_scene->attenuation.x + d * _scene->attenuation.y + pow(d, 2) * _scene->attenuation.z);
        
        switch(l.get_light_type()){
            case(light_type::direction):
                dir = glm::normalize(vec3(l.get_position()));
                halfv = normalize(dir + eyedirn);
                denom = 1;
                break;
            case(light_type::point):
                vec3 pos = l.get_position();
                dir = glm::normalize(pos - homogPosTransf);
                halfv = normalize(dir + eyedirn);
                break;
        }

        vec3 sDirection = l.get_position() - homogPosTransf;
        vec3 sInitial = homogPosTransf + sDirection * vec3(0.001);

        auto closest_shadow = _closest_shape(sInitial, sDirection);
        if (closest_shadow.intersect)
        {

            finalcolor += denom * l.lighting(initial, dir, shape.get());
        }
        else
        {
            finalcolor += vec3(0, 0, 0);
        }
    }

    return vec3(shape->get_material().emission + shape->get_material().ambient) + finalcolor;

}
} // namespace raytracer
