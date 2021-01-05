#ifndef SPHERE_CPP
#define SPHERE_HPP

#include "gl_typedef.hpp"
#include "shape.hpp"
#include <optional>
#include <vector>

namespace raytracer {

  class Ray;
  class Sphere : public Shape {

  public:
    explicit Sphere(float radius = 1.0f, vec3 center = vec3(0, 0, 0),
                    mat4 transformation = mat4(1.0f));

    std::optional<IntersectResult> inside(const Ray &ray) override;
    void print() override;

    vec3 normal(const vec3 &) const override;
    vec3 get_center();
    float get_radius();

  private:
    float _radius{1.0f};
    vec3 _center{0, 0, 0};
  };

} // namespace raytracer

#endif