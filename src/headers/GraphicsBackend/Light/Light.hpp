#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

namespace Model {

class Light {
public:
  glm::vec3 light_color;
  glm::vec3 light_pos;
};

} // namespace Model

#endif
