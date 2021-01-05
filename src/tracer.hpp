#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "gl_typedef.hpp"
#include "scene.hpp"

// Needed for std::shared_ptr
#include <memory>

namespace raytracer {

  class IntersectResult;
  class Ray;
  class tracer {

  private:
    vec3 _trace_reflected(const Ray &ray, int counter) const;
    vec3 _compute_color(IntersectResult &rd, const Ray &ray) const;
    std::optional<IntersectResult> _closest_shape(const Ray &ray) const;

    std::shared_ptr<Scene> _scene;
    int _max_depth;

  public:
    explicit tracer(int max_depth, std::shared_ptr<Scene> scene);
    vec3 trace(const Ray &ray) const;
  };

} // namespace raytracer
#endif