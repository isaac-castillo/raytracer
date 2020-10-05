#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>



#include "camera.hpp"
#include "gl_typedef.hpp"
#include "light.hpp"
#include "shape.hpp"
namespace raytracer {

class tracer;
class scene
{

private:
    camera _cam;
    std::vector<light> _lights;
    std::vector<std::unique_ptr<shape>> _shapes;

    int _width = {0};
    int _height = {0};
    int _num_shapes = {0};

    vec3 _attenuation;


public:
    scene();
    void set_camera(const vec3 & eye, const vec3 & center, const vec3 & up, const float & fovy);
    void set_camera(const camera & cam);
    void set_height(int height);
    void set_width(int width);
    void add_shape(std::unique_ptr<shape> & _shape);
    void add_light(const light & light);

    void print() const;
    int get_width() const;
    int get_height() const;
    const std::vector<std::unique_ptr<shape>> & get_shapes();
    std::vector<vec3> render_scene(const tracer & tracer);
    std::vector<light> get_lights();

    camera get_cam();
    vec3 get_attenuation() const; 
    void set_attenuation(const vec3 &);
};
}
#endif
