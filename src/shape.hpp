#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "gl_typedef.hpp"
#include "intersect_result.hpp"
#include "material.hpp"
#include <memory>
#include <optional>

namespace raytracer {

  enum class shapes { plane, sphere };

  class Ray;
  class Shape {

  private:
    Material _material;

  protected:
    explicit Shape(vec3 normal, mat4 transform)
        : _transform(transform), _normal(normal){

                                 };

    explicit Shape() {}

    Shape(vec3 normal) : _normal(normal) {}

    vec3 _normal;
    mat4 _transform = mat4(1.0);

  public:
    virtual void print() = 0;
    virtual std::optional<IntersectResult> inside(const Ray &ray) = 0;
    mat4 get_transform() const { return _transform; }

    void set_transform(const mat4 transform) { _transform = transform; }
    virtual vec3 normal(const vec3 &v = vec3(0)) const = 0;
    Material get_material() const { return _material; }

    void set_material(const Material &material) { _material = material; }
  };

} // namespace raytracer
#endif