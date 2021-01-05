#include "camera.hpp"

#include <iostream>

#include "util.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace raytracer {

  Camera &Camera::set_look_from(const vec3 &look_from) {
    this->_look_from = look_from;
    return *this;
  }

  Camera &Camera::set_look_at(const vec3 &look_at) {
    this->_look_at = look_at;
    return *this;
  }

  Camera &Camera::set_up(const vec3 &up) {
    this->_up = up;
    return *this;
  }

  Camera &Camera::set_fovy(const float &fovy) {
    this->_fovy = fovy;
    return *this;
  }

  Camera &Camera::set_fovx(const float fovx, int width, int height) {

    auto aspect = (double)width / height;
    this->_fovy =
        glm::degrees(2 * glm::atan(glm::tan(glm::radians(fovx / 2)) / aspect));
    return *this;
  }

  vec3 Camera::direction(int px, int py, int width, int height) const {

    auto tan = glm::tan(glm::radians(_fovy) / 2.0);
    auto aspect = (double)width / height;
    auto offset_width = ((px + 0.5) - (width / 2.0)) / (width / 2.0);
    auto offset_height = (height / 2.0 - (py + 0.5)) / (height / 2.0);

    float alpha = aspect * tan * offset_width;
    float beta = tan * offset_height;

    vec3 wvec = glm::normalize(_look_from - _look_at);
    vec3 uvec = glm::normalize(glm::cross(_up, wvec));
    vec3 vvec = glm::cross(wvec, uvec);
    return normalize(alpha * uvec + beta * vvec - wvec);
  }

  vec3 Camera::look_from() const { return _look_from; }
  vec3 Camera::at() const { return _look_at; }

  vec3 Camera::up() const { return _up; }

  float Camera::fovy() const { return _fovy; }

  mat4 Camera::look_at_matrix() const {
    return glm::lookAt(_look_from, _look_at, _up);
  }

  void Camera::print() const {
    std::cout << "Camera:";
    std::cout << "look_from=";
    util::print_vector(_look_from);

    std::cout << "look_at=";
    util::print_vector(_look_at);
    std::cout << "up=";
    util::print_vector(_up);
  }

} // namespace raytracer