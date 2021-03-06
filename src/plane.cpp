#include "plane.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>

#include "gl_typedef.hpp"
#include "intersect_result.hpp"
#include "ray.hpp"
#include "util.hpp"

namespace raytracer {

  Plane::Plane(const std::vector<vec3> &vertices)
      : _vertices(vertices),
        Shape(vec4(glm::triangleNormal(vec3(vertices[0]), vec3(vertices[1]),
                                       vec3(vertices[2])),
                   0)) {}

  void Plane::print() {

    std::cout << "vertices:" << std::endl;
    for (auto const &vec : _vertices) {
      util::print_vector(vec);
    }
    std::cout << "normal:";
    util::print_vector(_normal);
    std::cout << "transform";
    util::print_matrix(_transform);
    std::cout << "material" << std::endl;
    std::cout << "ambient";
    util::print_vector(get_material().ambient);
    std::cout << "emission";
    util::print_vector(get_material().emission);
    std::cout << "diffuse";
    util::print_vector(get_material().diffuse);
    std::cout << "shininess: " << get_material().shininess << std::endl;
    std::cout << "specular";
    util::print_vector(get_material().specular);

    // std::cout << "normal: " << std::setprecision(3) <<
    // glm::to_string(_normal) << std::endl; std::cout << "transform: " <<
    // std::setprecision(3) << glm::to_string(_transform) << std::endl;
  }

  /* A algorithm to compute whether a position interects with a plane */
  std::optional<IntersectResult> Plane::inside(const Ray &_ray) {

    IntersectResult result;

    /* We want to determine if the ray intersects with the plane, which is
     * transformed */
    /* We apply the strategy which may not be relevant here, since a transformed
       plane is just a transformed plane (as opposed to an ellipse or whatever):

        1. Convert the Transformed Object into a space that we understand:
            - Take the inverse of the transformation and apply it to the ray
                The initial position transforms with the homogenous coordinate
       as 1 The direction transforms with a homogenous coordinate as 0
        2. Perform the standard intersection (Ray-Plane):
            - P is the
            - A point on the plane is given as P = P_i + t * P_d, where P_i, and
       P_d are the initial position and direction of the ray
            - A plane is given by 2 vertices. The relevant vertices are P, the
       point of intersection, and A, a point on the triangle. the plane is then
       formed by the equation (P-A) * n = 0, where P-A is the vector from P to
       A. Note: A could just as easily been B or C. Expanded: P * n - A * n = 0
       which becomes P * n = A * n The normal of a plane is [(C-A) X (B-A)] /
       |(C-A) X (B-A)| where X is the cross product
            - The combined equation is (P_i + t * P_ d) * n = A * n which
       becomes P_i * n + t * P_d * n = A * n Note that does products do not
       "cancel". For some a,b,c: c * a = c * b does not imply a = b. (Consider
       orthogonal vectors in 3 dimensions: c * a = c * b = 0, but a != c )
            - Therefore the solution after solving for t is t = [A * n - P_i *
       n] / [P_d * n]
        3. If this solution t is positive, then the intersection occured in the
       direction of the ray Likewise, if the solution t is negative, it must
       have gone backwards, and therefore will not hit the ray.
        4. However, we must now determine that the intersected point occured
       inside of the plane: We use barycentric coordinates for this.
     */

    /* 1 */
    auto inverse_ray = util::inverse_ray(_transform, _ray);

    /* 2 */
    result.distance = _dist_to_plane(inverse_ray);
    std::optional<IntersectResult> return_result;
    /* 3: If t is a tiny bit positive */
    if (result.distance > 0.0001) {
      const auto [position, direction] = inverse_ray;
      /* This point is the point after inversing the inverse (by applying the
       * transform positively) */
      auto world_coord = util::transform_to_world(
          _transform, position + direction * result.distance);
      result.point = util::dehomogenize(world_coord);

      /* 4 */
      auto intersect = _intersect(result.point);
      result.shape_ptr = std::make_shared<Plane>(*this);

      if (intersect) {
        return_result = result;
      }
    }

    return return_result;
  }

  /* Use Barycentric coordinates to determine if the intersected position is in
   * the triangle */
  bool Plane::_intersect(const vec3 &position_to_plane) {

    vec3 v0 = vec3(_vertices[1] - _vertices[0]);
    vec3 v1 = vec3(_vertices[2] - _vertices[0]);
    vec3 v2 = vec3(position_to_plane) - vec3(_vertices[0]);
    float d00 = glm::dot(v0, v0);
    float d01 = glm::dot(v0, v1);
    float d11 = glm::dot(v1, v1);
    float d20 = glm::dot(v2, v0);
    float d21 = glm::dot(v2, v1);
    float d = d00 * d11 - d01 * d01;
    float beta = (d11 * d20 - d01 * d21) / d;
    float gamma = (d00 * d21 - d01 * d20) / d;
    float alpha = 1.0f - beta - gamma;

    return beta >= 0 && gamma >= 0 && alpha >= 0;
  }

  float Plane::_dist_to_plane(const Ray &_ray) {

    float t =
        glm::dot(_vertices[0], _normal) - glm::dot(_ray.position, _normal);
    t = t / glm::dot(_ray.direction, _normal);

    return t;
  }

  vec3 Plane::normal(const vec3 &v) const { return _normal; }
} // namespace raytracer
