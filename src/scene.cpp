#include "scene.hpp"
#include "gl_typedef.hpp"

#include "ray.hpp"
#include "shape.hpp"
#include "tracer.hpp"
#include <iostream>
#include <memory>
#include <vector>
namespace raytracer {

  Scene::Scene() : _attenuation(vec3(1, 0, 0)), _cam() {}
  void Scene::set_camera(const vec3 &look_from, const vec3 &look_at,
                         const vec3 &up, const float &fovy) {
    _cam.set_look_from(look_from);
    _cam.set_look_at(look_at);
    _cam.set_up(up);
    _cam.set_fovy(fovy);
  }

  void Scene::set_camera(const Camera &cam) { _cam = cam; }

  void Scene::set_height(int height) { this->_height = height; }

  void Scene::set_width(int width) { this->_width = width; }

  void Scene::print() const {

    for (auto const &s : _shapes) {
      s->print();
    }

    for (auto const &light : _lights) {
      light.print();
    }

    _cam.print();
  }

  std::vector<vec3> Scene::render_scene(const tracer &tracer) {

    std::vector<vec3> pixels(_width * _height);
    std::cout << "Rendering a scene of size " << _width << " x " << _height
              << "" << std::endl;

    vec3 eye = _cam.look_from();

    int i, j;
    for (i = 0; i < _height; i++) {

      for (j = 0; j < _width; j++) {
        int counter = 0;

        Ray _ray;

        _ray.position = eye;
        _ray.direction = _cam.direction(j, i, _width, _height);

        // Multiply the result by 255 to handle RGB values of 255.
        vec3 res = vec3(255) * tracer.trace(_ray);
        pixels[i * _width + j] = res;
      }

      // Someway of printing out the status of the image.
      if (i + j % 100 == 0) {
        std::cout << "\b" << float((i + j)) / (_width * _height) * 100
                  << " \% done " << std::endl;
      }
    }

    return pixels;
  }

  std::vector<Light> Scene::get_lights() { return _lights; }

  const std::vector<std::unique_ptr<Shape>> &Scene::get_shapes() {
    return _shapes;
  }

  void Scene::add_shape(std::unique_ptr<Shape> &_shape) {

    _shapes.push_back(std::move(_shape));
  }
  void Scene::add_light(const Light &light) { _lights.push_back(light); }

  int Scene::get_width() const { return _width; }
  int Scene::get_height() const { return _height; }

  vec3 Scene::get_attenuation() const { return _attenuation; }

  void Scene::set_attenuation(const vec3 &vec) { _attenuation = vec; }

  Camera Scene::get_cam() { return _cam; }
} // namespace raytracer