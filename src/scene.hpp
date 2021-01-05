#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "camera.hpp"
#include "gl_typedef.hpp"
#include "light.hpp"
#include "shape.hpp"
namespace raytracer {

  class tracer;
  class Scene {

  private:
    Camera _cam;
    std::vector<Light> _lights;
    std::vector<std::unique_ptr<Shape>> _shapes;

    int _width = {0};
    int _height = {0};
    int _num_shapes = {0};

    vec3 _attenuation{1, 0, 0};

  public:
    Scene();
    void set_camera(const vec3 &eye, const vec3 &center, const vec3 &up,
                    const float &fovy);
    void set_camera(const Camera &cam);
    void set_height(int height);
    void set_width(int width);
    void add_shape(std::unique_ptr<Shape> &_shape);
    void add_light(const Light &light);

    void print() const;
    int get_width() const;
    int get_height() const;
    const std::vector<std::unique_ptr<Shape>> &get_shapes();
    std::vector<vec3> render_scene(const tracer &tracer);
    std::vector<Light> get_lights();

    Camera get_cam();
    vec3 get_attenuation() const;
    void set_attenuation(const vec3 &);
  };
} // namespace raytracer
#endif
